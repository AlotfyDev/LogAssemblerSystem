#pragma once
#include "TContainerState.hpp"
#include "TDispatchExposureState.hpp"
#include "TReferenceValidityState.hpp"
#include "TRoundState.hpp"
#include "TSafePointState.hpp"

/*
    Compatibility shim:
    Most eviction guard helpers are owned by core state headers.
    These aliases preserve names used by the eviction component.
*/

namespace assembler {
namespace circulation_mechanism {

[[nodiscard]] constexpr bool eviction_safe_point_available(TSafePointState state) noexcept
{
    return safe_point_available(state);
}

[[nodiscard]] constexpr bool reference_cleared_for_eviction(TReferenceValidityState state) noexcept
{
    return reference_released(state);
}

[[nodiscard]] constexpr bool round_clear_for_eviction(TRoundState state) noexcept
{
    return round_release_ready(state) || state == TRoundState::idle;
}
} // namespace circulation_mechanism
} // namespace assembler
