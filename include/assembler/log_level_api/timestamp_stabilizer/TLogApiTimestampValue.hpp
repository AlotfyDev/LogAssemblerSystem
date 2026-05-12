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

#include "TLogApiTimestampInputKind.hpp"
#include "TLogApiTimestampPrecisionKind.hpp"

namespace assembler::log_level_api::timestamp_stabilizer {

/*
    Timestamp value carrier.

    The numeric value is interpreted according to the configured calendar and precision.
    This carrier is intentionally not a clock or stabilization algorithm.
*/
struct TLogApiTimestampValue final {
    std::int64_t value{0};
    TLogApiTimestampPrecisionKind precision{TLogApiTimestampPrecisionKind::Unknown};
    TLogApiTimestampInputKind input_kind{TLogApiTimestampInputKind::Unknown};
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept {
        return present && precision != TLogApiTimestampPrecisionKind::Unknown;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer
