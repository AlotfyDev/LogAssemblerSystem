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

#include "TLogApiCirculationIntegrationId.hpp"
#include "TLogApiCirculationIntegrationStatus.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_integration {

struct TLogApiCirculationIntegrationSmokeConfig final {
    TLogApiCirculationIntegrationId id{};
    TLogApiCirculationIntegrationStatus status{TLogApiCirculationIntegrationStatus::Unknown};

    std::string integration_name{"default.logapi.circulation.smoke.integration"};
    bool accept_contract_ready_handoff{true};

    [[nodiscard]] bool IsReady() const noexcept {
        return id.IsValid()
            && (status == TLogApiCirculationIntegrationStatus::Ready
                || status == TLogApiCirculationIntegrationStatus::SmokeAccepted)
            && !integration_name.empty();
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration
