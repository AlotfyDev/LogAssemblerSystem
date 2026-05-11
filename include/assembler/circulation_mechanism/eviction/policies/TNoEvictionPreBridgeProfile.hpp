#pragma once
#include "TEvictionPolicyProfile.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TNoEvictionPreBridgeProfile final {
    TEvictionPolicyProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return profile.is_valid() && profile.kind == TEvictionPolicyKind::no_eviction_pre_bridge && !profile.eviction_enabled();
    }
};
} // namespace circulation_mechanism
} // namespace assembler
