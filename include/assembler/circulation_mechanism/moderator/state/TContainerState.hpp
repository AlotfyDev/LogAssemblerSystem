#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TContainerState : std::uint8_t {
    default_empty,
    ingress_ready,
    ingress_round_member,
    receiving,
    filled_or_closed,
    dispatch_candidate,
    dispatch_round_member,
    dispatch_exposed,
    dispatch_completed,
    reset_pending,
    under_moderation,
    inactive,
    evicted,
    faulted
};
[[nodiscard]] constexpr bool reset_eligible(TContainerState s) noexcept {
    return s == TContainerState::dispatch_completed || s == TContainerState::reset_pending;
}
[[nodiscard]] constexpr bool ingress_ready_candidate(TContainerState s) noexcept {
    return s == TContainerState::default_empty || s == TContainerState::ingress_ready;
}
[[nodiscard]] constexpr bool unsafe_active_container(TContainerState s) noexcept {
    return s == TContainerState::ingress_round_member || s == TContainerState::receiving || s == TContainerState::dispatch_round_member || s == TContainerState::dispatch_exposed;
}
} // namespace circulation_mechanism
} // namespace assembler
