
#include "assembler/circulation_mechanism/circulation_mechanism_capacity.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_safe_points.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_container_registry.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_waiting_list.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_round_manager.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_reference_precalculator.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_ingress.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_dispatcher.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_release_recycle.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_communication_bindings.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w01.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w02.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w03.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile_w04.hpp"

#include <array>
#include <cstdint>

using namespace assembler::circulation_mechanism;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

struct E2EContainer {
    TContainerState state_value{TContainerState::default_empty};
    TSlotIndex ingress_slot{TSlotIndex::invalid()};
    TSlotIndex dispatch_slot{TSlotIndex::invalid()};
    TIngressPayloadEnvelopeRef placed_payload{TIngressPayloadEnvelopeRef::invalid()};
    TDispatchAccessRef exposed_ref{};
    bool exposure_observed{false};

    constexpr E2EContainer() noexcept = default;
    constexpr E2EContainer(TContainerState s, TSlotIndex in, TSlotIndex out) noexcept
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
        exposure_observed = true;
        state_value = TContainerState::dispatch_exposed;
        return true;
    }
};

int main() {
    constexpr TUniformContainerCapacityProfile uniform{
        TCapacityProfileId::from_raw(1),
        TCapacityGenerationId::from_raw(1),
        TCapacityProfileStatus::active,
        2U,
        1U
    };
    constexpr TIngressCapacityProfile ingress_capacity{
        TCapacityProfileId::from_raw(2),
        TCapacityProfileStatus::active,
        1U,
        2U,
        1U
    };
    constexpr TDispatchCapacityProfile dispatch_capacity{
        TCapacityProfileId::from_raw(3),
        TCapacityProfileStatus::active,
        1U,
        2U,
        1U,
        1U
    };
    constexpr TCirculationCapacityProfile circulation_capacity{
        TCapacityProfileId::from_raw(4),
        TCapacityGenerationId::from_raw(2),
        TCapacityProfileStatus::active,
        uniform,
        ingress_capacity,
        dispatch_capacity,
        1U,
        true,
        false
    };
    static_assert(circulation_capacity.is_valid(), "capacity valid");

    TContainerRegistry<E2EContainer, 1> registry{};
    registry.initialize();
    auto assigned = registry.assign(
        TContainerRegistryIndex::from_raw(1),
        E2EContainer{TContainerState::ingress_ready, TSlotIndex::from_raw(1), TSlotIndex::invalid()}
    );
    if (!assigned.accepted()) return 1;

    TIngressWaitingList<2> ingress_list{};
    auto ingress_candidate = ingress_list.try_push(
        TWaitingListEntry{TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready, 0U, registry.generation()}
    );
    if (!ingress_candidate.accepted()) return 2;

    TRoundManager<2> ingress_round{TRoundId::from_raw(10), TRoundKind::ingress};
    if (ingress_round.begin_collecting() != TRoundLifecycleStatus::accepted) return 3;
    if (ingress_round.open() != TRoundLifecycleStatus::accepted) return 4;
    auto ingress_admission = ingress_round.admit(TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready);
    if (!ingress_admission.accepted()) return 5;
    if (ingress_round.lock_membership() != TRoundLifecycleStatus::accepted) return 6;
    if (ingress_round.mark_draining() != TRoundLifecycleStatus::accepted) return 7;

    std::array<TReferenceCandidate, 1> ingress_candidates{
        TReferenceCandidate{TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready, registry.generation()}
    };
    TReferencePrecalculator<2, 2> precalc{
        TReferencePrecalculatorId::from_raw(20),
        TReferenceSupplyPolicy{1U, 1U, true},
        1U
    };
    auto ingress_refs = precalc.replenish_ingress(
        registry,
        ingress_candidates,
        TRoundId::from_raw(10),
        TReferenceReportId::from_raw(21)
    );
    if (!ingress_refs.prepared_any() || ingress_refs.ingress_refs_prepared != 1U) return 8;

    TIngress ingress{
        TIngressId::from_raw(30),
        TIngressBoundaryDescriptor{TIngressBoundaryId::from_raw(31), TIngressBoundaryStatus::ready, true, false}
    };
    auto* target = registry.try_get(TContainerRegistryIndex::from_raw(1));
    if (!target) return 9;

    auto placed = ingress.place(
        TIngressReportId::from_raw(32),
        TIngressPayloadEnvelopeRef::from_raw(100),
        precalc.pop_next_ingress(),
        *target
    );
    if (!placed.accepted()) return 10;
    if (!target->placed_payload.is_valid()) return 11;

    TDispatchWaitingList<2> dispatch_list{};
    auto dispatch_candidate = dispatch_list.try_push(
        TWaitingListEntry{TContainerRegistryIndex::from_raw(1), TContainerState::dispatch_candidate, 0U, registry.generation()}
    );
    if (!dispatch_candidate.accepted()) return 12;

    TRoundManager<2> dispatch_round{TRoundId::from_raw(40), TRoundKind::dispatch};
    if (dispatch_round.begin_collecting() != TRoundLifecycleStatus::accepted) return 13;
    if (dispatch_round.open() != TRoundLifecycleStatus::accepted) return 14;
    auto dispatch_admission = dispatch_round.admit(TContainerRegistryIndex::from_raw(1), TContainerState::dispatch_candidate);
    if (!dispatch_admission.accepted()) return 15;
    if (dispatch_round.lock_membership() != TRoundLifecycleStatus::accepted) return 16;
    if (dispatch_round.mark_draining() != TRoundLifecycleStatus::accepted) return 17;

    std::array<TReferenceCandidate, 1> dispatch_candidates{
        TReferenceCandidate{TContainerRegistryIndex::from_raw(1), TContainerState::dispatch_candidate, registry.generation()}
    };
    auto dispatch_refs = precalc.replenish_dispatch(
        registry,
        dispatch_candidates,
        TRoundId::from_raw(40),
        TReferenceReportId::from_raw(41)
    );
    if (!dispatch_refs.prepared_any() || dispatch_refs.dispatch_refs_prepared != 1U) return 18;

    TDispatcher dispatcher{
        TDispatcherId::from_raw(51),
        TPassivePullDispatchProfile{TDispatchProfileKind::passive_pull, false, false},
        TPushDispatchProfile{TDispatchProfileKind::push, false},
        TDispatchBoundaryDescriptor{TDispatchBoundaryId::from_raw(52), TDispatchBoundaryStatus::ready, true, false}
    };
    auto exposed = dispatcher.expose_passive(
        TDispatchReportId::from_raw(53),
        precalc.pop_next_dispatch(),
        *target
    );
    if (!exposed.exposed()) return 19;
    if (!target->exposure_observed) return 20;

    static_assert(TRecyclePolicy::can_release_reference(TReferenceValidityState::invalidated) == TReleaseRecycleStatus::accepted,
        "invalidated ref may be released");
    static_assert(TRecyclePolicy::can_release_exposure(TDispatchExposureState::bridge_consumed) == TReleaseRecycleStatus::accepted,
        "bridge consumed exposure may be released");
    static_assert(TRecyclePolicy::can_reset_container(TContainerState::reset_pending, TSafePointState::available) == TReleaseRecycleStatus::accepted,
        "reset pending container can reset at safe point");

    constexpr rscp::TReadSideAdmissionBoundaryDescriptor read_admission{
        rscp::TReadSideAdmissionBoundaryId::from_raw(60),
        rscp::TReadSideAdmissionMode::passive_pull_from_bridge,
        rscp::TReadSideAdmissionStatus::ready,
        true,
        false
    };
    constexpr rscp::TReceiverContextDescriptor receiver{
        rscp::TReceiverContextId::from_raw(61),
        rscp::TReceiverContextKind::in_process_receiver,
        rscp::TReceiverLifecycleExpectation::ack_required,
        true,
        true
    };
    constexpr rscp::TPostBridgeBoundaryContractDescriptor post_bridge_contract{
        rscp::TPostBridgeBoundaryContractId::from_raw(62),
        rscp::TPostBridgeTransferSemantic::move,
        rscp::TPostBridgeBoundaryContractStatus::compatible,
        true,
        true
    };
    constexpr rscp::TReadSideCirculationProfile read_profile{
        rscp::TReadSideProfileId::from_raw(63),
        rscp::TReadSideProfileStatus::ready,
        read_admission,
        receiver,
        post_bridge_contract
    };
    static_assert(read_profile.ready(), "read-side profile ready");

    constexpr rscp::TPostBridgeCapacityProfile read_capacity{
        rscp::TPostBridgeCapacityProfileId::from_raw(64),
        rscp::TPostBridgeCapacityStatus::ready,
        1U,
        2U,
        1U,
        1U,
        0U
    };
    static_assert(read_capacity.receiver_has_room(), "read-side capacity has room");

    constexpr rscp::TReadSideBackpressureProfile read_pressure{
        rscp::TReadSideBackpressureProfileId::from_raw(65),
        rscp::TReadSideBackpressureMode::observe_only,
        rscp::TReadSideBackpressureState::normal,
        false
    };
    static_assert(read_pressure.decide(read_capacity) == rscp::TBackpressureDecisionKind::allow_admission,
        "read-side admits when no pressure");

    constexpr rscp::TReadSideDiagnosticRecord no_issue{
        rscp::TReadSideDiagnosticId::from_raw(66),
        rscp::TReadSideDiagnosticKind::none,
        rscp::TReadSideDiagnosticSeverity::info
    };
    constexpr rscp::TAddonBoundaryDescriptor addon{
        rscp::TAddonBoundaryId::from_raw(67),
        rscp::TAddonBoundaryKind::diagnostic_sink_adapter,
        rscp::TAddonBoundaryStatus::ready,
        false,
        false,
        false,
        false
    };
    constexpr auto integration = rscp::TReadSideIntegrationReport::evaluate(
        rscp::TReadSideIntegrationReportId::from_raw(68),
        no_issue,
        addon
    );
    static_assert(integration.passed(), "read-side addon integration passed");

    return 0;
}
