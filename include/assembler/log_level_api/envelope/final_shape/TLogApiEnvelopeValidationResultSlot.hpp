#pragma once

/*
    LOGAPI-W23 — Envelope Final Shape And Identity

    Responsibility:
        Define final envelope identity/header shape, official envelope slots,
        validation result slot, readiness view, and final envelope carrier.

    Boundary:
        The envelope is a carrier and identity surface, not an assembler and not
        a policy decision maker. A validation result slot records valid/invalid
        evidence, but accepting or rejecting a payload based on that result is a
        separate user/policy concern.

    Doctrine:
        Envelope = identity/header + content slot + metadata slot + timestamp slot
                   + validation result slot.
*/

#include "assembler/log_level_api/validator/TLogApiValidationResult.hpp"

#include "TLogApiValidationOutcomeKind.hpp"

namespace assembler::log_level_api::envelope::final_shape {

/*
    Validation result slot.

    This slot records validation result/evidence only.
    It does not decide payload acceptance/rejection.
*/
struct TLogApiEnvelopeValidationResultSlot final {
    TLogApiValidationOutcomeKind outcome{TLogApiValidationOutcomeKind::NotEvaluated};
    assembler::log_level_api::validator::TLogApiValidationResult validation_result{};
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept {
        return present;
    }

    [[nodiscard]] bool IsValidOutcome() const noexcept {
        if (!present) return outcome == TLogApiValidationOutcomeKind::NotEvaluated;
        return outcome == TLogApiValidationOutcomeKind::Valid
            || outcome == TLogApiValidationOutcomeKind::Invalid
            || outcome == TLogApiValidationOutcomeKind::NotEvaluated;
    }

    [[nodiscard]] static TLogApiEnvelopeValidationResultSlot NotEvaluated() {
        TLogApiEnvelopeValidationResultSlot slot{};
        slot.outcome = TLogApiValidationOutcomeKind::NotEvaluated;
        slot.present = false;
        return slot;
    }

    [[nodiscard]] static TLogApiEnvelopeValidationResultSlot FromValidationResult(
        const assembler::log_level_api::validator::TLogApiValidationResult& result
    ) {
        TLogApiEnvelopeValidationResultSlot slot{};
        slot.validation_result = result;
        slot.present = true;
        slot.outcome = result.IsAccepted()
            ? TLogApiValidationOutcomeKind::Valid
            : TLogApiValidationOutcomeKind::Invalid;
        return slot;
    }
};

} // namespace assembler::log_level_api::envelope::final_shape
