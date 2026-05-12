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

#include "TLogApiTimestampValue.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

/*
    Input to timestamp stabilization.

    Payload/writer-filler timestamp is optional. System-entry timestamp is expected
    for normal stabilization, but this struct only carries values; it does not read clocks.
*/
struct TLogApiTimestampStabilizationInput final {
    TLogApiTimestampValue payload_or_writer_filler_timestamp{};
    TLogApiTimestampValue system_entry_timestamp{};

    [[nodiscard]] bool HasSystemEntryTimestamp() const noexcept {
        return system_entry_timestamp.IsPresent();
    }

    [[nodiscard]] bool HasPayloadOrWriterFillerTimestamp() const noexcept {
        return payload_or_writer_filler_timestamp.IsPresent();
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
