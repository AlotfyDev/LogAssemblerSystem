#pragma once

/*
    LOGAPI-W07 — Envelope Carrier

    This header belongs to the Log Level API envelope carrier layer.

    Responsibility:
        Define the Log Level Envelope carrier and its compositional blocks:
        envelope identity/header/status, content reference, metadata block reference,
        stabilized timestamp, validation evidence reference, envelope view, and
        carrier result/report structures.

    Boundary:
        The envelope is a carrier, not an assembler.
        This wave must not define envelope assembly algorithms, concrete schemas,
        concrete validators, metadata injection logic, timestamp clock acquisition,
        API consuming behavior, communication bindings, circulation handoff, or
        policy assignment.

    Doctrine:
        Content, metadata struct, and stabilized timestamp remain independent
        until the envelope assembler composes them into a Log Level Envelope.
*/

#include "assembler/log_level_api/validator/TLogApiValidationResult.hpp"

namespace assembler::log_level_api::envelope {

/*
    Optional validation evidence block.

    If validation is not required by the active profile, this block may be absent.
*/
struct TLogApiEnvelopeValidationBlock final {
    assembler::log_level_api::validator::TLogApiValidationResult validation{};
    bool present{false};

    [[nodiscard]] bool IsAcceptedWhenPresent() const noexcept {
        return !present || validation.IsAccepted();
    }
};

} // namespace assembler::log_level_api::envelope
