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

#include <string>

#include "assembler/log_level_api/envelope/final_shape/TLogApiEnvelopeValidationResultSlot.hpp"

namespace assembler::log_level_api::envelope::readiness_exposure {

/*
    Validation exposure view.

    This is observational only. It does not accept/reject payloads.
*/
struct TLogApiEnvelopeValidationExposureView final {
    std::string outcome{};
    bool evaluated{false};
    bool valid{false};
    bool invalid{false};

    [[nodiscard]] static TLogApiEnvelopeValidationExposureView From(
        const assembler::log_level_api::envelope::final_shape::TLogApiEnvelopeValidationResultSlot& slot
    ) {
        using Outcome = assembler::log_level_api::envelope::final_shape::TLogApiValidationOutcomeKind;

        TLogApiEnvelopeValidationExposureView view{};
        view.evaluated = slot.IsPresent();

        switch (slot.outcome) {
            case Outcome::Valid:
                view.outcome = "valid";
                view.valid = true;
                break;
            case Outcome::Invalid:
                view.outcome = "invalid";
                view.invalid = true;
                break;
            case Outcome::NotEvaluated:
                view.outcome = "not_evaluated";
                break;
            default:
                view.outcome = "unknown";
                break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::envelope::readiness_exposure
