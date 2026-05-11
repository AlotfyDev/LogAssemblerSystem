#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TBundleAgentState : std::uint8_t {
    uninitialized,
    stable,
    horizontal_scaling_pending,
    vertical_scaling_pending,
    waiting_for_safe_point,
    profile_switch_ready,
    profile_switch_applied,
    invariant_violation
};
[[nodiscard]] constexpr bool is_stable(TBundleAgentState s) noexcept {
    return s == TBundleAgentState::stable || s == TBundleAgentState::profile_switch_applied;
}
[[nodiscard]] constexpr bool is_scaling_pending(TBundleAgentState s) noexcept {
    return s == TBundleAgentState::horizontal_scaling_pending || s == TBundleAgentState::vertical_scaling_pending || s == TBundleAgentState::waiting_for_safe_point || s == TBundleAgentState::profile_switch_ready;
}
} // namespace circulation_mechanism
} // namespace assembler
