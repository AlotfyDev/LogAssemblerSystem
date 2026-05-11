#pragma once
#include "TReceiverAdmissionControllerId.hpp"
#include "TReceiverAdmissionRequest.hpp"
#include "TReceiverAdmissionDecision.hpp"
#include "../backpressure_runtime/TReceiverBackpressureGate.hpp"

/*
    TReceiverAdmissionController.hpp

    Delivery:
        CME-READSIDE-PROD-W03 — ReadSide Backpressure And Receiver Admission Runtime

    Current responsibility:
        Production decision layer for read-side receiver admission.

    Production capabilities:
        - validates admission request
        - evaluates backpressure gate
        - accepts when receiver/capacity/gate allow
        - routes to retry/failed-dispatch/delay/manual-review decisions
        - emits decision surface without invoking receiver

    Explicit non-ownership:
        - Does not call receiver.
        - Does not enqueue retry by itself.
        - Does not persist payload.
        - Does not mutate PreBridge runtime.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReceiverAdmissionController final {
    TReceiverAdmissionControllerId controller_id{};
    TReceiverBackpressureGate gate{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return controller_id.is_valid() && gate.is_valid();
    }

    [[nodiscard]] constexpr TReceiverAdmissionDecision decide(TReceiverAdmissionRequest request) const noexcept {
        if (!is_valid() || !request.is_valid()) {
            return TReceiverAdmissionDecision{
                request.request_id,
                TReceiverAdmissionDecisionKind::reject_invalid_request,
                TReceiverBackpressureGateStatus::faulted,
                request.failure_hint
            };
        }

        if (!request.capacity.receiver_has_room()) {
            return TReceiverAdmissionDecision{
                request.request_id,
                TReceiverAdmissionDecisionKind::reject_no_capacity,
                TReceiverBackpressureGateStatus::admission_blocked,
                read_side_circulation_profile::TFailedDispatchKind::receiver_not_ready
            };
        }

        if (!request.receiver_ready()) {
            return TReceiverAdmissionDecision{
                request.request_id,
                TReceiverAdmissionDecisionKind::reject_receiver_not_ready,
                TReceiverBackpressureGateStatus::faulted,
                read_side_circulation_profile::TFailedDispatchKind::receiver_not_ready
            };
        }

        const auto gate_status = gate.evaluate(request.capacity);
        switch (gate_status) {
            case TReceiverBackpressureGateStatus::ready:
            case TReceiverBackpressureGateStatus::pressure_observed:
                return TReceiverAdmissionDecision{request.request_id, TReceiverAdmissionDecisionKind::accept, gate_status, request.failure_hint};
            case TReceiverBackpressureGateStatus::release_delayed:
                return TReceiverAdmissionDecision{request.request_id, TReceiverAdmissionDecisionKind::delay_for_backpressure, gate_status, request.failure_hint};
            case TReceiverBackpressureGateStatus::retry_pressure:
                return TReceiverAdmissionDecision{request.request_id, TReceiverAdmissionDecisionKind::route_to_retry, gate_status, read_side_circulation_profile::TFailedDispatchKind::receiver_not_ready};
            case TReceiverBackpressureGateStatus::admission_blocked:
                return TReceiverAdmissionDecision{request.request_id, TReceiverAdmissionDecisionKind::reject_no_capacity, gate_status, read_side_circulation_profile::TFailedDispatchKind::receiver_not_ready};
            case TReceiverBackpressureGateStatus::delegated:
                return TReceiverAdmissionDecision{request.request_id, TReceiverAdmissionDecisionKind::manual_review, gate_status, request.failure_hint};
            default:
                return TReceiverAdmissionDecision{request.request_id, TReceiverAdmissionDecisionKind::reject_invalid_request, gate_status, request.failure_hint};
        }
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
