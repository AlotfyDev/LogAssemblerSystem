#include <cassert>
#include <iostream>

#include "assembler/log_level_api/api_configurator/TLogApiConfigurationSurface.hpp"
#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffContractSurface.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"
#include "assembler/log_level_api/public_api/TLogApiPublicApiSurface.hpp"

int main() {
    using namespace assembler::log_level_api::api_configurator;
    using namespace assembler::log_level_api::communication_bindings::circulation_handoff;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::public_api;

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
    assert(parser_binding->IsResolved());

    TLogApiPublicResolvedContext context{};
    context.active_profile = &active.profile;
    context.parser_binding = parser_binding;
    context.circulation_target = TLogApiDefaultCirculationHandoffProfile::MakeDefaultTarget();
    assert(context.IsReady());

    const char payload[] = "public-api-content-only";
    TLogApiPublicCallRequest request{};
    request.id = TLogApiPublicCallId{1};
    request.input_kind = TLogApiPublicInputKind::OpaquePayload;
    request.context = context;
    request.opaque.content = {payload, sizeof(payload)};

    assert(request.IsReady());

    auto result = TLogApiPublicApiFacade::AcceptOpaque(request);
    assert(result.IsAccepted());
    assert(result.parse_result.IsAccepted());
    assert(result.parse_result.parsed_content.IsOpaque());

    auto view = TLogApiPublicApiCallView::From(request, result);
    assert(view.accepted);
    assert(view.input_kind == "opaque_payload");
    assert(view.content_profile_name == "opaque.pass_through");
    assert(view.parser_name == "default.opaque.no_parse.parser");

    TLogApiPublicApiUsageModel usage{};
    assert(usage.supported_input_paths.size() == 3);
    assert(usage.forbidden_per_call_material.size() == 7);

    TLogApiPublicCallRequest bad{};
    bad.id = TLogApiPublicCallId{2};
    bad.input_kind = TLogApiPublicInputKind::JsonText;
    bad.context = context;

    auto rejected = TLogApiPublicApiFacade::AcceptOpaque(bad);
    assert(!rejected.IsAccepted());
    assert(rejected.HasBlockingIssue());

    std::cout << "LOGAPI-W27 smoke test passed\\n";
    return 0;
}
