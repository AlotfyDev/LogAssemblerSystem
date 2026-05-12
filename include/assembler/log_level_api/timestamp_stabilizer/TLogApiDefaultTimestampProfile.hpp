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

#include "TLogApiTimestampStabilizerConfig.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

struct TLogApiDefaultTimestampProfile final {
    [[nodiscard]] static TLogApiTimestampStabilizerConfig Make() {
        TLogApiTimestampStabilizerConfig config{};
        config.id = TLogApiTimestampStabilizerId{1};
        config.status = TLogApiTimestampStabilizerStatus::Resolved;
        config.profile_name = "default.timestamp.stabilizer";
        config.time_basis = TLogApiTimeBasisKind::HybridSystemAndWriterFillerTime;
        config.calendar = TLogApiCalendarKind::UnixEpochUtc;
        config.precision = TLogApiTimestampPrecisionKind::Milliseconds;
        config.fallback_mode = TLogApiTimestampFallbackMode::UseWriterFillerTimeWhenValidOtherwiseSystem;
        config.offset_mode = TLogApiTimestampOffsetMode::PreserveBothAndReportDelta;
        return config;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
