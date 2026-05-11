#pragma once
#include "TReceiverAdmissionDecisionKind.hpp"
#include "TReceiverAdmissionRequestId.hpp"
#include "../backpressure_runtime/TReceiverBackpressureGateStatus.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/failed_dispatch/TFailedDispatchKind.hpp"

/*
    TReceiverAdmissionDecision.hpp

    Current responsibility:
        Carries decision for a receiver admission request.

    Non-ownership:
        Decision does not execute receiver or retry.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReceiverAdmissionDecision final {
    TReceiverAdmissionRequestId request_id{};
    TReceiverAdmissionDecisionKind decision{TReceiverAdmissionDecisionKind::not_evaluated};
    TReceiverBackpressureGateStatus gate_status{TReceiverBackpressureGateStatus::undefined};
    read_side_circulation_profile::TFailedDispatchKind failure_kind{read_side_circulation_profile::TFailedDispatchKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return request_id.is_valid();
    }

    [[nodiscard]] constexpr bool accepted() const noexcept {
        return decision == TReceiverAdmissionDecisionKind::accept;
    }

    [[nodiscard]] constexpr bool rejected() const noexcept {
        return !accepted();
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
