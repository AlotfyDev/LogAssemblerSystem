#pragma once
#include "TReadSideBackpressureProfileId.hpp"
#include "TReadSideBackpressureMode.hpp"
#include "TReadSideBackpressureState.hpp"
#include "TBackpressureDecisionKind.hpp"
#include "../post_bridge_capacity/TPostBridgeCapacityProfile.hpp"

/*
    TReadSideBackpressureProfile.hpp

    Current responsibility:
        Production read-side backpressure decision contract.

    Production capabilities:
        - mode/state classification
        - capacity-sensitive decision
        - receiver-delay release mode
        - retry-pressure routing mode
        - receiver-controlled delegation mode

    Explicit non-ownership:
        - Does not throttle itself.
        - Does not mutate capacity profile.
        - Does not schedule retry.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideBackpressureProfile final {
    TReadSideBackpressureProfileId profile_id{};
    TReadSideBackpressureMode mode{TReadSideBackpressureMode::disabled};
    TReadSideBackpressureState state{TReadSideBackpressureState::none};
    bool receiver_may_delay_release{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return profile_id.is_valid();
    }

    [[nodiscard]] constexpr bool backpressure_enabled() const noexcept {
        return mode != TReadSideBackpressureMode::disabled;
    }

    [[nodiscard]] constexpr bool pressure_active() const noexcept {
        return state == TReadSideBackpressureState::pressure_detected
            || state == TReadSideBackpressureState::throttling
            || state == TReadSideBackpressureState::blocked;
    }

    [[nodiscard]] constexpr TBackpressureDecisionKind decide(TPostBridgeCapacityProfile capacity) const noexcept {
        if (!backpressure_enabled()) return TBackpressureDecisionKind::allow_admission;
        if (!capacity.is_valid() || capacity.capacity_insufficient()) {
            if (mode == TReadSideBackpressureMode::observe_only) return TBackpressureDecisionKind::observe_only;
            if (mode == TReadSideBackpressureMode::block_admission) return TBackpressureDecisionKind::block_admission;
            if (mode == TReadSideBackpressureMode::delay_release) return TBackpressureDecisionKind::delay_release;
            if (mode == TReadSideBackpressureMode::retry_pressure) return TBackpressureDecisionKind::route_to_retry;
            if (mode == TReadSideBackpressureMode::receiver_controlled) return TBackpressureDecisionKind::delegate_to_receiver;
        }
        if (pressure_active() && mode == TReadSideBackpressureMode::block_admission) return TBackpressureDecisionKind::block_admission;
        return TBackpressureDecisionKind::allow_admission;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
