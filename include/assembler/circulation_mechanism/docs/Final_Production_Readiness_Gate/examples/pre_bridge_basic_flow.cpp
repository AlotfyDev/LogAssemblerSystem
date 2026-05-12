
#include "assembler/circulation_mechanism/circulation_mechanism_pre_bridge.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_container_registry.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_waiting_list.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_round_manager.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_reference_precalculator.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_ingress.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_dispatcher.hpp"

#include <array>
#include <cstdint>

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::pre_bridge;

struct TExamplePreBridgeContainer
{
    TContainerState state_value{TContainerState::default_empty};
    TSlotIndex ingress_slot{TSlotIndex::invalid()};
    TSlotIndex dispatch_slot{TSlotIndex::invalid()};
    TIngressPayloadEnvelopeRef placed_payload{TIngressPayloadEnvelopeRef::invalid()};
    TDispatchAccessRef exposed_ref{};
    bool exposure_observed{false};

    constexpr TExamplePreBridgeContainer() noexcept = default;

    constexpr TExamplePreBridgeContainer(TContainerState state, TSlotIndex ingress, TSlotIndex dispatch) noexcept
        : state_value(state),
          ingress_slot(ingress),
          dispatch_slot(dispatch)
    {
    }

    constexpr TContainerState state() const noexcept
    {
        return state_value;
    }

    constexpr TSlotIndex find_first_ingress_writable_slot() const noexcept
    {
        return ingress_slot;
    }

    constexpr TSlotIndex find_first_dispatch_ready_slot() const noexcept
    {
        return dispatch_slot;
    }

    bool place_from_ingress_ref(TIngressAccessRef ref, TIngressPayloadEnvelopeRef payload) noexcept
    {
        if (!ref.can_be_consumed_by_ingress() || !payload.is_valid())
        {
            return false;
        }

        placed_payload = payload;
        state_value = TContainerState::dispatch_candidate;
        dispatch_slot = ref.base.scope.slot_index;
        return true;
    }

    bool expose_from_dispatch_ref(TDispatchAccessRef ref) noexcept
    {
        if (!ref.can_be_consumed_by_dispatcher())
        {
            return false;
        }

        exposed_ref = ref;
        exposure_observed = true;
        state_value = TContainerState::dispatch_exposed;
        return true;
    }
};

constexpr TUniformContainerCapacityProfile make_uniform_capacity()
{
    return TUniformContainerCapacityProfile{
        TCapacityProfileId::from_raw(1),
        TCapacityGenerationId::from_raw(1),
        TCapacityProfileStatus::active,
        2U,
        1U
    };
}

constexpr TIngressCapacityProfile make_ingress_capacity()
{
    return TIngressCapacityProfile{
        TCapacityProfileId::from_raw(2),
        TCapacityProfileStatus::active,
        1U,
        2U,
        1U
    };
}

constexpr TDispatchCapacityProfile make_dispatch_capacity()
{
    return TDispatchCapacityProfile{
        TCapacityProfileId::from_raw(3),
        TCapacityProfileStatus::active,
        1U,
        2U,
        1U,
        1U
    };
}

constexpr TCirculationCapacityProfile make_capacity_profile()
{
    return TCirculationCapacityProfile{
        TCapacityProfileId::from_raw(4),
        TCapacityGenerationId::from_raw(2),
        TCapacityProfileStatus::active,
        make_uniform_capacity(),
        make_ingress_capacity(),
        make_dispatch_capacity(),
        1U,
        true,
        false
    };
}

constexpr TExposureContractDescriptor make_exposure_contract()
{
    return TExposureContractDescriptor{
        TExposureContractId::from_raw(5),
        TExposureMode::passive_pull,
        TExposureMaterialKind::dispatch_ref,
        false,
        false
    };
}

constexpr TEnvelopePlacementPortDescriptor make_ingress_port()
{
    return TEnvelopePlacementPortDescriptor{
        TEnvelopePlacementPortId::from_raw(6),
        TCommunicationBindingStatus::ready,
        true,
        false
    };
}

