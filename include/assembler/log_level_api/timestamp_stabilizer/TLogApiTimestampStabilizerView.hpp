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

#include <string>

#include "TLogApiTimestampStabilizerConfig.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

struct TLogApiTimestampStabilizerView final {
    std::string profile_name{};
    std::string time_basis{};
    std::string calendar{};
    std::string precision{};
    std::string fallback_mode{};
    std::string offset_mode{};
    bool resolved{false};

    [[nodiscard]] static TLogApiTimestampStabilizerView From(const TLogApiTimestampStabilizerConfig& c) {
        TLogApiTimestampStabilizerView v{};
        v.profile_name = c.profile_name;
        v.resolved = c.IsResolved();

        switch (c.time_basis) {
            case TLogApiTimeBasisKind::SystemEntryTime: v.time_basis = "system_entry_time"; break;
            case TLogApiTimeBasisKind::WriterFillerTime: v.time_basis = "writer_filler_time"; break;
            case TLogApiTimeBasisKind::HybridSystemAndWriterFillerTime: v.time_basis = "hybrid_system_and_writer_filler_time"; break;
            default: v.time_basis = "unknown"; break;
        }

        switch (c.calendar) {
            case TLogApiCalendarKind::UnixEpochUtc: v.calendar = "unix_epoch_utc"; break;
            case TLogApiCalendarKind::TradingServerTime: v.calendar = "trading_server_time"; break;
            case TLogApiCalendarKind::ExchangeTime: v.calendar = "exchange_time"; break;
            case TLogApiCalendarKind::Custom: v.calendar = "custom"; break;
            default: v.calendar = "unknown"; break;
        }

        switch (c.precision) {
            case TLogApiTimestampPrecisionKind::Seconds: v.precision = "seconds"; break;
            case TLogApiTimestampPrecisionKind::Milliseconds: v.precision = "milliseconds"; break;
            case TLogApiTimestampPrecisionKind::Microseconds: v.precision = "microseconds"; break;
            case TLogApiTimestampPrecisionKind::Nanoseconds: v.precision = "nanoseconds"; break;
            default: v.precision = "unknown"; break;
        }

        switch (c.fallback_mode) {
            case TLogApiTimestampFallbackMode::RejectWhenMissing: v.fallback_mode = "reject_when_missing"; break;
            case TLogApiTimestampFallbackMode::UseSystemEntryTime: v.fallback_mode = "use_system_entry_time"; break;
            case TLogApiTimestampFallbackMode::UseWriterFillerTimeWhenValidOtherwiseSystem: v.fallback_mode = "use_writer_filler_time_when_valid_otherwise_system"; break;
            case TLogApiTimestampFallbackMode::AcceptAbsentAndMarkUnstable: v.fallback_mode = "accept_absent_and_mark_unstable"; break;
            default: v.fallback_mode = "unknown"; break;
        }

        switch (c.offset_mode) {
            case TLogApiTimestampOffsetMode::None: v.offset_mode = "none"; break;
            case TLogApiTimestampOffsetMode::CaptureDeltaOnly: v.offset_mode = "capture_delta_only"; break;
            case TLogApiTimestampOffsetMode::AdjustWriterFillerToSystem: v.offset_mode = "adjust_writer_filler_to_system"; break;
            case TLogApiTimestampOffsetMode::PreserveBothAndReportDelta: v.offset_mode = "preserve_both_and_report_delta"; break;
            default: v.offset_mode = "unknown"; break;
        }

        return v;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
