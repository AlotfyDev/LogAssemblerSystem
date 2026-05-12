#pragma once

/*
    LOGAPI-W26 — Circulation Integration Smoke Skeleton

    Responsibility:
        Define a minimal smoke-level integration skeleton that connects a ready
        Log Level API envelope exposure and the W25 circulation handoff contract
        to a stub circulation admission result.

    Boundary:
        This wave does not implement the circulation engine, placement, slots,
        queues, waiting lists, round managers, dispatcher, bridge orchestration,
        protocols, or real admission behavior.

    Doctrine:
        This is an integration skeleton, not production circulation.
        It proves boundary compatibility only.
*/

#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffContract.hpp"

#include "TLogApiCirculationIntegrationSmokeRequest.hpp"
#include "TLogApiCirculationIntegrationSmokeResult.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_integration {

/*
    Smoke integration skeleton.

    It submits the W25 handoff request to the W25 contract and, if accepted,
    produces a stub admission result. No real circulation behavior is executed.
*/
class TLogApiCirculationIntegrationSmokeSkeleton final {
public:
    [[nodiscard]] static TLogApiCirculationIntegrationSmokeResult Run(
        const TLogApiCirculationIntegrationSmokeRequest& request
    ) {
        using namespace assembler::log_level_api::communication_bindings::circulation_handoff;

        TLogApiCirculationIntegrationSmokeResult result{};

        if (!request.IsReady()) {
            result.issues.push_back({
                "LOGAPI_CIRCULATION_SMOKE_REQUEST_NOT_READY",
                "Smoke integration request requires ready config and ready W25 handoff request.",
                true
            });
            result.smoke_admission.status = TLogApiCirculationSmokeAdmissionStatus::StubRejected;
            return result;
        }

        result.handoff_result = TLogApiCirculationHandoffContract::Submit(request.handoff_request);

        if (!result.handoff_result.IsAcceptedByContract()) {
            result.issues.push_back({
                "LOGAPI_CIRCULATION_HANDOFF_CONTRACT_REJECTED",
                "W25 handoff contract rejected the request.",
                true
            });
            result.smoke_admission.status = TLogApiCirculationSmokeAdmissionStatus::StubRejected;
            return result;
        }

        if (!request.config.accept_contract_ready_handoff) {
            result.issues.push_back({
                "LOGAPI_CIRCULATION_SMOKE_CONFIG_REJECTED",
                "Smoke config is set to reject contract-ready handoff.",
                true
            });
            result.smoke_admission.status = TLogApiCirculationSmokeAdmissionStatus::StubRejected;
            return result;
        }

        result.smoke_admission.status = TLogApiCirculationSmokeAdmissionStatus::StubAdmitted;
        result.smoke_admission.stub_admission_ref =
            "stub-admission-for-" + result.handoff_result.token.ToString();
        result.smoke_admission.note =
            "Stub admission only; no circulation placement was performed.";

        return result;
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration
