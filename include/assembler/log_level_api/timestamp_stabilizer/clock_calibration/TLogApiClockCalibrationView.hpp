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

#include <string>

#include "TLogApiClockCalibrationResult.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

struct TLogApiClockCalibrationView final {
    bool accepted{false};
    bool has_offset{false};
    bool has_drift{false};
    std::int64_t offset_value{0};
    double drift_ppm{0.0};
    std::string note{};

    [[nodiscard]] static TLogApiClockCalibrationView From(const TLogApiClockCalibrationResult& result) {
        TLogApiClockCalibrationView view{};
        view.accepted = result.IsAccepted();
        view.has_offset = result.report.offset.IsPresent();
        view.has_drift = result.report.drift.IsPresent();
        view.offset_value = result.report.offset.offset_value;
        view.drift_ppm = result.report.drift.drift_ppm;
        view.note = result.report.note;
        return view;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
