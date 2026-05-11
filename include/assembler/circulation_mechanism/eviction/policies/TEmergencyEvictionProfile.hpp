#pragma once
#include "TEvictionPolicyProfile.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TEmergencyEvictionProfile final {
    TEvictionPolicyProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return profile.is_valid() && profile.kind == TEvictionPolicyKind::emergency && profile.safe_point_required;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
