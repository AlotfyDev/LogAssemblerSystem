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

#include "TLogApiContentParseRequest.hpp"
#include "TLogApiContentParseResult.hpp"

namespace assembler::log_level_api::content_parser {

/*
    First-class no-parse / opaque parser.

    This parser preserves payload bytes/text as an opaque content reference.
    It is still selected through configuration and must not be chosen by hot-path
    discovery.
*/
class TLogApiOpaqueContentParser final {
public:
    [[nodiscard]] static TLogApiContentParseResult Parse(const TLogApiContentParseRequest& request) {
        TLogApiContentParseResult result{};

        if (!request.IsReady()) {
            result.issues.push_back({
                "LOGAPI_PARSE_REQUEST_NOT_READY",
                "Content parse request requires content and a resolved parser binding.",
                true
            });
            return result;
        }

        if (!request.parser_binding->profile.IsOpaqueNoParse()) {
            result.issues.push_back({
                "LOGAPI_PARSE_PROFILE_NOT_OPAQUE",
                "Opaque parser requires an OpaqueNoParse parser profile.",
                true
            });
            return result;
        }

        result.parsed_content.parsed_kind = TLogApiParsedContentKind::OpaqueContentRef;
        result.parsed_content.source_content = request.content;
        result.parsed_content.parsed = false;
        return result;
    }
};

} // namespace assembler::log_level_api::content_parser
