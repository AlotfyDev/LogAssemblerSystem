
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
    constexpr TPreBridgeBindingSet bindings{
        TPreBridgeBindingSetId::from_raw(11),
        TPreBridgeCapacityBinding{capacity, true},
        TPreBridgeBoundaryBinding{ingress_binding, dispatch_binding},
        TPreBridgeReferenceSupplyBinding{TReferenceSupplyPolicy{1U, 1U, true}, true},
        TPreBridgeDiagnosticsBinding{true, false, false}
    };
    static_assert(bindings.is_valid(), "binding set valid");

    constexpr TPreBridgeDefaultInjectionProfile default_profile{
        TPreBridgeDefaultProfileId::from_raw(12),
        TPreBridgeDefaultProfileStatus::ready,
        bindings
    };
    static_assert(default_profile.is_valid(), "default injection profile valid");

    constexpr auto profile = default_profile.to_pre_bridge_profile(runtime_config);
    static_assert(profile.is_valid(), "converted prebridge profile valid");

    TPreBridgeCirculationEngine engine{TPreBridgeEngineId::from_raw(13), profile};
    if (!engine.is_valid()) return 1;
    auto init = engine.initialize(TPreBridgeEngineReportId::from_raw(14));
    if (!init.passed()) return 2;

    TPreBridgeConfigurationReport report{
        TPreBridgeEngineReportId::from_raw(15),
        TPreBridgeDefaultProfileId::from_raw(12),
        default_profile.validation_issue()
    };
    if (!report.passed()) return 3;

    return 0;
}
