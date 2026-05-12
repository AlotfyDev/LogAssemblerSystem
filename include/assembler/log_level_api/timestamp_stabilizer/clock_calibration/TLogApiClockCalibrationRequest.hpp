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

#include "TLogApiClockCalibrationMode.hpp"
#include "TLogApiClockSample.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration {

/*
    Calibration request between writer/filler clock and system-entry clock.

    This carries already captured samples. It does not acquire time from clocks.
*/
struct TLogApiClockCalibrationRequest final {
    TLogApiClockCalibrationMode mode{TLogApiClockCalibrationMode::Unknown};
    TLogApiClockSample writer_filler_sample{};
    TLogApiClockSample system_entry_sample{};
    TLogApiClockSample previous_writer_filler_sample{};
    TLogApiClockSample previous_system_entry_sample{};

    [[nodiscard]] bool HasCurrentPair() const noexcept {
        return writer_filler_sample.IsReady() && system_entry_sample.IsReady();
    }

    [[nodiscard]] bool HasPreviousPair() const noexcept {
        return previous_writer_filler_sample.IsReady() && previous_system_entry_sample.IsReady();
    }

    [[nodiscard]] bool IsReady() const noexcept {
        if (mode == TLogApiClockCalibrationMode::Unknown) return false;
        if (!HasCurrentPair()) return false;
        if ((mode == TLogApiClockCalibrationMode::CaptureDriftOnly
            || mode == TLogApiClockCalibrationMode::CaptureOffsetAndDrift
            || mode == TLogApiClockCalibrationMode::CaptureSkewReport) && !HasPreviousPair()) {
            return false;
        }
        return true;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration
