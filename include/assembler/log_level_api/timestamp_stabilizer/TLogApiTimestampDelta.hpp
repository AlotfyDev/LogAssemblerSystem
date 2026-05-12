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

#include <cstdint>

#include "TLogApiTimestampPrecisionKind.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

struct TLogApiTimestampDelta final {
    std::int64_t delta_value{0};
    TLogApiTimestampPrecisionKind precision{TLogApiTimestampPrecisionKind::Unknown};
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept {
        return present && precision != TLogApiTimestampPrecisionKind::Unknown;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
