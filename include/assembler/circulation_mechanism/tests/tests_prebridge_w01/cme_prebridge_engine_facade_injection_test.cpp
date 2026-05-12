
#include "assembler/circulation_mechanism/circulation_mechanism_pre_bridge.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::pre_bridge;

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

constexpr TCirculationCapacityProfile capacity{
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

constexpr TExposureContractDescriptor exposure{
    TExposureContractId::from_raw(5),
    TExposureMode::passive_pull,
    TExposureMaterialKind::dispatch_ref,
    false,
    false
};

constexpr TEnvelopePlacementPortDescriptor ingress_port{
    TEnvelopePlacementPortId::from_raw(6),
    TCommunicationBindingStatus::ready,
    true,
    false
};

constexpr TBridgeFacingDispatchAdapterDescriptor dispatch_adapter{
    TDispatchOutputAdapterId::from_raw(7),
    TCommunicationBindingStatus::ready,
    true,
    false,
    exposure
};

constexpr TCirculationCommunicationBindingDescriptor ingress_binding{
    TCommunicationBindingId::from_raw(8),
    TCommunicationBindingKind::ingress_placement,
    TCommunicationBindingStatus::ready,
    ingress_port,
    TBridgeFacingDispatchAdapterDescriptor{},
    TBridgeFacingBoundaryDescriptor{}
};

constexpr TCirculationCommunicationBindingDescriptor dispatch_binding{
    TCommunicationBindingId::from_raw(9),
    TCommunicationBindingKind::dispatch_output,
    TCommunicationBindingStatus::ready,
    TEnvelopePlacementPortDescriptor{},
    dispatch_adapter,
    TBridgeFacingBoundaryDescriptor{}
};

constexpr TCirculationConfigurationDescriptor runtime_config{
    TCirculationConfigurationId::from_raw(10),
    TCirculationConfigurationStatus::validated,
    TCirculationProfileKind::pre_bridge,
    TCirculationApiVersion::from_raw(1),
    TCirculationProfileVersion::from_raw(1)
};

int main()
{
    static_assert(capacity.is_valid(), "capacity valid");
    static_assert(ingress_binding.is_valid(), "ingress binding valid");
    static_assert(dispatch_binding.is_valid(), "dispatch binding valid");
    static_assert(runtime_config.ready_for_runtime(), "runtime config ready");

    TPreBridgeCirculationConfig config{
        runtime_config,
        capacity,
        ingress_binding,
        dispatch_binding
    };

    if (!config.is_valid()) return 1;

    TPreBridgeCirculationProfile profile{
        config,
        true,
        true,
        false
    };

    if (!profile.is_valid()) return 2;

    TPreBridgeCirculationEngine engine{TPreBridgeEngineId::from_raw(11), profile};
    if (!engine.is_valid()) return 3;

    auto init = engine.initialize(TPreBridgeEngineReportId::from_raw(12));
    if (!init.passed()) return 4;
    if (!engine.view().ready()) return 5;

    auto start = engine.start(TPreBridgeEngineReportId::from_raw(13));
    if (!start.passed()) return 6;
    if (!engine.view().ready()) return 7;

    auto stop = engine.stop(TPreBridgeEngineReportId::from_raw(14));
    if (!stop.passed()) return 8;

    return 0;
}
