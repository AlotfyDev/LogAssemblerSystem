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

#include "TLogApiEnvelopeContentSlot.hpp"
#include "TLogApiEnvelopeHeaderFinal.hpp"
#include "TLogApiEnvelopeMetadataSlot.hpp"
#include "TLogApiEnvelopeTimestampSlot.hpp"
#include "TLogApiEnvelopeValidationResultSlot.hpp"

namespace assembler::log_level_api::envelope::final_shape {

struct TLogApiFinalEnvelope final {
    TLogApiEnvelopeHeaderFinal header{};
    TLogApiEnvelopeContentSlot content_slot{};
    TLogApiEnvelopeMetadataSlot metadata_slot{};
    TLogApiEnvelopeTimestampSlot timestamp_slot{};
    TLogApiEnvelopeValidationResultSlot validation_slot{};

    [[nodiscard]] bool HasRequiredSlots() const noexcept {
        return content_slot.IsPresent()
            && metadata_slot.IsPresent()
            && timestamp_slot.IsPresent();
    }

    [[nodiscard]] bool IsWellShaped() const noexcept {
        return header.IsPresent()
            && HasRequiredSlots()
            && validation_slot.IsValidOutcome();
    }
};

} // namespace assembler::log_level_api::envelope::final_shape
