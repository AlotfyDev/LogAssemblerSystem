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
#include "TLogApiTimestampDelta.hpp"
#include "TLogApiTimestampValue.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

struct TLogApiStabilizedTimestamp final {
    TLogApiTimestampValue stabilized_value{};
    TLogApiTimestampValue source_value{};
    TLogApiTimestampValue system_entry_value{};
    TLogApiTimestampDelta source_system_delta{};
    TLogApiCalendarKind calendar{TLogApiCalendarKind::Unknown};

    [[nodiscard]] bool IsPresent() const noexcept {
        return stabilized_value.IsPresent()
            && calendar != TLogApiCalendarKind::Unknown;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
