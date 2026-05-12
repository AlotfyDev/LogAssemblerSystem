#include <cassert>
#include <iostream>

#include "assembler/log_level_api/api_configurator/TLogApiConfigurationSurface.hpp"
#include "assembler/log_level_api/api_facade/TLogApiFacadeSurface.hpp"
#include "assembler/log_level_api/content/TLogApiContentProfileSurface.hpp"
#include "assembler/log_level_api/envelope_assembler/TLogApiEnvelopeAssemblerSurface.hpp"
#include "assembler/log_level_api/envelope_assembler/final_envelope_bridge/TLogApiFinalEnvelopeAssemblerBridgeSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

int main() {
    using namespace assembler::log_level_api::api_configurator;
    using namespace assembler::log_level_api::api_facade;
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::envelope_assembler;
    using namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::timestamp_stabilizer;
    using namespace assembler::log_level_api::validator;

    TLogApiDefaultConfiguration defaults{};
    TLogApiConfigurationPatch patch{};
    patch.assembler_family = TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler;
    patch.validation_required = false;
    patch.validator_binding_name = std::string{};
    auto config = TLogApiConfigurator::Resolve(defaults, patch);
    assert(config.IsAccepted());

    const char payload[] = "final-bridge-payload";
    TLogApiFacadeAcceptedContent accepted{};
    accepted.content = TLogApiContentInputRef{payload, sizeof(payload)};
    accepted.active_profile = &config.profile;
    assert(accepted.IsValid());

    auto metadata_config = TLogApiDefaultMetadataProfile::Make();
    auto metadata = TLogApiMetadataInjector::Prepare(metadata_config);
    assert(metadata.IsAccepted());

    auto timestamp_config = TLogApiDefaultTimestampProfile::Make();
    TLogApiTimestampValue writer{1000, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::WriterFillerProvided, true};
    TLogApiTimestampValue system{1100, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::SystemProvided, true};
    TLogApiTimestampStabilizationInput ts_input{};
    ts_input.payload_or_writer_filler_timestamp = writer;
    ts_input.system_entry_timestamp = system;
    auto ts = TLogApiTimestampStabilizer::Stabilize(timestamp_config, ts_input);
    assert(ts.IsAccepted());

    TLogApiEnvelopeAssemblyInput assembly_input{};
    assembly_input.accepted_content = accepted;
    assembly_input.metadata = metadata.block;
    assembly_input.timestamp = ts.timestamp;
    assembly_input.validation_present = false;

    auto assembly_profile = TLogApiEnvelopeAssemblyProfile::FromActiveProfile(config.profile);
    assert(assembly_profile.family == TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler);

    auto bridge_profile = TLogApiDefaultFinalEnvelopeAssemblerBridgeProfile::Make(assembly_profile);
    assert(bridge_profile.IsReady());

    TLogApiFinalEnvelopeAssemblyBridgeInput bridge_input{};
    bridge_input.assembly_input = assembly_input;

    auto final_result = TLogApiPlainFinalEnvelopeAssemblerBridge::Assemble(bridge_profile, bridge_input, 55);
    assert(final_result.IsAccepted());
    assert(final_result.final_envelope_result.envelope.IsWellShaped());
    assert(final_result.final_envelope_result.envelope.header.id.value == 55);
    assert(final_result.final_envelope_result.envelope.validation_slot.outcome == assembler::log_level_api::envelope::final_shape::TLogApiValidationOutcomeKind::NotEvaluated);

    auto view = TLogApiFinalEnvelopeAssemblerBridgeView::From(bridge_profile, final_result);
    assert(view.accepted);
    assert(view.envelope_id == "logapi-final-envelope-55");

    TLogApiConfigurationPatch vpatch{};
    vpatch.assembler_family = TLogApiAssemblerFamilyKind::ValidatorComposedEnvelopeAssembler;
    vpatch.validation_required = true;
    auto vconfig = TLogApiConfigurator::Resolve(defaults, vpatch);
    assert(vconfig.IsAccepted());

    TLogApiFacadeAcceptedContent vaccepted{};
    vaccepted.content = TLogApiContentInputRef{payload, sizeof(payload)};
    vaccepted.active_profile = &vconfig.profile;

    TLogApiEnvelopeAssemblyInput vinput{};
    vinput.accepted_content = vaccepted;
    vinput.metadata = metadata.block;
    vinput.timestamp = ts.timestamp;
    vinput.validation = TLogApiValidationResult::Accepted();
    vinput.validation_present = true;

    auto vassembly_profile = TLogApiEnvelopeAssemblyProfile::FromActiveProfile(vconfig.profile);
    auto vbridge_profile = TLogApiDefaultFinalEnvelopeAssemblerBridgeProfile::Make(vassembly_profile);
    TLogApiFinalEnvelopeAssemblyBridgeInput vbridge_input{};
    vbridge_input.assembly_input = vinput;

    auto vfinal = TLogApiValidatorComposedFinalEnvelopeAssemblerBridge::Assemble(vbridge_profile, vbridge_input, 56);
    assert(vfinal.IsAccepted());
    assert(vfinal.final_envelope_result.envelope.validation_slot.outcome == assembler::log_level_api::envelope::final_shape::TLogApiValidationOutcomeKind::Valid);

    std::cout << "LOGAPI-EXT-W02 smoke test passed\\n";
    return 0;
}
