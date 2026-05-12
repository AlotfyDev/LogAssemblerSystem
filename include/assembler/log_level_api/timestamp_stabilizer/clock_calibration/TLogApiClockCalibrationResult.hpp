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

#include <vector>

#include "TLogApiClockCalibrationIssue.hpp"
#include "TLogApiClockSkewReport.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

struct TLogApiClockCalibrationResult final {
    TLogApiClockSkewReport report{};
    std::vector<TLogApiClockCalibrationIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return report.HasEvidence() && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
