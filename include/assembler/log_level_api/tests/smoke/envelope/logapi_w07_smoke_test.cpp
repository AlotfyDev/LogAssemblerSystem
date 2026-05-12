#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentProfileSurface.hpp"
#include "assembler/log_level_api/envelope/TLogApiEnvelopeSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::envelope;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::timestamp_stabilizer;
    using namespace assembler::log_level_api::validator;

    const char payload[] = "{\"message\":\"hello envelope\"}";

    TLogApiEnvelope e{};
    e.header.envelope_id = TLogApiEnvelopeId{1};
    e.header.status = TLogApiEnvelopeStatus::Prepared;
    e.header.envelope_profile_name = "default.envelope.profile";
    e.header.content_profile_name = "default.json.minimal";
    e.header.metadata_profile_name = "default.metadata.struct";
    e.header.timestamp_profile_name = "default.timestamp.stabilizer";
    e.content.content = TLogApiContentInputRef{payload, sizeof(payload)};

    auto metadata_config = TLogApiDefaultMetadataProfile::Make();
    auto metadata_result = TLogApiMetadataInjector::Prepare(metadata_config);
    assert(metadata_result.IsAccepted());
    e.metadata.metadata = metadata_result.block;

    auto timestamp_config = TLogApiDefaultTimestampProfile::Make();
    TLogApiTimestampValue writer{};
    writer.value = 1000;
    writer.precision = TLogApiTimestampPrecisionKind::Milliseconds;
    writer.input_kind = TLogApiTimestampInputKind::WriterFillerProvided;
    writer.present = true;

    TLogApiTimestampValue system{};
    system.value = 1100;
    system.precision = TLogApiTimestampPrecisionKind::Milliseconds;
    system.input_kind = TLogApiTimestampInputKind::SystemProvided;
    system.present = true;

    TLogApiTimestampStabilizationInput ts_input{};
    ts_input.payload_or_writer_filler_timestamp = writer;
    ts_input.system_entry_timestamp = system;

    auto ts_result = TLogApiTimestampStabilizer::Stabilize(timestamp_config, ts_input);
    assert(ts_result.IsAccepted());
    e.timestamp.timestamp = ts_result.timestamp;

    e.validation.present = true;
    e.validation.validation = TLogApiValidationResult::Accepted();

    assert(e.IsComplete());

    auto view = TLogApiEnvelopeView::From(e);
    assert(view.complete);
    assert(view.has_content);
    assert(view.has_metadata);
    assert(view.has_timestamp);
    assert(view.has_validation);

    TLogApiEnvelopeResult result{};
    result.envelope = e;
    assert(result.IsAccepted());

    std::cout << "LOGAPI-W07 smoke test passed\\n";
    return 0;
}
