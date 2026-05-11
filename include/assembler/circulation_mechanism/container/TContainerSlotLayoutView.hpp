#pragma once
#include <cstdint>
#include <cstddef>
namespace assembler {
namespace circulation_mechanism {

struct TContainerSlotLayoutView final {
    std::uint32_t slots_per_container{0};
    std::uint32_t slot_payload_capacity_units{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return slots_per_container > 0 && slot_payload_capacity_units > 0; }
    [[nodiscard]] constexpr std::uint64_t total_units() const noexcept {
        return static_cast<std::uint64_t>(slots_per_container) * static_cast<std::uint64_t>(slot_payload_capacity_units);
    }
};
} // namespace circulation_mechanism
} // namespace assembler
