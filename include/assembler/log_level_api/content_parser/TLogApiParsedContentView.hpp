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

#include "TLogApiParsedContentRef.hpp"

namespace assembler::log_level_api::content_parser {

struct TLogApiParsedContentView final {
    std::string parsed_kind{};
    bool parsed{false};
    bool opaque{false};
    bool source_present{false};

    [[nodiscard]] static TLogApiParsedContentView From(const TLogApiParsedContentRef& ref) {
        TLogApiParsedContentView view{};
        view.parsed = ref.parsed;
        view.opaque = ref.IsOpaque();
        view.source_present = ref.source_content.IsPresent();

        switch (ref.parsed_kind) {
            case TLogApiParsedContentKind::OpaqueContentRef: view.parsed_kind = "opaque_content_ref"; break;
            case TLogApiParsedContentKind::JsonFieldView: view.parsed_kind = "json_field_view"; break;
            case TLogApiParsedContentKind::CStructFieldView: view.parsed_kind = "cstruct_field_view"; break;
            case TLogApiParsedContentKind::Mt5StructureView: view.parsed_kind = "mt5_structure_view"; break;
            case TLogApiParsedContentKind::ExternalParsedView: view.parsed_kind = "external_parsed_view"; break;
            default: view.parsed_kind = "unknown"; break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::content_parser
