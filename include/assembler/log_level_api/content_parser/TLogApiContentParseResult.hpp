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

#include <vector>

#include "TLogApiContentParserIssue.hpp"
#include "TLogApiParsedContentRef.hpp"

namespace assembler::log_level_api::content_parser {

struct TLogApiContentParseResult final {
    TLogApiParsedContentRef parsed_content{};
    std::vector<TLogApiContentParserIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return parsed_content.IsPresent() && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::content_parser
