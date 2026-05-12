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

#include <vector>

#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffResult.hpp"
#include "TLogApiCirculationIntegrationIssue.hpp"
#include "TLogApiCirculationSmokeAdmissionResult.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_integration {

struct TLogApiCirculationIntegrationSmokeResult final {
    assembler::log_level_api::communication_bindings::circulation_handoff::TLogApiCirculationHandoffResult handoff_result{};
    TLogApiCirculationSmokeAdmissionResult smoke_admission{};
    std::vector<TLogApiCirculationIntegrationIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (handoff_result.HasBlockingIssue()) return true;
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return handoff_result.IsAcceptedByContract()
            && smoke_admission.IsStubAdmitted()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_integration
