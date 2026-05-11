#pragma once
#include "TContainerState.hpp"
#include "TDispatchExposureState.hpp"
#include "TReferenceValidityState.hpp"
#include "TRoundState.hpp"
#include "TSafePointState.hpp"

namespace assembler {
namespace circulation_mechanism {

[[nodiscard]] constexpr bool safe_point_available(TSafePointState state) noexcept {
    return state == TSafePointState::available || state == TSafePointState::claimed;
}
[[nodiscard]] constexpr bool reference_released(TReferenceValidityState state) noexcept {
    return state == TReferenceValidityState::consumed || state == TReferenceValidityState::expired || state == TReferenceValidityState::invalidated;
}
[[nodiscard]] constexpr bool exposure_release_ready(TDispatchExposureState state) noexcept {
    return state == TDispatchExposureState::bridge_consumed || state == TDispatchExposureState::release_pending || state == TDispatchExposureState::closed;
}
[[nodiscard]] constexpr bool container_release_ready(TContainerState state) noexcept {
    return state == TContainerState::dispatch_completed || state == TContainerState::reset_pending;
}
[[nodiscard]] constexpr bool round_release_ready(TRoundState state) noexcept {
    return state == TRoundState::closed || state == TRoundState::completed || state == TRoundState::aborted;
}
} // namespace circulation_mechanism
} // namespace assembler
