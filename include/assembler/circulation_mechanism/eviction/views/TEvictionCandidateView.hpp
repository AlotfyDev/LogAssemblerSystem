#pragma once
#include "assembler/circulation_mechanism/eviction/TEvictionCandidate.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TEvictionCandidateView final {
    TEvictionCandidate candidate{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return candidate.is_valid(); }
    [[nodiscard]] constexpr bool selectable() const noexcept { return candidate.safe_to_evict(); }
};
} // namespace circulation_mechanism
} // namespace assembler
