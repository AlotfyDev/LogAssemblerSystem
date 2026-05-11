#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TContainerState : std::uint8_t {
    default_empty, ingress_ready, ingress_round_member, receiving, filled_or_closed, dispatch_candidate,
    dispatch_round_member, dispatch_exposed, dispatch_completed, reset_pending, under_moderation, inactive, evicted, faulted
};
[[nodiscard]] constexpr bool can_join_ingress_round(TContainerState s) noexcept {
    return s == TContainerState::default_empty || s == TContainerState::ingress_ready;
}
[[nodiscard]] constexpr bool can_join_dispatch_round(TContainerState s) noexcept {
    return s == TContainerState::dispatch_candidate;
}
[[nodiscard]] constexpr bool is_container_terminal(TContainerState s) noexcept {
    return s == TContainerState::inactive || s == TContainerState::evicted || s == TContainerState::faulted;
}
[[nodiscard]] constexpr bool can_transition(TContainerState from, TContainerState to) noexcept {
    if (from == to) return true;
    switch(from) {
        case TContainerState::default_empty: return to == TContainerState::ingress_ready || to == TContainerState::inactive || to == TContainerState::faulted;
        case TContainerState::ingress_ready: return to == TContainerState::ingress_round_member || to == TContainerState::inactive || to == TContainerState::faulted;
        case TContainerState::ingress_round_member: return to == TContainerState::receiving || to == TContainerState::filled_or_closed || to == TContainerState::faulted;
        case TContainerState::receiving: return to == TContainerState::filled_or_closed || to == TContainerState::faulted;
        case TContainerState::filled_or_closed: return to == TContainerState::dispatch_candidate || to == TContainerState::reset_pending || to == TContainerState::faulted;
        case TContainerState::dispatch_candidate: return to == TContainerState::dispatch_round_member || to == TContainerState::evicted || to == TContainerState::faulted;
        case TContainerState::dispatch_round_member: return to == TContainerState::dispatch_exposed || to == TContainerState::dispatch_completed || to == TContainerState::faulted;
        case TContainerState::dispatch_exposed: return to == TContainerState::dispatch_completed || to == TContainerState::faulted;
        case TContainerState::dispatch_completed: return to == TContainerState::reset_pending || to == TContainerState::evicted || to == TContainerState::faulted;
        case TContainerState::reset_pending: return to == TContainerState::under_moderation || to == TContainerState::faulted;
        case TContainerState::under_moderation: return to == TContainerState::default_empty || to == TContainerState::faulted;
        case TContainerState::inactive: return to == TContainerState::default_empty;
        default: return false;
    }
}
} // namespace circulation_mechanism
} // namespace assembler
