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

#include <string>

#include "TLogApiEnvelopeId.hpp"
#include "TLogApiEnvelopeStatus.hpp"

namespace assembler::log_level_api::envelope {

struct TLogApiEnvelopeHeader final {
    TLogApiEnvelopeId envelope_id{};
    TLogApiEnvelopeStatus status{TLogApiEnvelopeStatus::Unknown};

    std::string envelope_profile_name{};
    std::string content_profile_name{};
    std::string metadata_profile_name{};
    std::string timestamp_profile_name{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return envelope_id.IsValid()
            && status != TLogApiEnvelopeStatus::Unknown
            && !envelope_profile_name.empty()
            && !content_profile_name.empty();
    }
};

} // namespace assembler::log_level_api::envelope
