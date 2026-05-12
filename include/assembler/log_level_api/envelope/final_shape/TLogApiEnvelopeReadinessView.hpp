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

#include <string>

#include "TLogApiEnvelopeReadinessKind.hpp"
#include "TLogApiFinalEnvelope.hpp"

namespace assembler::log_level_api::envelope::final_shape {

struct TLogApiEnvelopeReadinessView final {
    TLogApiEnvelopeReadinessKind readiness{TLogApiEnvelopeReadinessKind::Unknown};

    bool has_header{false};
    bool has_content{false};
    bool has_metadata{false};
    bool has_timestamp{false};
    bool has_validation_slot{false};
    bool validation_evaluated{false};

    std::string envelope_id{};
    std::string version{};

    [[nodiscard]] static TLogApiEnvelopeReadinessView From(const TLogApiFinalEnvelope& envelope) {
        TLogApiEnvelopeReadinessView view{};
        view.has_header = envelope.header.IsPresent();
        view.has_content = envelope.content_slot.IsPresent();
        view.has_metadata = envelope.metadata_slot.IsPresent();
        view.has_timestamp = envelope.timestamp_slot.IsPresent();
        view.has_validation_slot = envelope.validation_slot.IsValidOutcome();
        view.validation_evaluated = envelope.validation_slot.IsPresent();
        view.envelope_id = envelope.header.id.ToString();
        view.version = envelope.header.version.ToString();

        view.readiness = envelope.IsWellShaped()
            ? TLogApiEnvelopeReadinessKind::ReadyForCirculationBinding
            : TLogApiEnvelopeReadinessKind::NotReady;

        return view;
    }

    [[nodiscard]] bool IsReadyForCirculationBinding() const noexcept {
        return readiness == TLogApiEnvelopeReadinessKind::ReadyForCirculationBinding;
    }
};

} // namespace assembler::log_level_api::envelope::final_shape
