#include "assembler/circulation_mechanism/circulation_mechanism_read_side_engine.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::read_side;
namespace rscp = assembler::circulation_mechanism::read_side_circulation_profile;

int main()
{
    constexpr TReadSideCirculationConfig invalid_config{};
    static_assert(!invalid_config.is_valid(), "default config invalid");

    constexpr TReadSideEngineProfile prebridge_dependent{
        invalid_config,
        true,
        true
    };
    static_assert(!prebridge_dependent.is_valid(), "read-side profile must not require pre-bridge runtime");

    TReadSideCirculationEngine invalid_engine{TReadSideEngineId::from_raw(1), prebridge_dependent};
    auto init = invalid_engine.initialize(TReadSideEngineReportId::from_raw(2));
    if (init.passed()) return 1;

    constexpr TCirculationConfigurationDescriptor wrong_runtime_config{
        TCirculationConfigurationId::from_raw(10),
        TCirculationConfigurationStatus::validated,
        TCirculationProfileKind::pre_bridge,
        TCirculationApiVersion::from_raw(1),
        TCirculationProfileVersion::from_raw(1)
    };

    constexpr TReadSideCirculationConfig wrong_profile_kind{
        wrong_runtime_config,
        rscp::TReadSideCirculationProfile{},
        rscp::TPostBridgeCapacityProfile{},
        rscp::TReadSideBackpressureProfile{},
        rscp::TDelayedReleaseProfile{},
        rscp::TAddonBoundaryDescriptor{}
    };

    if (wrong_profile_kind.is_valid()) return 2;

    return 0;
}
