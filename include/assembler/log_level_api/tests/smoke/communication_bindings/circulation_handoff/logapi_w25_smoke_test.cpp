#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"
#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelopeSurface.hpp"
#include "assembler/log_level_api/envelope/readiness_exposure/TLogApiEnvelopeReadinessExposureSurface.hpp"
#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffContractSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::envelope::final_shape;
    using namespace assembler::log_level_api::envelope::readiness_exposure;
    using namespace assembler::log_level_api::communication_bindings::circulation_handoff;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::timestamp_stabilizer;

    const char payload[] = "handoff-payload";
    TLogApiContentInputRef content_ref{payload, sizeof(payload)};

    TLogApiParsedContentRef parsed{};
    parsed.parsed_kind = TLogApiParsedContentKind::OpaqueContentRef;
    parsed.source_content = content_ref;
    parsed.parsed = false;

    auto metadata_config = TLogApiDefaultMetadataProfile::Make();
    auto metadata_result = TLogApiMetadataInjector::Prepare(metadata_config);
    assert(metadata_result.IsAccepted());

    TLogApiTimestampValue writer{1000, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::WriterFillerProvided, true};
    TLogApiTimestampValue system{1100, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::SystemProvided, true};

    auto timestamp_config = TLogApiDefaultTimestampProfile::Make();
    TLogApiTimestampStabilizationInput timestamp_input{};
    timestamp_input.payload_or_writer_filler_timestamp = writer;
    timestamp_input.system_entry_timestamp = system;

    auto timestamp_result = TLogApiTimestampStabilizer::Stabilize(timestamp_config, timestamp_input);
    assert(timestamp_result.IsAccepted());

    TLogApiFinalEnvelope envelope{};
    envelope.header.id = TLogApiEnvelopeIdentityFactory::FromSequence(88);
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

    TLogApiEnvelopeExposureRequest exposure_request{};
    exposure_request.exposure_id = TLogApiEnvelopeExposureId{1};
    exposure_request.exposure_kind = TLogApiEnvelopeExposureKind::BindingView;
    exposure_request.envelope = &envelope;

    auto exposure = TLogApiEnvelopeExposureBuilder::Build(exposure_request);
    assert(exposure.IsAccepted());

    TLogApiCirculationHandoffRequest handoff{};
    handoff.id = TLogApiCirculationHandoffId{10};
    handoff.status = TLogApiCirculationHandoffStatus::Ready;
    handoff.expectation = TLogApiCirculationAdmissionExpectationKind::EnvelopeIntake;
    handoff.envelope_exposure = exposure.view;
    handoff.target = TLogApiDefaultCirculationHandoffProfile::MakeDefaultTarget();
    assert(handoff.IsReady());

    auto result = TLogApiCirculationHandoffContract::Submit(handoff);
    assert(result.IsAcceptedByContract());

    auto view = TLogApiCirculationHandoffView::From(handoff, result);
    assert(view.accepted_by_contract);
    assert(view.envelope_id == "logapi-final-envelope-88");
    assert(view.target_name == "default.circulation.intake");

    TLogApiCirculationHandoffRequest bad{};
    bad.id = TLogApiCirculationHandoffId{11};
    bad.status = TLogApiCirculationHandoffStatus::Ready;
    bad.expectation = TLogApiCirculationAdmissionExpectationKind::EnvelopeIntake;
    bad.target = TLogApiDefaultCirculationHandoffProfile::MakeDefaultTarget();

    auto rejected = TLogApiCirculationHandoffContract::Submit(bad);
    assert(!rejected.IsAcceptedByContract());
    assert(rejected.HasBlockingIssue());

    std::cout << "LOGAPI-W25 smoke test passed\\n";
    return 0;
}
