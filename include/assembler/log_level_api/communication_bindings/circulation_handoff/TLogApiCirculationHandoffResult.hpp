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

#include <vector>

#include "TLogApiCirculationAdmissionToken.hpp"
#include "TLogApiCirculationHandoffIssue.hpp"
#include "TLogApiCirculationHandoffStatus.hpp"

namespace assembler::log_level_api::communication_bindings::circulation_handoff {

struct TLogApiCirculationHandoffResult final {
    TLogApiCirculationHandoffStatus status{TLogApiCirculationHandoffStatus::Unknown};
    TLogApiCirculationAdmissionToken token{};
    std::vector<TLogApiCirculationHandoffIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAcceptedByContract() const noexcept {
        return status == TLogApiCirculationHandoffStatus::AcceptedByContract
            && token.IsValid()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::communication_bindings::circulation_handoff
