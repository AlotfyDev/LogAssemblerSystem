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

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"

#include "TLogApiParsedContentKind.hpp"

namespace assembler::log_level_api::content_parser {

/*
    Parsed content reference.

    It may remain an opaque content reference if the active parser profile is
    OpaqueNoParse. It must not carry metadata or stabilized timestamp.
*/
struct TLogApiParsedContentRef final {
    TLogApiParsedContentKind parsed_kind{TLogApiParsedContentKind::Unknown};
    assembler::log_level_api::content::TLogApiContentInputRef source_content{};
    bool parsed{false};

    [[nodiscard]] bool IsPresent() const noexcept {
        return source_content.IsPresent()
            && parsed_kind != TLogApiParsedContentKind::Unknown;
    }

    [[nodiscard]] bool IsOpaque() const noexcept {
        return parsed_kind == TLogApiParsedContentKind::OpaqueContentRef;
    }
};

} // namespace assembler::log_level_api::content_parser
