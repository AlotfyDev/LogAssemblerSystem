#include <cassert>
#include <iostream>

#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"

int main() {
    using namespace assembler::log_level_api::timestamp_stabilizer;

    auto config = TLogApiDefaultTimestampProfile::Make();
    assert(config.IsResolved());

    TLogApiTimestampValue writer_time{};
    writer_time.value = 1000;
    writer_time.precision = TLogApiTimestampPrecisionKind::Milliseconds;
    writer_time.input_kind = TLogApiTimestampInputKind::WriterFillerProvided;
    writer_time.present = true;

    TLogApiTimestampValue system_time{};
    system_time.value = 1100;
    system_time.precision = TLogApiTimestampPrecisionKind::Milliseconds;
    system_time.input_kind = TLogApiTimestampInputKind::SystemProvided;
    system_time.present = true;

    TLogApiTimestampStabilizationInput input{};
    input.payload_or_writer_filler_timestamp = writer_time;
    input.system_entry_timestamp = system_time;

    auto result = TLogApiTimestampStabilizer::Stabilize(config, input);
    assert(result.IsAccepted());
    assert(result.timestamp.IsPresent());
    assert(result.timestamp.stabilized_value.value == 1000);
    assert(result.timestamp.source_system_delta.IsPresent());
    assert(result.timestamp.source_system_delta.delta_value == 100);

    auto view = TLogApiTimestampStabilizerView::From(config);
    assert(view.resolved);
    assert(view.calendar == "unix_epoch_utc");
    assert(view.precision == "milliseconds");
    assert(view.offset_mode == "preserve_both_and_report_delta");

    std::cout << "LOGAPI-W05 smoke test passed\\n";
    return 0;
}
