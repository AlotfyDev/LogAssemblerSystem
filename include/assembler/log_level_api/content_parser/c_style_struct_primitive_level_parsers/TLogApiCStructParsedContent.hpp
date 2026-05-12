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

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructLevelSchemaDescriptor.hpp"

#include "TLogApiCStructParsedField.hpp"

namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers {

/*
    Parsed content view for default C-style struct primitive schemas.

    This is content-only. Metadata and stabilized timestamp remain outside this view.
*/
struct TLogApiCStructParsedContent final {
    assembler::log_level_api::content::TLogApiContentInputRef source{};
    const assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructLevelSchemaDescriptor* schema{nullptr};

    TLogApiCStructParsedField schema_marker{};
    TLogApiCStructParsedField level_code{};
    TLogApiCStructParsedField flags{};
    TLogApiCStructParsedField message_id{};
    TLogApiCStructParsedField numeric_code{};
    TLogApiCStructParsedField payload_timestamp{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return source.IsPresent()
            && schema != nullptr
            && schema->IsDeclared()
            && schema_marker.IsUsable()
            && level_code.IsUsable()
            && message_id.IsUsable();
    }
};

} // namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers
