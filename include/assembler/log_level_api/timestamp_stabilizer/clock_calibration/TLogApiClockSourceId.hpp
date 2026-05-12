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
#include <string>

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

struct TLogApiClockSourceId final {
    std::uint64_t value{0};

    constexpr TLogApiClockSourceId() = default;
    constexpr explicit TLogApiClockSourceId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-clock-source-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
