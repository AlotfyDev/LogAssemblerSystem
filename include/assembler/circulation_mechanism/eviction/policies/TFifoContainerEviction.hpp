#pragma once
#include "assembler/circulation_mechanism/eviction/TEvictionCandidate.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TFifoContainerEviction final {
    [[nodiscard]] static constexpr bool can_consider(TEvictionCandidate c) noexcept { return c.safe_to_evict(); }
};
} // namespace circulation_mechanism
} // namespace assembler
