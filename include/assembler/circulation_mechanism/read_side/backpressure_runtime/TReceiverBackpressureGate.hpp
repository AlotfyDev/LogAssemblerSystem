#pragma once
#include "TReceiverBackpressureGateId.hpp"
#include "TReceiverBackpressureGateStatus.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/backpressure/TReadSideBackpressureProfile.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/post_bridge_capacity/TPostBridgeCapacityProfile.hpp"

/*
    TReceiverBackpressureGate.hpp

    Current responsibility:
        Evaluates receiver-side backpressure and converts it into admission-facing gate status.

    Production capabilities:
        - consumes read-side backpressure profile
        - consumes post-bridge capacity profile
        - computes gate status
        - does not execute throttling or receiver operations

    Explicit non-ownership:
        - Does not mutate capacity.
        - Does not block threads.
        - Does not call receiver.
        - Does not schedule retry.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReceiverBackpressureGate final {
    TReceiverBackpressureGateId gate_id{};
    read_side_circulation_profile::TReadSideBackpressureProfile profile{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return gate_id.is_valid() && profile.is_valid();
    }

    [[nodiscard]] constexpr TReceiverBackpressureGateStatus evaluate(read_side_circulation_profile::TPostBridgeCapacityProfile capacity) const noexcept {
        if (!is_valid()) return TReceiverBackpressureGateStatus::faulted;

        // Pressure mode may express a receiver-side policy even when capacity is still available.
        // This keeps retry/backpressure semantics from being reduced to capacity exhaustion only.
        if (profile.pressure_active()) {
            if (profile.mode == read_side_circulation_profile::TReadSideBackpressureMode::observe_only) {
                return TReceiverBackpressureGateStatus::pressure_observed;
            }
            if (profile.mode == read_side_circulation_profile::TReadSideBackpressureMode::block_admission) {
                return TReceiverBackpressureGateStatus::admission_blocked;
            }
            if (profile.mode == read_side_circulation_profile::TReadSideBackpressureMode::delay_release) {
                return TReceiverBackpressureGateStatus::release_delayed;
            }
            if (profile.mode == read_side_circulation_profile::TReadSideBackpressureMode::retry_pressure) {
                return TReceiverBackpressureGateStatus::retry_pressure;
            }
            if (profile.mode == read_side_circulation_profile::TReadSideBackpressureMode::receiver_controlled) {
                return TReceiverBackpressureGateStatus::delegated;
            }
        }

        const auto decision = profile.decide(capacity);
        switch (decision) {
            case read_side_circulation_profile::TBackpressureDecisionKind::allow_admission:
                return TReceiverBackpressureGateStatus::ready;
            case read_side_circulation_profile::TBackpressureDecisionKind::observe_only:
                return TReceiverBackpressureGateStatus::pressure_observed;
            case read_side_circulation_profile::TBackpressureDecisionKind::block_admission:
                return TReceiverBackpressureGateStatus::admission_blocked;
            case read_side_circulation_profile::TBackpressureDecisionKind::delay_release:
                return TReceiverBackpressureGateStatus::release_delayed;
            case read_side_circulation_profile::TBackpressureDecisionKind::route_to_retry:
                return TReceiverBackpressureGateStatus::retry_pressure;
            case read_side_circulation_profile::TBackpressureDecisionKind::delegate_to_receiver:
                return TReceiverBackpressureGateStatus::delegated;
            default:
                return TReceiverBackpressureGateStatus::faulted;
        }
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