constexpr TBridgeFacingDispatchAdapterDescriptor make_dispatch_adapter()
{
    return TBridgeFacingDispatchAdapterDescriptor{
        TDispatchOutputAdapterId::from_raw(7),
        TCommunicationBindingStatus::ready,
        true,
        false,
        make_exposure_contract()
    };
}

constexpr TCirculationCommunicationBindingDescriptor make_ingress_binding()
{
    return TCirculationCommunicationBindingDescriptor{
        TCommunicationBindingId::from_raw(8),
        TCommunicationBindingKind::ingress_placement,
        TCommunicationBindingStatus::ready,
        make_ingress_port(),
        TBridgeFacingDispatchAdapterDescriptor{},
        TBridgeFacingBoundaryDescriptor{}
    };
}

constexpr TCirculationCommunicationBindingDescriptor make_dispatch_binding()
{
    return TCirculationCommunicationBindingDescriptor{
        TCommunicationBindingId::from_raw(9),
        TCommunicationBindingKind::dispatch_output,
        TCommunicationBindingStatus::ready,
        TEnvelopePlacementPortDescriptor{},
        make_dispatch_adapter(),
        TBridgeFacingBoundaryDescriptor{}
    };
}

constexpr TCirculationConfigurationDescriptor make_runtime_config()
{
    return TCirculationConfigurationDescriptor{
        TCirculationConfigurationId::from_raw(10),
        TCirculationConfigurationStatus::validated,
        TCirculationProfileKind::pre_bridge,
        TCirculationApiVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(1)
    };
}

constexpr TPreBridgeDefaultInjectionProfile make_default_injection_profile()
{
    return TPreBridgeDefaultInjectionProfile{
        TPreBridgeDefaultProfileId::from_raw(11),
        TPreBridgeDefaultProfileStatus::ready,
        TPreBridgeBindingSet{
            TPreBridgeBindingSetId::from_raw(12),
            TPreBridgeCapacityBinding{make_capacity_profile(), true},
            TPreBridgeBoundaryBinding{make_ingress_binding(), make_dispatch_binding()},
            TPreBridgeReferenceSupplyBinding{TReferenceSupplyPolicy{1U, 1U, true}, true},
            TPreBridgeDiagnosticsBinding{true, false, false}
        }
    };
}

