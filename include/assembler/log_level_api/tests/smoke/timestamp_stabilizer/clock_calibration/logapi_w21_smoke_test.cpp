#include <cassert>
#include <iostream>

#include "assembler/log_level_api/timestamp_stabilizer/clock_calibration/TLogApiClockCalibrationSurface.hpp"

int main() {
    using namespace assembler::log_level_api::timestamp_stabilizer;
    using namespace assembler::log_level_api::timestamp_stabilizer::clock_calibration;

    auto system = TLogApiDefaultClockSourceProfiles::MakeSystemClock();
    auto writer = TLogApiDefaultClockSourceProfiles::MakeWriterFillerClock();

    assert(system.IsResolved());
    assert(writer.IsResolved());

    TLogApiClockSample writer_prev{};
    writer_prev.source = writer;
    writer_prev.timestamp = TLogApiTimestampValue{1000, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::WriterFillerProvided, true};

    TLogApiClockSample system_prev{};
    system_prev.source = system;
    system_prev.timestamp = TLogApiTimestampValue{1100, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::SystemProvided, true};

    TLogApiClockSample writer_now{};
    writer_now.source = writer;
    writer_now.timestamp = TLogApiTimestampValue{2000, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::WriterFillerProvided, true};

    TLogApiClockSample system_now{};
    system_now.source = system;
    system_now.timestamp = TLogApiTimestampValue{2115, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::SystemProvided, true};

    TLogApiClockCalibrationRequest request{};
    request.mode = TLogApiClockCalibrationMode::CaptureSkewReport;
    request.previous_writer_filler_sample = writer_prev;
    request.previous_system_entry_sample = system_prev;
    request.writer_filler_sample = writer_now;
    request.system_entry_sample = system_now;

    assert(request.IsReady());

    auto result = TLogApiClockCalibrator::Calibrate(request);
    assert(result.IsAccepted());
    assert(result.report.offset.IsPresent());
    assert(result.report.offset.offset_value == 115);
    assert(result.report.drift.IsPresent());
    assert(result.report.drift.drift_ppm == 15.0);

    auto view = TLogApiClockCalibrationView::From(result);
    assert(view.accepted);
    assert(view.has_offset);
    assert(view.has_drift);
    assert(view.offset_value == 115);

    std::cout << "LOGAPI-W21 smoke test passed\\n";
    return 0;
}
