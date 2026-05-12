#pragma once

/*
    LOGAPI-W14 — Default JSON Level Parsers

    Responsibility:
        Define dedicated JSON parsers for each default Log Level API JSON schema:
        Trace, Debug, Info, Notice, Warning, Error, Critical, and Fatal.

    Boundary:
        This wave implements lightweight default JSON level parser skeletons only.
        It must not implement concrete validators, metadata injection, timestamp
        stabilization, envelope assembly, communication bindings, or policy assignment.

    Hot-path doctrine:
        Each log level has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include <vector>

#include "assembler/log_level_api/content_parser/TLogApiContentParseResult.hpp"

#include "TLogApiJsonParsedContent.hpp"
#include "TLogApiJsonParseIssue.hpp"

namespace assembler::log_level_api::content_parser::json_level_parsers {

struct TLogApiJsonParseResult final {
    assembler::log_level_api::content_parser::TLogApiContentParseResult core_result{};
    TLogApiJsonParsedContent parsed_json{};
    std::vector<TLogApiJsonParseIssue> json_issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (core_result.HasBlockingIssue()) return true;
        for (const auto& issue : json_issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return core_result.IsAccepted()
            && parsed_json.IsPresent()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::content_parser::json_level_parsers
