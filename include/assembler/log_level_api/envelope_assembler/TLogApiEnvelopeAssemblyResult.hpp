#pragma once

/*
    LOGAPI-W08 — Envelope Assembler Families

    This header belongs to the Log Level API envelope assembler family layer.

    Responsibility:
        Define envelope assembly input, assembly profile, assembly result, and
        two distinct assembler families:
            - plain envelope assembler
            - validator-composed envelope assembler

    Boundary:
        The assembler composes already prepared material into an envelope.
        It must not define content schemas, metadata field definitions, timestamp
        stabilization rules, concrete validators, API consuming behavior,
        communication bindings, circulation handoff, or policy assignment.

    Hot-path doctrine:
        Plain assembly and validator-composed assembly are separate types.
        The system must not branch inside one assembler flow to ask whether a
        validator exists. The assembler family is selected before the hot path.
*/

#include <vector>

#include "assembler/log_level_api/envelope/TLogApiEnvelopeResult.hpp"

#include "TLogApiEnvelopeAssemblyIssue.hpp"

namespace assembler::log_level_api::envelope_assembler {

struct TLogApiEnvelopeAssemblyResult final {
    assembler::log_level_api::envelope::TLogApiEnvelopeResult envelope_result{};
    std::vector<TLogApiEnvelopeAssemblyIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return envelope_result.HasBlockingIssue();
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return envelope_result.IsAccepted() && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::envelope_assembler
