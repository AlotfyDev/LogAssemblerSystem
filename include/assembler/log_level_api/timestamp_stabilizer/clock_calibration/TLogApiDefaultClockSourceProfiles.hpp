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

#include "TLogApiClockSourceDescriptor.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

struct TLogApiDefaultClockSourceProfiles final {
    [[nodiscard]] static TLogApiClockSourceDescriptor MakeSystemClock() {
        TLogApiClockSourceDescriptor d{};
        d.id = TLogApiClockSourceId{1};
        d.kind = TLogApiClockSourceKind::SystemClock;
        d.status = TLogApiClockSourceStatus::Resolved;
        d.source_name = "default.system.entry.clock";
        d.calendar = assembler::log_level_api::timestamp_stabilizer::TLogApiCalendarKind::UnixEpochUtc;
        d.precision = assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind::Milliseconds;
        return d;
    }

    [[nodiscard]] static TLogApiClockSourceDescriptor MakeWriterFillerClock() {
        TLogApiClockSourceDescriptor d{};
        d.id = TLogApiClockSourceId{2};
        d.kind = TLogApiClockSourceKind::WriterFillerClock;
        d.status = TLogApiClockSourceStatus::Resolved;
        d.source_name = "default.writer.filler.clock";
        d.calendar = assembler::log_level_api::timestamp_stabilizer::TLogApiCalendarKind::UnixEpochUtc;
        d.precision = assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind::Milliseconds;
        return d;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
