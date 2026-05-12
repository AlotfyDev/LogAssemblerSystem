
#include "assembler/circulation_mechanism/circulation_mechanism_container_registry.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_waiting_list.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_round_manager.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_reference_precalculator.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_ingress.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_dispatcher.hpp"

#include <array>
#include <cstdint>

using namespace assembler::circulation_mechanism;

struct IntegrationContainer {
    TContainerState state_value{TContainerState::default_empty};
    TSlotIndex ingress_slot{TSlotIndex::invalid()};
    TSlotIndex dispatch_slot{TSlotIndex::invalid()};
    TIngressPayloadEnvelopeRef placed_payload{TIngressPayloadEnvelopeRef::invalid()};
    TDispatchAccessRef exposed_ref{};

    constexpr IntegrationContainer() noexcept = default;
    constexpr IntegrationContainer(TContainerState s, TSlotIndex in, TSlotIndex out) noexcept
        : state_value(s), ingress_slot(in), dispatch_slot(out) {}

    constexpr TContainerState state() const noexcept { return state_value; }
    constexpr TSlotIndex find_first_ingress_writable_slot() const noexcept { return ingress_slot; }
    constexpr TSlotIndex find_first_dispatch_ready_slot() const noexcept { return dispatch_slot; }

    bool place_from_ingress_ref(TIngressAccessRef ref, TIngressPayloadEnvelopeRef payload) noexcept {
        if (!ref.can_be_consumed_by_ingress() || !payload.is_valid()) return false;
        placed_payload = payload;
        state_value = TContainerState::dispatch_candidate;
        dispatch_slot = ref.base.scope.slot_index;
        return true;
    }

    bool expose_from_dispatch_ref(TDispatchAccessRef ref) noexcept {
        if (!ref.can_be_consumed_by_dispatcher()) return false;
        exposed_ref = ref;
        state_value = TContainerState::dispatch_exposed;
        return true;
    }
};

int main() {
    TContainerRegistry<IntegrationContainer, 2> registry{};
    registry.initialize();
    auto ar = registry.assign(TContainerRegistryIndex::from_raw(1), IntegrationContainer{TContainerState::ingress_ready, TSlotIndex::from_raw(1), TSlotIndex::invalid()});
    if (!ar.accepted()) return 1;

    TIngressWaitingList<2> ingress_list{};
    auto wr = ingress_list.try_push(TWaitingListEntry{TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready, 0, registry.generation()});
    if (!wr.accepted()) return 2;

    TRoundManager<2> round{TRoundId::from_raw(1), TRoundKind::ingress};
    if (round.begin_collecting() != TRoundLifecycleStatus::accepted) return 3;
    if (round.open() != TRoundLifecycleStatus::accepted) return 4;
    auto adm = round.admit(TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready);
    if (!adm.accepted()) return 5;

    std::array<TReferenceCandidate, 1> candidates{TReferenceCandidate{TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready, registry.generation()}};
    TReferencePrecalculator<2,2> precalc{TReferencePrecalculatorId::from_raw(1), TReferenceSupplyPolicy{1,1,true}, 1};
    auto prep = precalc.replenish_ingress(registry, candidates, TRoundId::from_raw(1), TReferenceReportId::from_raw(1));
    if (prep.ingress_refs_prepared != 1) return 6;

    TIngress ingress{TIngressId::from_raw(1), TIngressBoundaryDescriptor{TIngressBoundaryId::from_raw(1), TIngressBoundaryStatus::ready, true, false}};
    auto* target = registry.try_get(TContainerRegistryIndex::from_raw(1));
    if (!target) return 7;
    auto placement = ingress.place(TIngressReportId::from_raw(2), TIngressPayloadEnvelopeRef::from_raw(99), precalc.pop_next_ingress(), *target);
    if (!placement.accepted()) return 8;

    // Prepare dispatch after state transition
    std::array<TReferenceCandidate, 1> dc{TReferenceCandidate{TContainerRegistryIndex::from_raw(1), TContainerState::dispatch_candidate, registry.generation()}};
    auto dprep = precalc.replenish_dispatch(registry, dc, TRoundId::from_raw(2), TReferenceReportId::from_raw(3));
    if (dprep.dispatch_refs_prepared != 1) return 9;

    TDispatcher dispatcher{TDispatcherId::from_raw(1),
        TPassivePullDispatchProfile{TDispatchProfileKind::passive_pull, false, false},
        TPushDispatchProfile{TDispatchProfileKind::push, false},
        TDispatchBoundaryDescriptor{TDispatchBoundaryId::from_raw(1), TDispatchBoundaryStatus::ready, true, false}
    };

    auto exposure = dispatcher.expose_passive(TDispatchReportId::from_raw(4), precalc.pop_next_dispatch(), *target);
    if (!exposure.exposed()) return 10;

    return 0;
}
