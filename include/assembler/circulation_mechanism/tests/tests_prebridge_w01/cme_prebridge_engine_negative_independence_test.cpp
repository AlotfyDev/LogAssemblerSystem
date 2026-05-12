
#include "assembler/circulation_mechanism/circulation_mechanism_pre_bridge.hpp"

using namespace assembler::circulation_mechanism;
using namespace assembler::circulation_mechanism::pre_bridge;

int main()
{
    TPreBridgeCirculationConfig invalid_config{};
    if (invalid_config.is_valid()) return 1;

    TPreBridgeCirculationProfile invalid_profile{
        invalid_config,
        true,
        true,
        false
    };

    TPreBridgeCirculationEngine invalid_engine{TPreBridgeEngineId::from_raw(1), invalid_profile};
    auto init = invalid_engine.initialize(TPreBridgeEngineReportId::from_raw(2));
    if (init.passed()) return 2;

    // Explicitly reject profile that requires read-side runtime.
    TPreBridgeCirculationProfile read_side_dependent{
        invalid_config,
        true,
        true,
        true
    };
    if (read_side_dependent.is_valid()) return 3;

    return 0;
}
