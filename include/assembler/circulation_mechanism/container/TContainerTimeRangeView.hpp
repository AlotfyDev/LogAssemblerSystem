#pragma once
#include "TContainerTimeRange.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TContainerTimeRangeView final {
    TContainerTimeRange range{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return range.is_valid(); }
    [[nodiscard]] constexpr bool has_value() const noexcept { return range.has_value; }
};
} // namespace circulation_mechanism
} // namespace assembler
