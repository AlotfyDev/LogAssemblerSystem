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

#include "TLogApiClockCalibrationRequest.hpp"
#include "TLogApiClockCalibrationResult.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

class TLogApiClockCalibrator final {
public:
    [[nodiscard]] static TLogApiClockCalibrationResult Calibrate(const TLogApiClockCalibrationRequest& request) {
        TLogApiClockCalibrationResult result{};

        if (!request.IsReady()) {
            result.issues.push_back({
                "LOGAPI_CLOCK_CALIBRATION_REQUEST_NOT_READY",
                "Clock calibration requires resolved clock sources and captured samples.",
                true
            });
            return result;
        }

        const auto current_offset =
            request.system_entry_sample.timestamp.value - request.writer_filler_sample.timestamp.value;

        result.report.offset.offset_value = current_offset;
        result.report.offset.precision = request.system_entry_sample.timestamp.precision;
        result.report.offset.present = true;

        if (request.HasPreviousPair()) {
            const auto previous_offset =
                request.previous_system_entry_sample.timestamp.value - request.previous_writer_filler_sample.timestamp.value;

            result.report.drift.drift_ppm = static_cast<double>(current_offset - previous_offset);
            result.report.drift.present = true;
        }

        result.report.note = "descriptor-level clock calibration report";
        return result;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
