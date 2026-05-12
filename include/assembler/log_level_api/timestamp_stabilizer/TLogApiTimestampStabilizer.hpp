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

#include "TLogApiTimestampStabilizationInput.hpp"
#include "TLogApiTimestampStabilizationIssue.hpp"
#include "TLogApiTimestampStabilizationResult.hpp"
#include "TLogApiTimestampStabilizerConfig.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

/*
    Minimal deterministic timestamp stabilization model.

    This model does not read system clocks. It receives already captured input
    timestamps and applies the configured basis/fallback/offset rule.
*/
class TLogApiTimestampStabilizer final {
public:
    [[nodiscard]] static TLogApiTimestampStabilizationResult Stabilize(
        const TLogApiTimestampStabilizerConfig& config,
        const TLogApiTimestampStabilizationInput& input
    ) {
        TLogApiTimestampStabilizationResult result{};

        if (!config.IsResolved()) {
            result.issues.push_back({
                "LOGAPI_TIMESTAMP_CONFIG_NOT_RESOLVED",
                "Timestamp stabilizer config must be resolved before stabilization.",
                true
            });
            return result;
        }

        if (!input.HasSystemEntryTimestamp()) {
            if (config.fallback_mode == TLogApiTimestampFallbackMode::RejectWhenMissing) {
                result.issues.push_back({
                    "LOGAPI_TIMESTAMP_SYSTEM_ENTRY_MISSING",
                    "System-entry timestamp is required by this profile.",
                    true
                });
                return result;
            }
        }

        const bool has_source = input.HasPayloadOrWriterFillerTimestamp();
        const bool has_system = input.HasSystemEntryTimestamp();

        TLogApiTimestampValue stabilized{};

        switch (config.time_basis) {
            case TLogApiTimeBasisKind::SystemEntryTime:
                if (has_system) stabilized = input.system_entry_timestamp;
                break;

            case TLogApiTimeBasisKind::WriterFillerTime:
                if (has_source) stabilized = input.payload_or_writer_filler_timestamp;
                else if (has_system && config.fallback_mode != TLogApiTimestampFallbackMode::RejectWhenMissing) stabilized = input.system_entry_timestamp;
                break;

            case TLogApiTimeBasisKind::HybridSystemAndWriterFillerTime:
                if (has_source && config.offset_mode == TLogApiTimestampOffsetMode::AdjustWriterFillerToSystem && has_system) {
                    stabilized = input.system_entry_timestamp;
                } else if (has_source) {
                    stabilized = input.payload_or_writer_filler_timestamp;
                } else if (has_system) {
                    stabilized = input.system_entry_timestamp;
                }
                break;

            default:
                break;
        }

        if (!stabilized.IsPresent()) {
            result.issues.push_back({
                "LOGAPI_TIMESTAMP_STABILIZED_VALUE_ABSENT",
                "No stabilized timestamp could be produced from the provided input.",
                true
            });
            return result;
        }

        stabilized.precision = config.precision;

        result.timestamp.stabilized_value = stabilized;
        result.timestamp.source_value = input.payload_or_writer_filler_timestamp;
        result.timestamp.system_entry_value = input.system_entry_timestamp;
        result.timestamp.calendar = config.calendar;

        if (has_source && has_system) {
            result.timestamp.source_system_delta.present = true;
            result.timestamp.source_system_delta.precision = config.precision;
            result.timestamp.source_system_delta.delta_value =
                input.system_entry_timestamp.value - input.payload_or_writer_filler_timestamp.value;
        }

        return result;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
