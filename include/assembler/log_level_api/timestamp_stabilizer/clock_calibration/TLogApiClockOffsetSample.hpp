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

#include <cstdint>

#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampPrecisionKind.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

struct TLogApiClockOffsetSample final {
    std::int64_t offset_value{0};
    assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind precision{
        assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind::Unknown
    };
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept {
        return present
            && precision != assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampPrecisionKind::Unknown;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
