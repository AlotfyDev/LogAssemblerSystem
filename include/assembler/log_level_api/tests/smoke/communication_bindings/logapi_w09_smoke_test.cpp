#include <cassert>
#include <iostream>

#include "assembler/log_level_api/api_configurator/TLogApiConfigurationSurface.hpp"
#include "assembler/log_level_api/api_facade/TLogApiFacadeSurface.hpp"
#include "assembler/log_level_api/communication_bindings/TLogApiCommunicationBindingSurface.hpp"
#include "assembler/log_level_api/content/TLogApiContentProfileSurface.hpp"
#include "assembler/log_level_api/envelope_assembler/TLogApiEnvelopeAssemblerSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorSurface.hpp"

using namespace assembler::log_level_api::api_configurator;
using namespace assembler::log_level_api::api_facade;
using namespace assembler::log_level_api::communication_bindings;
using namespace assembler::log_level_api::content;
using namespace assembler::log_level_api::envelope_assembler;
using namespace assembler::log_level_api::metadata_injector;
using namespace assembler::log_level_api::timestamp_stabilizer;
using namespace assembler::log_level_api::validator;

static TLogApiStabilizedTimestamp make_timestamp() {
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
    auto config_result = TLogApiConfigurator::Resolve(TLogApiDefaultConfiguration{});
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

    auto timestamp_config = TLogApiDefaultTimestampProfile::Make();
    TLogApiFacadeConfigRef facade_config{};
    facade_config.active_profile = &config_result.profile;
    facade_config.content_profile = content_profile;
    facade_config.validator_binding = validator_binding;
    facade_config.metadata_config = &metadata_config;
    facade_config.timestamp_config = &timestamp_config;
    assert(facade_config.IsReady());

    const char payload[] = "{\"message\":\"hello communication\"}";
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
    auto assembled = TValidatorComposedLogApiEnvelopeAssembler::Assemble(assembly_profile, assembly_input);
    assert(assembled.IsAccepted());

    auto binding = TLogApiDefaultCommunicationBindingProfile::Make();
    assert(binding.IsResolved());

    auto report = TLogApiCommunicationBinding::Inspect(binding);
    assert(!report.HasBlockingIssue());
    assert(report.view.resolved);
    assert(report.view.provider_name == "default.logapi.envelope.provider.plugin_adapter");
    assert(report.view.port_name == "default.circulation.envelope.intake.port_adapter");

    TLogApiCirculationHandoffRequest request{};
    request.envelope = &assembled.envelope_result.envelope;
    assert(request.HasEnvelope());

    auto handoff = TLogApiCommunicationBinding::PrepareHandoff(binding, request);
    assert(handoff.IsAccepted());

    std::cout << "LOGAPI-W09 smoke test passed\\n";
    return 0;
}
