#pragma once
#include "../config/TReadSideCirculationConfig.hpp"

/*
    TReadSideEngineProfile.hpp

    Current responsibility:
        Profile wrapper for ReadSide injection.

    Production capabilities:
        - binds a valid read-side configuration
        - declares post-bridge/read-side runtime nature
        - declares no PreBridge runtime dependency

    Explicit non-ownership:
        - Does not instantiate PreBridge.
        - Does not implement receiver/addon behavior.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideEngineProfile final {
    TReadSideCirculationConfig config{};
    bool post_bridge_profile{true};
    bool requires_pre_bridge_runtime{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return config.is_valid() && post_bridge_profile && !requires_pre_bridge_runtime;
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
