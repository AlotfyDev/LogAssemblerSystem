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

#include "TLogApiEnvelopeContentBlock.hpp"
#include "TLogApiEnvelopeHeader.hpp"
#include "TLogApiEnvelopeMetadataBlock.hpp"
#include "TLogApiEnvelopeTimestampBlock.hpp"
#include "TLogApiEnvelopeValidationBlock.hpp"

namespace assembler::log_level_api::envelope {

/*
    Log Level Envelope carrier.

    The envelope is the first object allowed to aggregate:
        content,
        metadata struct,
        stabilized timestamp,
        optional validation evidence.

    It does not assemble itself.
*/
struct TLogApiEnvelope final {
    TLogApiEnvelopeHeader header{};
    TLogApiEnvelopeContentBlock content{};
    TLogApiEnvelopeMetadataBlock metadata{};
    TLogApiEnvelopeTimestampBlock timestamp{};
    TLogApiEnvelopeValidationBlock validation{};

    [[nodiscard]] bool IsComplete() const noexcept {
        return header.IsPresent()
            && content.IsPresent()
            && metadata.IsPresent()
            && timestamp.IsPresent()
            && validation.IsAcceptedWhenPresent();
    }
};

} // namespace assembler::log_level_api::envelope
