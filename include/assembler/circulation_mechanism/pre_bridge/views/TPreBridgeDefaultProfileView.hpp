#pragma once
#include "assembler/circulation_mechanism/pre_bridge/default_profile/TPreBridgeDefaultInjectionProfile.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeDefaultProfileView final {
    TPreBridgeDefaultInjectionProfile profile{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return profile.is_valid();
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
