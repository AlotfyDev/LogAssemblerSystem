#pragma once
#include "assembler/circulation_mechanism/eviction/TEvictionCandidate.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TOldestTimeRangeEviction final {
    [[nodiscard]] static constexpr bool can_consider(TEvictionCandidate c) noexcept {
        return c.evaluate(true) == TEvictionEvaluationStatus::accepted;
    }
    [[nodiscard]] static constexpr bool lhs_is_older(TEvictionCandidate lhs, TEvictionCandidate rhs) noexcept {
        return can_consider(lhs) && can_consider(rhs) && lhs.time_range.older_than(rhs.time_range);
    }
};
} // namespace circulation_mechanism
} // namespace assembler
