#include <cassert>
#include <iostream>

#include "assembler/log_level_api/api_configurator/TLogApiConfigurationSurface.hpp"
#include "assembler/log_level_api/api_facade/TLogApiFacadeSurface.hpp"
#include "assembler/log_level_api/content/TLogApiContentProfileSurface.hpp"
#include "assembler/log_level_api/envelope_assembler/TLogApiEnvelopeAssemblerSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

static assembler::log_level_api::timestamp_stabilizer::TLogApiStabilizedTimestamp make_timestamp() {
    using namespace assembler::log_level_api::timestamp_stabilizer;

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
    return ts_result.timestamp;
}

int main() {
    using namespace assembler::log_level_api::api_configurator;
    using namespace assembler::log_level_api::api_facade;
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::envelope_assembler;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::validator;

    auto default_config = TLogApiDefaultConfiguration{};
    auto config_result = TLogApiConfigurator::Resolve(default_config);
    assert(config_result.IsAccepted());

    auto content_registry = TLogApiContentProfileResolver::MakeDefaultRegistryView();
    const auto* content_profile = content_registry.FindByName(config_result.profile.content_profile_name);
    assert(content_profile != nullptr);

    auto validator_registry = TLogApiValidatorBindingResolver::MakeDefaultRegistryView();
    const auto* validator_binding = validator_registry.FindByName(config_result.profile.validator_binding_name);
    assert(validator_binding != nullptr);

    auto metadata_config = TLogApiDefaultMetadataProfile::Make();
    auto metadata_result = TLogApiMetadataInjector::Prepare(metadata_config);
    assert(metadata_result.IsAccepted());

    auto timestamp = make_timestamp();

    TLogApiFacadeConfigRef facade_config{};
    facade_config.active_profile = &config_result.profile;
    facade_config.content_profile = content_profile;
    facade_config.validator_binding = validator_binding;
    facade_config.metadata_config = &metadata_config;
    auto timestamp_config = assembler::log_level_api::timestamp_stabilizer::TLogApiDefaultTimestampProfile::Make();
    facade_config.timestamp_config = &timestamp_config;
    assert(facade_config.IsReady());

    const char payload[] = "{\"message\":\"hello assembler\"}";
    TLogApiContentOnlyInput input{};
    input.content = TLogApiContentInputRef{payload, sizeof(payload)};

    auto accepted = TLogApiFacade::AcceptContent(input, facade_config);
    assert(accepted.IsAccepted());

    TLogApiEnvelopeAssemblyInput assembly_input{};
    assembly_input.accepted_content = accepted.accepted_content;
    assembly_input.metadata = metadata_result.block;
    assembly_input.timestamp = timestamp;
    assembly_input.validation = TLogApiValidationResult::Accepted();
    assembly_input.validation_present = true;

    auto assembly_profile = TLogApiEnvelopeAssemblyProfile::FromActiveProfile(config_result.profile);
    assert(assembly_profile.IsResolved());
    assert(assembly_profile.family == TLogApiAssemblerFamilyKind::ValidatorComposedEnvelopeAssembler);

    auto validator_assembled = TValidatorComposedLogApiEnvelopeAssembler::Assemble(assembly_profile, assembly_input);
    assert(validator_assembled.IsAccepted());
    assert(validator_assembled.envelope_result.envelope.validation.present);

    TLogApiConfigurationPatch patch{};
    patch.assembler_family = TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler;
    patch.validation_required = false;
    patch.validator_binding_name = std::string{};

    auto plain_config = TLogApiConfigurator::Resolve(default_config, patch);
    assert(plain_config.IsAccepted());

    auto plain_profile = TLogApiEnvelopeAssemblyProfile::FromActiveProfile(plain_config.profile);
    assert(plain_profile.IsResolved());
    assert(plain_profile.family == TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler);

    TLogApiEnvelopeAssemblyInput plain_input = assembly_input;
    plain_input.accepted_content.active_profile = &plain_config.profile;
    plain_input.validation_present = false;

    auto plain_assembled = TPlainLogApiEnvelopeAssembler::Assemble(plain_profile, plain_input);
    assert(plain_assembled.IsAccepted());
    assert(!plain_assembled.envelope_result.envelope.validation.present);

    auto view = TLogApiEnvelopeAssemblerView::From(assembly_profile);
    assert(view.resolved);
    assert(view.family == "validator_composed_envelope_assembler");

    std::cout << "LOGAPI-W08 smoke test passed\\n";
    return 0;
}
