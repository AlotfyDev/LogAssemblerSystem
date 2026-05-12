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

#include "TLogApiEnvelopeExposureId.hpp"
#include "TLogApiEnvelopeExposureKind.hpp"

namespace assembler::log_level_api::envelope::readiness_exposure {

struct TLogApiEnvelopeExposureRequest final {
    TLogApiEnvelopeExposureId exposure_id{};
    TLogApiEnvelopeExposureKind exposure_kind{TLogApiEnvelopeExposureKind::Unknown};
    const assembler::log_level_api::envelope::final_shape::TLogApiFinalEnvelope* envelope{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return exposure_id.IsValid()
            && exposure_kind != TLogApiEnvelopeExposureKind::Unknown
            && envelope != nullptr;
    }
};

} // namespace assembler::log_level_api::envelope::readiness_exposure
