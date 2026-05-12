#pragma once

/*
    LOGAPI-W15 — Default C-Style Struct Primitive Level Parsers

    Responsibility:
        Define dedicated parsers for each default C-style struct primitive
        log-level schema: Trace, Debug, Info, Notice, Warning, Error, Critical,
        and Fatal.

    Boundary:
        This wave implements lightweight default C-style struct primitive parser
        skeletons only. It must not implement validators, metadata injection,
        timestamp stabilization, envelope assembly, communication bindings,
        circulation handoff, or policy assignment.

    Hot-path doctrine:
        Each log level has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        C-style struct parsing uses explicit schema offsets and sizes, not
        compiler-implied struct layout.
*/

#include <vector>

#include "assembler/log_level_api/content_parser/TLogApiContentParseResult.hpp"

#include "TLogApiCStructParsedContent.hpp"
#include "TLogApiCStructParseIssue.hpp"

namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers {

struct TLogApiCStructParseResult final {
    assembler::log_level_api::content_parser::TLogApiContentParseResult core_result{};
    TLogApiCStructParsedContent parsed_struct{};
    std::vector<TLogApiCStructParseIssue> struct_issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (core_result.HasBlockingIssue()) return true;
        for (const auto& issue : struct_issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return core_result.IsAccepted()
            && parsed_struct.IsPresent()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers
