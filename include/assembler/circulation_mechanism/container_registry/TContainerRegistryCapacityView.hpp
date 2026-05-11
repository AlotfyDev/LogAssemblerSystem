#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

struct TContainerRegistryCapacityView final {
    std::uint32_t capacity{0};
    std::uint32_t active_count{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return capacity > 0U && active_count <= capacity; }
    [[nodiscard]] constexpr std::uint32_t remaining() const noexcept { return is_valid() ? capacity - active_count : 0U; }
    [[nodiscard]] constexpr bool full() const noexcept { return is_valid() && active_count == capacity; }
};
} // namespace circulation_mechanism
} // namespace assembler
