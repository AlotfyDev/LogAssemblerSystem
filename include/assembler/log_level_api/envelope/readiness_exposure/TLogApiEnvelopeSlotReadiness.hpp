#pragma once

/*
    LOGAPI-W24 — Envelope Readiness And Exposure View

    Responsibility:
        Define envelope readiness and exposure view/report types on top of the
        final envelope shape from LOGAPI-W23.

    Boundary:
        This wave does not assemble envelopes, mutate envelopes, perform
        circulation handoff, run validators, execute policy decisions, or persist
        envelope material.

    Doctrine:
        Readiness/exposure views are observational surfaces.
        They help later communication bindings and circulation integration decide
        whether an envelope is visible/ready, without owning downstream behavior.
*/

#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelope.hpp"

namespace assembler::log_level_api::envelope::readiness_exposure {

struct TLogApiEnvelopeSlotReadiness final {
    bool header_ready{false};
    bool content_ready{false};
    bool metadata_ready{false};
    bool timestamp_ready{false};
    bool validation_slot_ready{false};

    [[nodiscard]] static TLogApiEnvelopeSlotReadiness From(
        const assembler::log_level_api::envelope::final_shape::TLogApiFinalEnvelope& envelope
    ) noexcept {
        TLogApiEnvelopeSlotReadiness r{};
        r.header_ready = envelope.header.IsPresent();
        r.content_ready = envelope.content_slot.IsPresent();
        r.metadata_ready = envelope.metadata_slot.IsPresent();
        r.timestamp_ready = envelope.timestamp_slot.IsPresent();
        r.validation_slot_ready = envelope.validation_slot.IsValidOutcome();
        return r;
    }

    [[nodiscard]] bool RequiredSlotsReady() const noexcept {
        return header_ready && content_ready && metadata_ready && timestamp_ready;
    }

    [[nodiscard]] bool AllSlotsWellFormed() const noexcept {
        return RequiredSlotsReady() && validation_slot_ready;
    }
};

} // namespace assembler::log_level_api::envelope::readiness_exposure
