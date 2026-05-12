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
#include <string_view>

#include "assembler/log_level_api/content/TLogApiContentInputRef.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParseRequest.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

#include "TLogApiJsonLevelParserProfile.hpp"
#include "TLogApiJsonParseResult.hpp"

namespace assembler::log_level_api::content_parser::json_level_parsers::detail {

[[nodiscard]] inline std::string_view ToView(const assembler::log_level_api::content::TLogApiContentInputRef& input) {
    return std::string_view{static_cast<const char*>(input.data), input.size_bytes};
}

/*
    Minimal hot-path-friendly string extractor for default schemas.

    This is intentionally not a general JSON parser. It only extracts simple
    string-like values for known default schema fields.
*/
[[nodiscard]] inline TLogApiJsonParsedField ExtractSimpleField(std::string_view text, const char* name) {
    TLogApiJsonParsedField field{};
    field.field_name = name;

    std::string key = "\"";
    key += name;
    key += "\"";

    auto pos = text.find(key);
    if (pos == std::string_view::npos) return field;

    auto colon = text.find(':', pos + key.size());
    if (colon == std::string_view::npos) return field;

    auto begin = text.find_first_not_of(" \t\r\n", colon + 1);
    if (begin == std::string_view::npos) return field;

    if (text[begin] == '"') {
        auto end = text.find('"', begin + 1);
        if (end == std::string_view::npos) return field;
        field.value = std::string{text.substr(begin + 1, end - begin - 1)};
        field.present = true;
        return field;
    }

    auto end = text.find_first_of(",}\r\n", begin);
    if (end == std::string_view::npos) end = text.size();
    field.value = std::string{text.substr(begin, end - begin)};
    field.present = true;
    return field;
}

[[nodiscard]] inline TLogApiJsonParsedField DefaultLevelField(
    const assembler::log_level_api::content::json_schemas::TLogApiJsonLevelSchemaDescriptor& schema
) {
    TLogApiJsonParsedField field{};
    field.field_name = "level";
    field.defaulted = true;

    switch (schema.level) {
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Trace: field.value = "trace"; break;
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Debug: field.value = "debug"; break;
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Info: field.value = "info"; break;
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Notice: field.value = "notice"; break;
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Warning: field.value = "warning"; break;
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Error: field.value = "error"; break;
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Critical: field.value = "critical"; break;
        case assembler::log_level_api::content::json_schemas::TLogApiLogLevelKind::Fatal: field.value = "fatal"; break;
        default: field.value = "unknown"; field.defaulted = false; break;
    }

    return field;
}

[[nodiscard]] inline TLogApiJsonParseResult ParseKnownDefaultJson(
    const assembler::log_level_api::content_parser::TLogApiContentParseRequest& request,
    const TLogApiJsonLevelParserProfile& profile
) {
    using namespace assembler::log_level_api::content_parser;

    TLogApiJsonParseResult result{};

    if (!request.IsReady() || !profile.IsReady()) {
        result.json_issues.push_back({"LOGAPI_JSON_PARSE_NOT_READY", "JSON parser request/profile is not ready.", true});
        return result;
    }

    auto text = ToView(request.content);

    result.parsed_json.source = request.content;
    result.parsed_json.schema = profile.schema;
    result.parsed_json.message = ExtractSimpleField(text, "message");
    result.parsed_json.level = ExtractSimpleField(text, "level");

    if (!result.parsed_json.level.IsUsable()) {
        result.parsed_json.level = DefaultLevelField(*profile.schema);
    }

    result.parsed_json.code = ExtractSimpleField(text, "code");
    result.parsed_json.context = ExtractSimpleField(text, "context");
    result.parsed_json.payload_timestamp = ExtractSimpleField(text, "payload_timestamp");

    if (!result.parsed_json.message.IsUsable()) {
        result.json_issues.push_back({"LOGAPI_JSON_MESSAGE_MISSING", "Default JSON schema requires message.", true});
        return result;
    }

    result.core_result.parsed_content.parsed_kind = TLogApiParsedContentKind::JsonFieldView;
    result.core_result.parsed_content.source_content = request.content;
    result.core_result.parsed_content.parsed = true;

    return result;
}

} // namespace assembler::log_level_api::content_parser::json_level_parsers::detail