int run_pre_bridge_example()
{
    constexpr auto default_profile = make_default_injection_profile();
    static_assert(default_profile.is_valid(), "default PreBridge profile must be valid.");

    constexpr auto profile = default_profile.to_pre_bridge_profile(make_runtime_config());
    static_assert(profile.is_valid(), "PreBridge profile must be valid.");

    TPreBridgeCirculationEngine engine{TPreBridgeEngineId::from_raw(13), profile};
    if (!engine.is_valid())
    {
        return 1;
    }

    if (!engine.initialize(TPreBridgeEngineReportId::from_raw(14)).passed())
    {
        return 2;
    }

    if (!engine.start(TPreBridgeEngineReportId::from_raw(15)).passed())
    {
        return 3;
    }

    TContainerRegistry<TExamplePreBridgeContainer, 1> registry{};
    registry.initialize();

    auto assigned = registry.assign(
        TContainerRegistryIndex::from_raw(1),
        TExamplePreBridgeContainer{
            TContainerState::ingress_ready,
            TSlotIndex::from_raw(1),
            TSlotIndex::invalid()
        }
    );

    if (!assigned.accepted())
    {
        return 4;
    }

    TIngressWaitingList<2> ingress_list{};
    auto ingress_entry = ingress_list.try_push(
        TWaitingListEntry{
            TContainerRegistryIndex::from_raw(1),
            TContainerState::ingress_ready,
            0U,
            registry.generation()
        }
    );

    if (!ingress_entry.accepted())
    {
        return 5;
    }

    TRoundManager<2> ingress_round{TRoundId::from_raw(20), TRoundKind::ingress};
    if (ingress_round.begin_collecting() != TRoundLifecycleStatus::accepted) return 6;
    if (ingress_round.open() != TRoundLifecycleStatus::accepted) return 7;
    if (!ingress_round.admit(TContainerRegistryIndex::from_raw(1), TContainerState::ingress_ready).accepted()) return 8;
    if (ingress_round.lock_membership() != TRoundLifecycleStatus::accepted) return 9;
    if (ingress_round.mark_draining() != TRoundLifecycleStatus::accepted) return 10;

    std::array<TReferenceCandidate, 1> ingress_candidates{
        TReferenceCandidate{
            TContainerRegistryIndex::from_raw(1),
            TContainerState::ingress_ready,
            registry.generation()
        }
    };

    TReferencePrecalculator<2, 2> precalc{
        TReferencePrecalculatorId::from_raw(30),
        TReferenceSupplyPolicy{1U, 1U, true},
        1U
    };

    auto ingress_precalc = precalc.replenish_ingress(
        registry,
        ingress_candidates,
        TRoundId::from_raw(20),
        TReferenceReportId::from_raw(31)
    );

    if (ingress_precalc.ingress_refs_prepared != 1U)
    {
        return 11;
    }

    TIngress ingress{
        TIngressId::from_raw(40),
        TIngressBoundaryDescriptor{
            TIngressBoundaryId::from_raw(41),
            TIngressBoundaryStatus::ready,
            true,
            false
        }
    };

    auto* target = registry.try_get(TContainerRegistryIndex::from_raw(1));
    if (!target)
    {
        return 12;
    }

    auto placement = ingress.place(
        TIngressReportId::from_raw(42),
        TIngressPayloadEnvelopeRef::from_raw(100),
        precalc.pop_next_ingress(),
        *target
    );

    if (!placement.accepted())
    {
        return 13;
    }

    TDispatchWaitingList<2> dispatch_list{};
    auto dispatch_entry = dispatch_list.try_push(
        TWaitingListEntry{
            TContainerRegistryIndex::from_raw(1),
            TContainerState::dispatch_candidate,
            0U,
            registry.generation()
        }
    );

    if (!dispatch_entry.accepted())
    {
        return 14;
    }

    TRoundManager<2> dispatch_round{TRoundId::from_raw(50), TRoundKind::dispatch};
    if (dispatch_round.begin_collecting() != TRoundLifecycleStatus::accepted) return 15;
    if (dispatch_round.open() != TRoundLifecycleStatus::accepted) return 16;
    if (!dispatch_round.admit(TContainerRegistryIndex::from_raw(1), TContainerState::dispatch_candidate).accepted()) return 17;
    if (dispatch_round.lock_membership() != TRoundLifecycleStatus::accepted) return 18;
    if (dispatch_round.mark_draining() != TRoundLifecycleStatus::accepted) return 19;

    std::array<TReferenceCandidate, 1> dispatch_candidates{
        TReferenceCandidate{
            TContainerRegistryIndex::from_raw(1),
            TContainerState::dispatch_candidate,
            registry.generation()
        }
    };

    auto dispatch_precalc = precalc.replenish_dispatch(
        registry,
        dispatch_candidates,
        TRoundId::from_raw(50),
        TReferenceReportId::from_raw(51)
    );

    if (dispatch_precalc.dispatch_refs_prepared != 1U)
    {
        return 20;
    }

    TDispatcher dispatcher{
        TDispatcherId::from_raw(60),
        TPassivePullDispatchProfile{TDispatchProfileKind::passive_pull, false, false},
        TPushDispatchProfile{TDispatchProfileKind::push, false},
        TDispatchBoundaryDescriptor{
            TDispatchBoundaryId::from_raw(61),
            TDispatchBoundaryStatus::ready,
            true,
            false
        }
    };

    auto exposure = dispatcher.expose_passive(
        TDispatchReportId::from_raw(62),
        precalc.pop_next_dispatch(),
        *target
    );

    if (!exposure.exposed())
    {
        return 21;
    }

    if (!target->exposure_observed)
    {
        return 22;
    }

    if (!engine.stop(TPreBridgeEngineReportId::from_raw(63)).passed())
    {
        return 23;
    }

    return 0;
}

int main()
{
    return run_pre_bridge_example();
}
