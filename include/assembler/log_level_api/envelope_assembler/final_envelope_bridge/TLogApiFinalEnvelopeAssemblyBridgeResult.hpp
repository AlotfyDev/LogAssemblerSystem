#pragma once

/*
    LOGAPI-EXT-W02 — Final Envelope Assembler Bridge

    Responsibility:
        Bridge the W08 envelope assembler family inputs/profiles into the W23
        final envelope shape, producing TLogApiFinalEnvelopeResult.

    Boundary:
        This wave does not implement new parser behavior, metadata injection,
        timestamp stabilization, circulation handoff, policy assignment, bridge
        orchestration, or receiver behavior.

    Doctrine:
        W08 assembly profile remains the assembler-family selection surface.
        W23 final envelope remains the target carrier shape.
        Validation result slot remains evidence only; it does not decide payload
        acceptance or rejection.
*/

#include <vector>

#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelopeResult.hpp"

#include "TLogApiFinalEnvelopeAssemblerBridgeIssue.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeStatus.hpp"

namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge {

struct TLogApiFinalEnvelopeAssemblyBridgeResult final {
    TLogApiFinalEnvelopeAssemblerBridgeStatus status{TLogApiFinalEnvelopeAssemblerBridgeStatus::Unknown};
    assembler::log_level_api::envelope::final_shape::TLogApiFinalEnvelopeResult final_envelope_result{};
    std::vector<TLogApiFinalEnvelopeAssemblerBridgeIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (final_envelope_result.HasBlockingIssue()) return true;
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return status == TLogApiFinalEnvelopeAssemblerBridgeStatus::Bridged
            && final_envelope_result.IsAccepted()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge
