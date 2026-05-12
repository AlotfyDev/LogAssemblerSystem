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

#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffRequest.hpp"
#include "TLogApiCirculationIntegrationSmokeConfig.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_integration {

struct TLogApiCirculationIntegrationSmokeRequest final {
    TLogApiCirculationIntegrationSmokeConfig config{};
    assembler::log_level_api::communication_bindings::circulation_handoff::TLogApiCirculationHandoffRequest handoff_request{};

    [[nodiscard]] bool IsReady() const noexcept {
        return config.IsReady() && handoff_request.IsReady();
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration
