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

#include "TLogApiEnvelopeExposureResult.hpp"

namespace assembler::log_level_api::envelope::readiness_exposure {

/*
    Readiness gate for later binding layers.

    This is a pure gate/check. It does not hand off to circulation.
*/
struct TLogApiEnvelopeReadinessGate final {
    [[nodiscard]] static bool AllowsBindingExposure(const TLogApiEnvelopeExposureResult& result) noexcept {
        return result.IsAccepted();
    }
};

} // namespace assembler::log_level_api::envelope::readiness_exposure
