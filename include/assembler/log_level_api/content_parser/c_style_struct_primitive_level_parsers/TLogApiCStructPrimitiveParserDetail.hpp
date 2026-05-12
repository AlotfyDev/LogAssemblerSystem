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
#include <cstring>
#include <string_view>
#include <variant>

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructEndianKind.hpp"
#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructFieldDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParseRequest.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

#include "TLogApiCStructLevelParserProfile.hpp"
#include "TLogApiCStructParseResult.hpp"

namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers::detail {

[[nodiscard]] inline bool Fits(
    const assembler::log_level_api::content::TLogApiContentInputRef& input,
    std::uint32_t offset,
    std::uint32_t size
) noexcept {
    return input.IsPresent()
        && static_cast<std::uint64_t>(offset) + static_cast<std::uint64_t>(size) <= input.size_bytes;
}

[[nodiscard]] inline const std::uint8_t* Bytes(const assembler::log_level_api::content::TLogApiContentInputRef& input) noexcept {
    return static_cast<const std::uint8_t*>(input.data);
}

[[nodiscard]] inline std::uint64_t ReadUnsigned(
    const assembler::log_level_api::content::TLogApiContentInputRef& input,
    std::uint32_t offset,
    std::uint32_t size,
    assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructEndianKind endian
) noexcept {
    const auto* data = Bytes(input);
    std::uint64_t value = 0;

    if (endian == assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructEndianKind::LittleEndian) {
        for (std::uint32_t i = 0; i < size; ++i) {
            value |= static_cast<std::uint64_t>(data[offset + i]) << (8u * i);
        }
    } else {
        for (std::uint32_t i = 0; i < size; ++i) {
            value = (value << 8u) | static_cast<std::uint64_t>(data[offset + i]);
        }
    }

    return value;
}

[[nodiscard]] inline std::int64_t SignExtend(std::uint64_t value, std::uint32_t size) noexcept {
    const std::uint32_t bits = size * 8u;
    if (bits == 64u) return static_cast<std::int64_t>(value);
    const std::uint64_t sign_bit = std::uint64_t{1} << (bits - 1u);
    if ((value & sign_bit) == 0) return static_cast<std::int64_t>(value);
    const std::uint64_t mask = (~std::uint64_t{0}) << bits;
    return static_cast<std::int64_t>(value | mask);
}

[[nodiscard]] inline TLogApiCStructParsedField ParseField(
    const assembler::log_level_api::content::TLogApiContentInputRef& input,
    const assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructFieldDescriptor& descriptor,
    assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructEndianKind endian
) {
    using namespace assembler::log_level_api::content::c_style_struct_primitives;

    TLogApiCStructParsedField field{};
    field.field_name = descriptor.field_name;
    field.primitive_kind = descriptor.layout.primitive_kind;

    if (!Fits(input, descriptor.layout.offset_bytes, descriptor.layout.size_bytes)) {
        return field;
    }

    if (descriptor.presence == TLogApiCStructFieldPresenceKind::Defaulted && descriptor.default_value.IsPresent()) {
        field.defaulted = true;
        if (std::holds_alternative<std::uint64_t>(descriptor.default_value.value)) {
            field.value = std::get<std::uint64_t>(descriptor.default_value.value);
        } else if (std::holds_alternative<std::int64_t>(descriptor.default_value.value)) {
            field.value = std::get<std::int64_t>(descriptor.default_value.value);
        } else if (std::holds_alternative<double>(descriptor.default_value.value)) {
            field.value = std::get<double>(descriptor.default_value.value);
        } else if (std::holds_alternative<bool>(descriptor.default_value.value)) {
            field.value = std::get<bool>(descriptor.default_value.value);
        } else {
            field.defaulted = false;
        }
        return field;
    }

    if (descriptor.presence == TLogApiCStructFieldPresenceKind::Reserved) {
        return field;
    }

    const auto raw = ReadUnsigned(input, descriptor.layout.offset_bytes, descriptor.layout.size_bytes, endian);

    switch (descriptor.layout.primitive_kind) {
        case TLogApiCStructPrimitiveKind::UInt8:
        case TLogApiCStructPrimitiveKind::UInt16:
        case TLogApiCStructPrimitiveKind::UInt32:
        case TLogApiCStructPrimitiveKind::UInt64:
            field.value = raw;
            field.present = true;
            break;

        case TLogApiCStructPrimitiveKind::Int8:
        case TLogApiCStructPrimitiveKind::Int16:
        case TLogApiCStructPrimitiveKind::Int32:
        case TLogApiCStructPrimitiveKind::Int64:
            field.value = SignExtend(raw, descriptor.layout.size_bytes);
            field.present = true;
            break;

        case TLogApiCStructPrimitiveKind::Bool8:
            field.value = static_cast<bool>(raw != 0);
            field.present = true;
            break;

        default:
            break;
    }

    return field;
}


[[nodiscard]] inline const assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructFieldDescriptor* FindField(
    const assembler::log_level_api::content::c_style_struct_primitives::TLogApiCStructLevelSchemaDescriptor& schema,
    const char* field_name
) noexcept {
    for (const auto& field : schema.layout.fields) {
        if (field.field_name == field_name) return &field;
    }
    return nullptr;
}

[[nodiscard]] inline TLogApiCStructParseResult ParseKnownDefaultCStruct(
    const assembler::log_level_api::content_parser::TLogApiContentParseRequest& request,
    const TLogApiCStructLevelParserProfile& profile
) {
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::content::c_style_struct_primitives;

    TLogApiCStructParseResult result{};

    if (!request.IsReady() || !profile.IsReady()) {
        result.struct_issues.push_back({"LOGAPI_CSTRUCT_PARSE_NOT_READY", "C-style struct parser request/profile is not ready.", true});
        return result;
    }

    if (request.content.size_bytes < profile.schema->layout.total_size_bytes) {
        result.struct_issues.push_back({"LOGAPI_CSTRUCT_BUFFER_TOO_SMALL", "Input buffer is smaller than the declared schema layout.", true});
        return result;
    }

    result.parsed_struct.source = request.content;
    result.parsed_struct.schema = profile.schema;

    const auto endian = profile.schema->layout.endian;

    if (const auto* f = FindField(*profile.schema, "schema_marker")) {
        result.parsed_struct.schema_marker = ParseField(request.content, *f, endian);
    }
    if (const auto* f = FindField(*profile.schema, "level_code")) {
        result.parsed_struct.level_code = ParseField(request.content, *f, endian);
    }
    if (const auto* f = FindField(*profile.schema, "flags")) {
        result.parsed_struct.flags = ParseField(request.content, *f, endian);
    }
    if (const auto* f = FindField(*profile.schema, "message_id")) {
        result.parsed_struct.message_id = ParseField(request.content, *f, endian);
    }
    if (const auto* f = FindField(*profile.schema, "numeric_code")) {
        result.parsed_struct.numeric_code = ParseField(request.content, *f, endian);
    }
    if (const auto* f = FindField(*profile.schema, "payload_timestamp")) {
        result.parsed_struct.payload_timestamp = ParseField(request.content, *f, endian);
    }

    if (!result.parsed_struct.IsPresent()) {
        result.struct_issues.push_back({"LOGAPI_CSTRUCT_REQUIRED_FIELDS_MISSING", "Required C-style struct fields are missing or unreadable.", true});
        return result;
    }

    result.core_result.parsed_content.parsed_kind = TLogApiParsedContentKind::CStructFieldView;
    result.core_result.parsed_content.source_content = request.content;
    result.core_result.parsed_content.parsed = true;

    return result;
}

} // namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers::detail
