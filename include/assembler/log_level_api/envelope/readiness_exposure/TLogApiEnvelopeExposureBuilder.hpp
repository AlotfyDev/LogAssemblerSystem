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

#include "TLogApiEnvelopeExposureRequest.hpp"
#include "TLogApiEnvelopeExposureResult.hpp"

namespace assembler::log_level_api::envelope::readiness_exposure {

class TLogApiEnvelopeExposureBuilder final {
public:
    [[nodiscard]] static TLogApiEnvelopeExposureResult Build(const TLogApiEnvelopeExposureRequest& request) {
        TLogApiEnvelopeExposureResult result{};

        if (!request.IsReady()) {
            result.issues.push_back({
                "LOGAPI_ENVELOPE_EXPOSURE_REQUEST_NOT_READY",
                "Envelope exposure request requires exposure id, exposure kind, and envelope reference.",
                true
            });
            return result;
        }

        result.view = TLogApiEnvelopeExposureView::FromEnvelope(
            request.exposure_id,
            request.exposure_kind,
            *request.envelope
        );

        if (!result.view.IsReadyForBindingExposure()) {
            result.issues.push_back({
                "LOGAPI_ENVELOPE_NOT_READY_FOR_BINDING_EXPOSURE",
                "Envelope is not well-shaped for binding exposure.",
                true
            });
        }

        return result;
    }
};

} // namespace assembler::log_level_api::envelope::readiness_exposure
