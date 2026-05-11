#pragma once
#include "TContainerState.hpp"
#include "TSafePointState.hpp"
#include "TReferenceValidityState.hpp"
#include "TRoundState.hpp"
#include "TDispatchExposureState.hpp"

namespace assembler {
namespace circulation_mechanism {

[[nodiscard]] constexpr bool eviction_safe_point_available(TSafePointState state) noexcept {
    return state == TSafePointState::available || state == TSafePointState::claimed;
}
[[nodiscard]] constexpr bool container_active_in_ingress(TContainerState state) noexcept {
    return state == TContainerState::ingress_round_member || state == TContainerState::receiving;
}
[[nodiscard]] constexpr bool container_active_in_dispatch(TContainerState state) noexcept {
    return state == TContainerState::dispatch_round_member || state == TContainerState::dispatch_exposed;
}
[[nodiscard]] constexpr bool container_eviction_state_candidate(TContainerState state) noexcept {
    return state == TContainerState::dispatch_candidate
        || state == TContainerState::dispatch_completed
        || state == TContainerState::reset_pending
        || state == TContainerState::inactive;
}
[[nodiscard]] constexpr bool reference_cleared_for_eviction(TReferenceValidityState state) noexcept {
    return state == TReferenceValidityState::consumed
        || state == TReferenceValidityState::expired
        || state == TReferenceValidityState::invalidated;
}
[[nodiscard]] constexpr bool round_clear_for_eviction(TRoundState state) noexcept {
    return state == TRoundState::closed || state == TRoundState::completed || state == TRoundState::aborted || state == TRoundState::idle;
}
[[nodiscard]] constexpr bool exposure_clear_for_eviction(TDispatchExposureState state) noexcept {
    return state == TDispatchExposureState::closed
        || state == TDispatchExposureState::release_pending
        || state == TDispatchExposureState::bridge_consumed;
}
} // namespace circulation_mechanism
} // namespace assembler
