#pragma once

/*
    LOGAPI-W05 — Timestamp Stabilizer Config And Model

    This header belongs to the Log Level API timestamp stabilization layer.

    Responsibility:
        Define timestamp stabilization configuration, timestamp source categories,
        calendar/time basis choices, writer/filler time handling, offset/drift
        modeling, stabilization result carriers, and stabilized timestamp blocks.

    Boundary:
        Timestamp is not content.
        Timestamp is not metadata.
        Timestamp stabilization does not define content schemas, metadata fields,
        concrete validators, envelope assembly, communication bindings, or policy
        assignment.

    Doctrine:
        Content + metadata struct + stabilized timestamp meet later inside the
        envelope through the envelope assembler.
*/

#include "TLogApiCalendarKind.hpp"
#include "TLogApiDefaultTimestampProfile.hpp"
#include "TLogApiStabilizedTimestamp.hpp"
#include "TLogApiTimeBasisKind.hpp"
#include "TLogApiTimestampDelta.hpp"
#include "TLogApiTimestampFallbackMode.hpp"
#include "TLogApiTimestampInputKind.hpp"
#include "TLogApiTimestampOffsetMode.hpp"
#include "TLogApiTimestampPrecisionKind.hpp"
#include "TLogApiTimestampStabilizationInput.hpp"
#include "TLogApiTimestampStabilizationIssue.hpp"
#include "TLogApiTimestampStabilizationResult.hpp"
#include "TLogApiTimestampStabilizer.hpp"
#include "TLogApiTimestampStabilizerConfig.hpp"
#include "TLogApiTimestampStabilizerId.hpp"
#include "TLogApiTimestampStabilizerStatus.hpp"
#include "TLogApiTimestampStabilizerView.hpp"
#include "TLogApiTimestampValue.hpp"
