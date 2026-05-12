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

#include <string>

#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructLevelSchemaDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"

namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers {

struct TLogApiCStructLevelParserProfile final {
    std::string parser_name{};
    const assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructLevelSchemaDescriptor* schema{nullptr};
    const assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor* binding{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return !parser_name.empty()
            && schema != nullptr
            && schema->IsDeclared()
            && binding != nullptr
            && binding->IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers
