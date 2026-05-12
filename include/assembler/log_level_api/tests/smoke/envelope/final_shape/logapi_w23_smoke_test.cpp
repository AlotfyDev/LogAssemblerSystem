#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"
#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelopeSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::envelope::final_shape;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::timestamp_stabilizer;
    using namespace assembler::log_level_api::validator;

    const char payload[] = "opaque-final-envelope-payload";
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
    envelope.header.id = TLogApiEnvelopeIdentityFactory::FromSequence(1);
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

    auto readiness = TLogApiEnvelopeReadinessView::From(envelope);
    assert(readiness.IsReadyForCirculationBinding());
    assert(readiness.has_validation_slot);
    assert(!readiness.validation_evaluated);

    auto valid_slot = TLogApiEnvelopeValidationResultSlot::FromValidationResult(TLogApiValidationResult::Accepted());
    assert(valid_slot.IsPresent());
    assert(valid_slot.outcome == TLogApiValidationOutcomeKind::Valid);

    TLogApiFinalEnvelopeResult result{};
    result.envelope = envelope;
    assert(result.IsAccepted());

    std::cout << "LOGAPI-W23 smoke test passed\\n";
    return 0;
}
