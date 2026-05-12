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

#include "TLogApiContentParserCapabilitySet.hpp"
#include "TLogApiContentParserId.hpp"
#include "TLogApiContentParserInputKind.hpp"
#include "TLogApiContentParserKind.hpp"
#include "TLogApiContentParserStatus.hpp"
#include "TLogApiParsedContentKind.hpp"

namespace assembler::log_level_api::content_parser {

/*
    Parser profile.

    This profile must be resolved during configuration. The hot path must not
    choose between parser kinds dynamically.
*/
struct TLogApiContentParserProfile final {
    TLogApiContentParserId id{};
    TLogApiContentParserStatus status{TLogApiContentParserStatus::Unknown};

    TLogApiContentParserKind parser_kind{TLogApiContentParserKind::Unknown};
    TLogApiContentParserInputKind input_kind{TLogApiContentParserInputKind::Unknown};
    TLogApiParsedContentKind output_kind{TLogApiParsedContentKind::Unknown};

    std::string parser_name{};
    std::string supported_content_profile_name{};
    std::string supported_schema_name{};

    TLogApiContentParserCapabilitySet capabilities{};

    [[nodiscard]] bool IsResolved() const noexcept {
        if (!id.IsValid()) return false;
        if (status != TLogApiContentParserStatus::Resolved
            && status != TLogApiContentParserStatus::Active) return false;
        if (parser_kind == TLogApiContentParserKind::Unknown) return false;
        if (input_kind == TLogApiContentParserInputKind::Unknown) return false;
        if (output_kind == TLogApiParsedContentKind::Unknown) return false;
        if (parser_name.empty()) return false;
        if (supported_content_profile_name.empty()) return false;
        if (!capabilities.Supports(TLogApiContentParserCapabilityKind::ProduceParsedContentRef)) return false;
        return true;
    }

    [[nodiscard]] bool IsOpaqueNoParse() const noexcept {
        return parser_kind == TLogApiContentParserKind::OpaqueNoParse
            && output_kind == TLogApiParsedContentKind::OpaqueContentRef;
    }
};

} // namespace assembler::log_level_api::content_parser
