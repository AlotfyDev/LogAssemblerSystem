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

namespace assembler::log_level_api::envelope::readiness_exposure {

enum class TLogApiEnvelopeExposureKind {
    Unknown = 0,
    InternalView,
    BindingView,
    CirculationCandidateView
};

} // namespace assembler::log_level_api::envelope::readiness_exposure
