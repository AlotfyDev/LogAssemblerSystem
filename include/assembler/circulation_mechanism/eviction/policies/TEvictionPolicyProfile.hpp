#pragma once
#include "TEvictionPolicyProfileId.hpp"
#include "assembler/circulation_mechanism/eviction/TEvictionPolicyKind.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TEvictionPolicyProfile final {
    TEvictionPolicyProfileId profile_id{};
    TEvictionPolicyKind kind{TEvictionPolicyKind::no_eviction_pre_bridge};
    bool safe_point_required{true};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile_id.is_valid(); }
    [[nodiscard]] constexpr bool eviction_enabled() const noexcept {
        return kind == TEvictionPolicyKind::oldest_time_range || kind == TEvictionPolicyKind::fifo_container || kind == TEvictionPolicyKind::emergency;
    }
    [[nodiscard]] constexpr bool delegated_to_read_side() const noexcept { return kind == TEvictionPolicyKind::delegate_to_read_side; }
};
} // namespace circulation_mechanism
} // namespace assembler
