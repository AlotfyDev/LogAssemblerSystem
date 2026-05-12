#pragma once

/*
    LOGAPI-W21 — Timestamp Clock Source And Calibration

    Responsibility:
        Define timestamp clock source descriptors, captured clock samples,
        writer/filler vs system-entry time calibration, offset/drift/skew reports,
        and calibration views used by the timestamp stabilizer production path.

    Boundary:
        This wave does not read operating-system clocks, does not implement
        calendar conversion, does not introduce policy assignment, and does not
        assemble envelopes.

    Doctrine:
        Timestamp is independent from content and metadata.
        Clock source and calibration are preparation concerns before the envelope
        receives a stabilized timestamp.
*/

#include "TLogApiClockCalibrationIssue.hpp"
#include "TLogApiClockCalibrationMode.hpp"
#include "TLogApiClockCalibrationRequest.hpp"
#include "TLogApiClockCalibrationResult.hpp"
#include "TLogApiClockCalibrationView.hpp"
#include "TLogApiClockCalibrator.hpp"
#include "TLogApiClockDriftSample.hpp"
#include "TLogApiClockOffsetSample.hpp"
#include "TLogApiClockSample.hpp"
#include "TLogApiClockSkewReport.hpp"
#include "TLogApiClockSourceDescriptor.hpp"
#include "TLogApiClockSourceId.hpp"
#include "TLogApiClockSourceKind.hpp"
#include "TLogApiClockSourceStatus.hpp"
#include "TLogApiDefaultClockSourceProfiles.hpp"
