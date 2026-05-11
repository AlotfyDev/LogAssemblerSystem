#pragma once
#include "../config/TPreBridgeCirculationConfig.hpp"

/*
    TPreBridgeCirculationProfile.hpp

    Current responsibility:
        Profile wrapper for PreBridge injection.

    Production capabilities:
        - binds valid config,
        - declares single producer / single dispatcher assumptions,
        - declares no ReadSide runtime dependency.

    Explicit non-ownership:
        - Does not own ReadSide retry/backpressure/receiver lifecycle.
*/
namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeCirculationProfile final {
    TPreBridgeCirculationConfig config{};
    bool single_producer{true};
    bool single_dispatcher{true};
    bool requires_read_side_runtime{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return config.is_valid() && single_producer && single_dispatcher && !requires_read_side_runtime;
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
