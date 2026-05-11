#pragma once
#include <cstdint>
#include "TWaitingListState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressWaitingListView final {
    TWaitingListState state{TWaitingListState::empty};
    std::uint32_t size{0};
    std::uint32_t capacity{0};
    std::uint64_t last_sequence{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return capacity > 0U && size <= capacity; }
    [[nodiscard]] constexpr bool has_candidates() const noexcept { return size > 0U; }
    [[nodiscard]] constexpr bool locked() const noexcept { return is_locked(state); }
};
} // namespace circulation_mechanism
} // namespace assembler
