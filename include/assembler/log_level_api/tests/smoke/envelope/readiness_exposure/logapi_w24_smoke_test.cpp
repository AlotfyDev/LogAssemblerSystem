#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"
#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelopeSurface.hpp"
#include "assembler/log_level_api/envelope/readiness_exposure/TLogApiEnvelopeReadinessExposureSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::envelope::final_shape;
    using namespace assembler::log_level_api::envelope::readiness_exposure;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::timestamp_stabilizer;
    using namespace assembler::log_level_api::validator;

    const char payload[] = "readiness-exposure-payload";
    TLogApiContentInputRef content_ref{payload, sizeof(payload)};

    TLogApiParsedContentRef parsed{};
    parsed.parsed_kind = TLogApiParsedContentKind::OpaqueContentRef;
    parsed.source_content = content_ref;
    parsed.parsed = false;

    auto metadata_config = TLogApiDefaultMetadataProfile::Make();
    auto metadata_result = TLogApiMetadataInjector::Prepare(metadata_config);
    assert(metadata_result.IsAccepted());

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

    auto timestamp_config = TLogApiDefaultTimestampProfile::Make();
    TLogApiTimestampStabilizationInput timestamp_input{};
    timestamp_input.payload_or_writer_filler_timestamp = writer;
    timestamp_input.system_entry_timestamp = system;

    auto timestamp_result = TLogApiTimestampStabilizer::Stabilize(timestamp_config, timestamp_input);
    assert(timestamp_result.IsAccepted());

    TLogApiFinalEnvelope envelope{};
    envelope.header.id = TLogApiEnvelopeIdentityFactory::FromSequence(42);
    envelope.header.version = {1, 0};
    envelope.header.status = TLogApiFinalEnvelopeStatus::Ready;
    envelope.header.envelope_profile_name = "default.final.envelope";
    envelope.header.content_profile_name = "opaque.pass_through";
    envelope.header.metadata_profile_name = "default.metadata.struct";
    envelope.header.timestamp_profile_name = "default.timestamp.stabilizer";
    envelope.header.validation_profile_name = "not_evaluated";
    envelope.content_slot.content = content_ref;
    envelope.content_slot.parsed_content = parsed;
    envelope.metadata_slot.metadata = metadata_result.block;
    envelope.timestamp_slot.timestamp = timestamp_result.timestamp;
    envelope.validation_slot = TLogApiEnvelopeValidationResultSlot::NotEvaluated();

    assert(envelope.IsWellShaped());

    TLogApiEnvelopeExposureRequest request{};
    request.exposure_id = TLogApiEnvelopeExposureId{1};
    request.exposure_kind = TLogApiEnvelopeExposureKind::BindingView;
    request.envelope = &envelope;

    auto result = TLogApiEnvelopeExposureBuilder::Build(request);
    assert(result.IsAccepted());
    assert(TLogApiEnvelopeReadinessGate::AllowsBindingExposure(result));

    assert(result.view.envelope_id == "logapi-final-envelope-42");
    assert(result.view.validation_view.outcome == "not_evaluated");
    assert(result.view.slot_readiness.AllSlotsWellFormed());

    TLogApiFinalEnvelope incomplete{};
    incomplete.header = envelope.header;
    incomplete.content_slot = envelope.content_slot;

    TLogApiEnvelopeExposureRequest bad_request{};
    bad_request.exposure_id = TLogApiEnvelopeExposureId{2};
    bad_request.exposure_kind = TLogApiEnvelopeExposureKind::BindingView;
    bad_request.envelope = &incomplete;

    auto bad = TLogApiEnvelopeExposureBuilder::Build(bad_request);
    assert(!bad.IsAccepted());
    assert(bad.HasBlockingIssue());
    assert(!TLogApiEnvelopeReadinessGate::AllowsBindingExposure(bad));

    std::cout << "LOGAPI-W24 smoke test passed\\n";
    return 0;
}
