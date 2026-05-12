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

#include <string>

namespace assembler::log_level_api::content_parser::json_level_parsers {

struct TLogApiJsonParseIssue final {
    std::string code{};
    std::string message{};
    bool blocking{false};

    [[nodiscard]] bool HasIssue() const noexcept {
        return !code.empty() || !message.empty();
    }
};

} // namespace assembler::log_level_api::content_parser::json_level_parsers
