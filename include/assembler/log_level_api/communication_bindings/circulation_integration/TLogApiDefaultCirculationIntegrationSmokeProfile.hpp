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

#include "TLogApiCirculationIntegrationSmokeConfig.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_integration {

struct TLogApiDefaultCirculationIntegrationSmokeProfile final {
    [[nodiscard]] static TLogApiCirculationIntegrationSmokeConfig Make() {
        TLogApiCirculationIntegrationSmokeConfig config{};
        config.id = TLogApiCirculationIntegrationId{1};
        config.status = TLogApiCirculationIntegrationStatus::Ready;
        config.integration_name = "default.logapi.circulation.smoke.integration";
        config.accept_contract_ready_handoff = true;
        return config;
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration
