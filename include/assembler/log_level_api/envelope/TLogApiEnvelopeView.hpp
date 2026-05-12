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

#include "TLogApiEnvelope.hpp"

namespace assembler::log_level_api::envelope {

struct TLogApiEnvelopeView final {
    std::string envelope_id{};
    std::string envelope_profile_name{};
    std::string content_profile_name{};
    std::string metadata_profile_name{};
    std::string timestamp_profile_name{};
    bool has_content{false};
    bool has_metadata{false};
    bool has_timestamp{false};
    bool has_validation{false};
    bool complete{false};

    [[nodiscard]] static TLogApiEnvelopeView From(const TLogApiEnvelope& e) {
        TLogApiEnvelopeView view{};
        view.envelope_id = e.header.envelope_id.ToString();
        view.envelope_profile_name = e.header.envelope_profile_name;
        view.content_profile_name = e.header.content_profile_name;
        view.metadata_profile_name = e.header.metadata_profile_name;
        view.timestamp_profile_name = e.header.timestamp_profile_name;
        view.has_content = e.content.IsPresent();
        view.has_metadata = e.metadata.IsPresent();
        view.has_timestamp = e.timestamp.IsPresent();
        view.has_validation = e.validation.present;
        view.complete = e.IsComplete();
        return view;
    }
};

} // namespace assembler::log_level_api::envelope
