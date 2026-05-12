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

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"

namespace assembler::log_level_api::envelope {

/*
    Envelope content block.

    It holds content reference only. It does not hold schema definitions,
    metadata fields, validator binding, or timestamp rules.
*/
struct TLogApiEnvelopeContentBlock final {
    assembler::log_level_api::content::TLogApiContentInputRef content{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return content.IsPresent();
    }
};

} // namespace assembler::log_level_api::envelope
