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

#include "TLogApiEnvelopeExposureBuilder.hpp"
#include "TLogApiEnvelopeExposureId.hpp"
#include "TLogApiEnvelopeExposureKind.hpp"
#include "TLogApiEnvelopeExposureReport.hpp"
#include "TLogApiEnvelopeExposureRequest.hpp"
#include "TLogApiEnvelopeExposureResult.hpp"
#include "TLogApiEnvelopeExposureStatus.hpp"
#include "TLogApiEnvelopeExposureView.hpp"
#include "TLogApiEnvelopeReadinessGate.hpp"
#include "TLogApiEnvelopeReadinessIssue.hpp"
#include "TLogApiEnvelopeSlotReadiness.hpp"
#include "TLogApiEnvelopeValidationExposureView.hpp"
