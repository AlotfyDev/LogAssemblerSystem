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

#include <string>

#include "TLogApiClockSourceId.hpp"
#include "TLogApiClockSourceKind.hpp"
#include "TLogApiClockSourceStatus.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiCalendarKind.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampPrecisionKind.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

struct TLogApiClockSourceDescriptor final {
    TLogApiClockSourceId id{};
    TLogApiClockSourceKind kind{TLogApiClockSourceKind::Unknown};
    TLogApiClockSourceStatus status{TLogApiClockSourceStatus::Unknown};

    std::string source_name{};
    assembler::log_level_api::timestamp_stabilizer::TLogApiCalendarKind calendar{
        assembler::log_level_api::timestamp_stabilizer::TLogApiCalendarKind::Unknown
    };
    assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind precision{
        assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind::Unknown
    };

    [[nodiscard]] bool IsResolved() const noexcept {
        return id.IsValid()
            && kind != TLogApiClockSourceKind::Unknown
            && (status == TLogApiClockSourceStatus::Resolved || status == TLogApiClockSourceStatus::Active)
            && !source_name.empty()
            && calendar != assembler::log_level_api::timestamp_stabilizer::TLogApiCalendarKind::Unknown
            && precision != assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind::Unknown;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
