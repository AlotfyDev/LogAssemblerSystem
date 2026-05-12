#pragma once

/*
    LOGAPI-W13 — Content Parser Core And Binding Surface

    Responsibility:
        Define the core content parser contract, parser binding surface, parser
        profile, parser result model, parsed content references/views, parser
        capabilities, and the opaque/no-parse profile.

    Boundary:
        This wave does not implement concrete JSON parsers, concrete C-style
        struct primitive parsers, MT5 parsers, concrete validators, metadata
        injection, timestamp stabilization, envelope assembly, circulation
        binding, or policy assignment.

    Doctrine:
        Parser selection is configuration-time.
        Parser execution is hot-path.
        Parser discovery is never hot-path.
        Opaque/NoParse is a first-class profile.
*/

#include "TLogApiContentParserBindingDescriptor.hpp"
#include "TLogApiContentParserCapabilityKind.hpp"
#include "TLogApiContentParserRegistryView.hpp"

namespace assembler::log_level_api::content_parser {

struct TLogApiDefaultParserProfiles final {
    [[nodiscard]] static TLogApiContentParserBindingDescriptor MakeOpaqueNoParseBinding() {
        TLogApiContentParserProfile profile{};
        profile.id = TLogApiContentParserId{1};
        profile.status = TLogApiContentParserStatus::Resolved;
        profile.parser_kind = TLogApiContentParserKind::OpaqueNoParse;
        profile.input_kind = TLogApiContentParserInputKind::OpaqueBytes;
        profile.output_kind = TLogApiParsedContentKind::OpaqueContentRef;
        profile.parser_name = "default.opaque.no_parse.parser";
        profile.supported_content_profile_name = "opaque.pass_through";
        profile.supported_schema_name = "none";
        profile.capabilities.capabilities = {
            TLogApiContentParserCapabilityKind::PreserveOpaquePayload,
            TLogApiContentParserCapabilityKind::ProduceParsedContentRef
        };

        TLogApiContentParserBindingDescriptor binding{};
        binding.binding_name = "default.opaque.no_parse.binding";
        binding.profile = profile;
        return binding;
    }

    [[nodiscard]] static TLogApiContentParserRegistryView MakeDefaultRegistryView() {
        TLogApiContentParserRegistryView view{};
        view.bindings.push_back(MakeOpaqueNoParseBinding());
        return view;
    }
};

} // namespace assembler::log_level_api::content_parser
