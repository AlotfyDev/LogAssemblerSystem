#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TModeratorState : std::uint8_t {
    uninitialized,
    idle,
    observing,
    preparing,
    reset_planned,
    resetting,
    ready_exposed,
    safe_point_confirmed,
    moderation_blocked,
    invariant_violation
};
[[nodiscard]] constexpr bool can_plan_reset(TModeratorState s) noexcept {
    return s == TModeratorState::idle || s == TModeratorState::observing || s == TModeratorState::safe_point_confirmed;
}
[[nodiscard]] constexpr bool can_expose_readiness(TModeratorState s) noexcept {
    return s == TModeratorState::ready_exposed || s == TModeratorState::safe_point_confirmed;
}
[[nodiscard]] constexpr bool is_blocked(TModeratorState s) noexcept {
    return s == TModeratorState::moderation_blocked || s == TModeratorState::invariant_violation;
}
} // namespace circulation_mechanism
} // namespace assembler
