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

#include <string>

#include "TLogApiContentParserBindingDescriptor.hpp"

namespace assembler::log_level_api::content_parser {

struct TLogApiContentParserBindingView final {
    std::string binding_name{};
    std::string parser_name{};
    std::string content_profile_name{};
    std::string parser_kind{};
    bool resolved{false};
    bool opaque_no_parse{false};

    [[nodiscard]] static TLogApiContentParserBindingView From(const TLogApiContentParserBindingDescriptor& d) {
        TLogApiContentParserBindingView view{};
        view.binding_name = d.binding_name;
        view.parser_name = d.profile.parser_name;
        view.content_profile_name = d.profile.supported_content_profile_name;
        view.resolved = d.IsResolved();
        view.opaque_no_parse = d.profile.IsOpaqueNoParse();

        switch (d.profile.parser_kind) {
            case TLogApiContentParserKind::OpaqueNoParse: view.parser_kind = "opaque_no_parse"; break;
            case TLogApiContentParserKind::JsonLevelSpecific: view.parser_kind = "json_level_specific"; break;
            case TLogApiContentParserKind::CStyleStructPrimitiveLevelSpecific: view.parser_kind = "cstyle_struct_primitive_level_specific"; break;
            case TLogApiContentParserKind::Mt5StructureSpecific: view.parser_kind = "mt5_structure_specific"; break;
            case TLogApiContentParserKind::ExternalSchemaSpecific: view.parser_kind = "external_schema_specific"; break;
            default: view.parser_kind = "unknown"; break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::content_parser
