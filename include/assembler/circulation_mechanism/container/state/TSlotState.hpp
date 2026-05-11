#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TSlotState : std::uint8_t {
    empty, reserved_for_ingress, occupied, sealed, dispatch_ready, dispatch_exposed, released, recyclable, faulted
};
[[nodiscard]] constexpr bool is_resident(TSlotState s) noexcept {
    return s == TSlotState::occupied || s == TSlotState::sealed || s == TSlotState::dispatch_ready || s == TSlotState::dispatch_exposed;
}
[[nodiscard]] constexpr bool is_dispatch_ready(TSlotState s) noexcept {
    return s == TSlotState::sealed || s == TSlotState::dispatch_ready;
}
} // namespace circulation_mechanism
} // namespace assembler
