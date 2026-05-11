#pragma once
#include "TContainerStateView.hpp"
#include "TContainerSlotLayoutView.hpp"
#include "TContainerTimeRangeView.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TContainerView final {
    TContainerStateView state_view{};
    TContainerSlotLayoutView layout_view{};
    TContainerTimeRangeView time_range_view{};
    std::uint32_t occupied_slots{0};
    std::uint32_t dispatch_ready_slots{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return state_view.is_valid() && layout_view.is_valid() && time_range_view.is_valid(); }
    [[nodiscard]] constexpr bool empty() const noexcept { return occupied_slots == 0; }
};
} // namespace circulation_mechanism
} // namespace assembler
