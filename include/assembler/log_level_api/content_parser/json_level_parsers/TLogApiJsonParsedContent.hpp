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

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content/json_schemas/TLogApiJsonLevelSchemaDescriptor.hpp"

#include "TLogApiJsonParsedField.hpp"

namespace assembler::log_level_api::content_parser::json_level_parsers {

/*
    Parsed JSON content view for default schemas.

    This is content-only. Metadata and stabilized timestamp remain outside this view.
*/
struct TLogApiJsonParsedContent final {
    assembler::log_level_api::content::TLogApiContentInputRef source{};
    const assembler::log_level_api::content::json_schemas::TLogApiJsonLevelSchemaDescriptor* schema{nullptr};

    TLogApiJsonParsedField message{};
    TLogApiJsonParsedField level{};
    TLogApiJsonParsedField code{};
    TLogApiJsonParsedField context{};
    TLogApiJsonParsedField payload_timestamp{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return source.IsPresent()
            && schema != nullptr
            && schema->IsDeclared()
            && message.IsUsable()
            && level.IsUsable();
    }
};

} // namespace assembler::log_level_api::content_parser::json_level_parsers
