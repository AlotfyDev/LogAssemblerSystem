#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TContainerState : std::uint8_t {
    default_empty, ingress_ready, ingress_round_member, receiving, filled_or_closed,
    dispatch_candidate, dispatch_round_member, dispatch_exposed, dispatch_completed,
    reset_pending, under_moderation, inactive, evicted, faulted
};
[[nodiscard]] constexpr bool ingress_round_eligible(TContainerState s) noexcept {
    return s == TContainerState::default_empty || s == TContainerState::ingress_ready;
}
[[nodiscard]] constexpr bool dispatch_round_eligible(TContainerState s) noexcept {
    return s == TContainerState::dispatch_candidate;
}
} // namespace circulation_mechanism
} // namespace assembler
