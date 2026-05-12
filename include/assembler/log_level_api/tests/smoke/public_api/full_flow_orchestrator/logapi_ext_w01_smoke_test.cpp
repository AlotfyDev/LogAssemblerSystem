#include <cassert>
#include <iostream>

#include "assembler/log_level_api/api_configurator/TLogApiConfigurationSurface.hpp"
#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffContractSurface.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataSurface.hpp"
#include "assembler/log_level_api/public_api/TLogApiPublicApiSurface.hpp"
#include "assembler/log_level_api/public_api/full_flow_orchestrator/TLogApiPublicApiFullFlowSurface.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampSurface.hpp"

int main() {
    using namespace assembler::log_level_api::api_configurator;
    using namespace assembler::log_level_api::communication_bindings::circulation_handoff;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::metadata_injector;
    using namespace assembler::log_level_api::public_api;
    using namespace assembler::log_level_api::public_api::full_flow_orchestrator;
    using namespace assembler::log_level_api::timestamp_stabilizer;

    TLogApiDefaultConfiguration defaults{};
    TLogApiConfigurationPatch patch{};
    patch.content_profile_name = std::string{"opaque.pass_through"};
    patch.assembler_family = TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler;
    patch.validation_required = false;
    patch.validator_binding_name = std::string{};

    auto active = TLogApiConfigurator::Resolve(defaults, patch);
    assert(active.IsAccepted());

    auto parser_registry = TLogApiDefaultParserProfiles::MakeDefaultRegistryView();
    const auto* parser_binding = parser_registry.FindByName("default.opaque.no_parse.binding");
    assert(parser_binding != nullptr);

    auto metadata_config = TLogApiDefaultMetadataProfile::Make();
    assert(metadata_config.IsReady());

    auto timestamp_config = TLogApiDefaultTimestampProfile::Make();
    assert(timestamp_config.IsResolved());

    TLogApiPublicResolvedContext public_context{};
    public_context.active_profile = &active.profile;
    public_context.parser_binding = parser_binding;
    public_context.circulation_target = TLogApiDefaultCirculationHandoffProfile::MakeDefaultTarget();
    assert(public_context.IsReady());

    TLogApiFullFlowResolvedContext full_context{};
    full_context.public_context = public_context;
    full_context.metadata_config = &metadata_config;
    full_context.timestamp_config = &timestamp_config;
    assert(full_context.IsReady());

    const char payload[] = "full-flow-opaque-payload";

    TLogApiPublicCallRequest public_call{};
    public_call.id = TLogApiPublicCallId{1};
    public_call.input_kind = TLogApiPublicInputKind::OpaquePayload;
    public_call.context = public_context;
    public_call.opaque.content = {payload, sizeof(payload)};
    assert(public_call.IsReady());

    TLogApiTimestampValue writer{1000, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::WriterFillerProvided, true};
    TLogApiTimestampValue system{1100, TLogApiTimestampPrecisionKind::Milliseconds, TLogApiTimestampInputKind::SystemProvided, true};

    TLogApiTimestampStabilizationInput ts_input{};
    ts_input.payload_or_writer_filler_timestamp = writer;
    ts_input.system_entry_timestamp = system;

    TLogApiFullFlowRequest request{};
    request.run_id = TLogApiFullFlowRunId{77};
    request.public_call = public_call;
    request.resolved_context = full_context;
    request.timestamp_input = ts_input;
    request.validation_present = false;

    auto result = TLogApiPublicApiFullFlowOrchestrator::RunOpaqueNoParse(request);
    assert(result.IsAccepted());
    assert(result.parse_result.IsAccepted());
    assert(result.metadata_result.IsAccepted());
    assert(result.timestamp_result.IsAccepted());
    assert(result.envelope_result.IsAccepted());
    assert(result.exposure_result.IsAccepted());
    assert(result.handoff_result.IsAcceptedByContract());

    auto view = TLogApiPublicApiFullFlowView::From(request, result);
    assert(view.accepted);
    assert(view.status == "handoff_accepted");
    assert(view.envelope_id == "logapi-final-envelope-77");

    TLogApiFullFlowRequest bad = request;
    bad.resolved_context.public_context.parser_binding = nullptr;
    auto rejected = TLogApiPublicApiFullFlowOrchestrator::RunOpaqueNoParse(bad);
    assert(!rejected.IsAccepted());
    assert(rejected.HasBlockingIssue());

    std::cout << "LOGAPI-EXT-W01 smoke test passed\\n";
    return 0;
}
