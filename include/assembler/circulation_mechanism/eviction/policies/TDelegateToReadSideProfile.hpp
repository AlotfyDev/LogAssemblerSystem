#pragma once
#include "TEvictionPolicyProfile.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDelegateToReadSideProfile final {
    TEvictionPolicyProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile.is_valid() && profile.delegated_to_read_side(); }
};
} // namespace circulation_mechanism
} // namespace assembler
