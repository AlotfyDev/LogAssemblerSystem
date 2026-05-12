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

#include <cstdint>
#include <string>
#include <variant>

#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructFieldDescriptor.hpp"
#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructPrimitiveKind.hpp"

namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers {

using TLogApiCStructParsedValue = std::variant<
    std::monostate,
    std::uint64_t,
    std::int64_t,
    double,
    bool
>;

struct TLogApiCStructParsedField final {
    std::string field_name{};
    assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructPrimitiveKind primitive_kind{
        assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructPrimitiveKind::Unknown
    };
    TLogApiCStructParsedValue value{};
    bool present{false};
    bool defaulted{false};

    [[nodiscard]] bool IsUsable() const noexcept {
        return !field_name.empty() && (present || defaulted);
    }
};

} // namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers
