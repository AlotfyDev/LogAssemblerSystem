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

#include "TLogApiCalendarKind.hpp"
#include "TLogApiTimeBasisKind.hpp"
#include "TLogApiTimestampFallbackMode.hpp"
#include "TLogApiTimestampOffsetMode.hpp"
#include "TLogApiTimestampPrecisionKind.hpp"
#include "TLogApiTimestampStabilizerId.hpp"
#include "TLogApiTimestampStabilizerStatus.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

/*
    Timestamp stabilizer configuration.

    This configuration determines the meaning of system-entry time, writer/filler
    time, offset calculation, fallback behavior, and final stabilized timestamp
    precision. It is more semantics-sensitive than ordinary metadata field updates.
*/
struct TLogApiTimestampStabilizerConfig final {
    TLogApiTimestampStabilizerId id{};
    TLogApiTimestampStabilizerStatus status{TLogApiTimestampStabilizerStatus::Unknown};

    std::string profile_name{};

    TLogApiTimeBasisKind time_basis{TLogApiTimeBasisKind::Unknown};
    TLogApiCalendarKind calendar{TLogApiCalendarKind::Unknown};
    TLogApiTimestampPrecisionKind precision{TLogApiTimestampPrecisionKind::Unknown};
    TLogApiTimestampFallbackMode fallback_mode{TLogApiTimestampFallbackMode::Unknown};
    TLogApiTimestampOffsetMode offset_mode{TLogApiTimestampOffsetMode::Unknown};

    [[nodiscard]] bool IsResolved() const noexcept {
        if (!id.IsValid()) return false;
        if (status != TLogApiTimestampStabilizerStatus::Resolved
            && status != TLogApiTimestampStabilizerStatus::Active) return false;
        if (profile_name.empty()) return false;
        if (time_basis == TLogApiTimeBasisKind::Unknown) return false;
        if (calendar == TLogApiCalendarKind::Unknown) return false;
        if (precision == TLogApiTimestampPrecisionKind::Unknown) return false;
        if (fallback_mode == TLogApiTimestampFallbackMode::Unknown) return false;
        if (offset_mode == TLogApiTimestampOffsetMode::Unknown) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
