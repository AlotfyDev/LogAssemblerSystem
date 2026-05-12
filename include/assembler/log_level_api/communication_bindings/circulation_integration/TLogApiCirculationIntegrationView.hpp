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

#include <string>

#include "TLogApiCirculationIntegrationSmokeRequest.hpp"
#include "TLogApiCirculationIntegrationSmokeResult.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_integration {

struct TLogApiCirculationIntegrationView final {
    std::string integration_id{};
    std::string integration_name{};
    std::string handoff_id{};
    std::string admission_ref{};
    bool request_ready{false};
    bool accepted{false};

    [[nodiscard]] static TLogApiCirculationIntegrationView From(
        const TLogApiCirculationIntegrationSmokeRequest& request,
        const TLogApiCirculationIntegrationSmokeResult& result
    ) {
        TLogApiCirculationIntegrationView view{};
        view.integration_id = request.config.id.ToString();
        view.integration_name = request.config.integration_name;
        view.handoff_id = request.handoff_request.id.ToString();
        view.admission_ref = result.smoke_admission.stub_admission_ref;
        view.request_ready = request.IsReady();
        view.accepted = result.IsAccepted();
        return view;
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration
