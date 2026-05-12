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

#include "assembler/log_level_api/content/json_schemas/TLogApiJsonLevelSchemaDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"

namespace assembler::log_level_api::content_parser::json_level_parsers {

struct TLogApiJsonLevelParserProfile final {
    std::string parser_name{};
    const assembler::log_level_api::content::json_schemas::TLogApiJsonLevelSchemaDescriptor* schema{nullptr};
    const assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor* binding{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return !parser_name.empty()
            && schema != nullptr
            && schema->IsDeclared()
            && binding != nullptr
            && binding->IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser::json_level_parsers
