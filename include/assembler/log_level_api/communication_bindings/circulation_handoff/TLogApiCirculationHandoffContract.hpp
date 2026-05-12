#pragma once

/*
    LOGAPI-W25 — Circulation Handoff Contract

    Responsibility:
        Define the handoff contract from Log Level API envelope exposure toward
        the future circulation intake/admission surface.

    Boundary:
        This wave defines request/result/admission contract carriers only.
        It does not implement circulation engine behavior, placement, slots,
        queues, waiting lists, bridge orchestration, protocol execution, envelope
        assembly, validators, timestamp stabilization, metadata injection, or
        policy assignment.

    Doctrine:
        Log Level API exposes a ready envelope.
        Circulation owns admission and placement.
        This contract bridges readiness to future circulation intake without
        leaking circulation internals into Log Level API.
*/

#include "TLogApiCirculationHandoffRequest.hpp"
#include "TLogApiCirculationHandoffResult.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_handoff {

/*
    Handoff contract gate.

    This gate validates that the envelope exposure is ready and that the target
    descriptor is compatible with logapi.final_envelope material.

    It does not perform circulation admission or placement.
*/
class TLogApiCirculationHandoffContract final {
public:
    [[nodiscard]] static TLogApiCirculationHandoffResult Submit(
        const TLogApiCirculationHandoffRequest& request
    ) {
        TLogApiCirculationHandoffResult result{};

        if (!request.IsReady()) {
            result.status = TLogApiCirculationHandoffStatus::RejectedByContract;
            result.issues.push_back({
                "LOGAPI_CIRCULATION_HANDOFF_REQUEST_NOT_READY",
                "Handoff request requires ready envelope exposure and resolved circulation target descriptor.",
                true
            });
            return result;
        }

        result.status = TLogApiCirculationHandoffStatus::AcceptedByContract;
        result.token = TLogApiCirculationAdmissionToken{request.id.value};
        return result;
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_handoff
