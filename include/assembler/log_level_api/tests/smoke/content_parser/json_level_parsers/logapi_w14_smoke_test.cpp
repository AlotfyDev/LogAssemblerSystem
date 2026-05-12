#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/json_schemas/TLogApiJsonSchemaSurface.hpp"
#include "assembler/log_level_api/content_parser/json_level_parsers/TLogApiJsonLevelParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::content::json_schemas;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::content_parser::json_level_parsers;

    auto pack = TLogApiDefaultJsonSchemaFactory::MakeDefaultPack();
    const auto* info_schema = pack.FindByLevel(TLogApiLogLevelKind::Info);
    assert(info_schema != nullptr);

    auto binding = TLogApiJsonLevelParserProfileFactory::MakeBinding(
        "default.json.info.parser.binding",
        "default.json.info.parser",
        "default.json.info",
        "default.json.minimal"
    );

    TLogApiJsonLevelParserProfile profile{};
    profile.parser_name = "default.json.info.parser";
    profile.schema = info_schema;
    profile.binding = &binding;
    assert(profile.IsReady());

    const char payload[] = "{\"message\":\"Order accepted\",\"code\":\"A1024\",\"context\":\"unit-test\"}";
    TLogApiContentInputRef content{payload, sizeof(payload)};

    TLogApiContentParseRequest request{};
    request.content = content;
    request.parser_binding = &binding;
    assert(request.IsReady());

    auto result = TInfoJsonContentParser::Parse(request, profile);
    assert(result.IsAccepted());
    assert(result.parsed_json.message.value == "Order accepted");
    assert(result.parsed_json.level.value == "info");
    assert(result.parsed_json.level.defaulted);
    assert(result.parsed_json.code.value == "A1024");
    assert(result.parsed_json.context.value == "unit-test");
    assert(result.core_result.parsed_content.parsed);
    assert(result.core_result.parsed_content.parsed_kind == TLogApiParsedContentKind::JsonFieldView);

    const auto* fatal_schema = pack.FindByLevel(TLogApiLogLevelKind::Fatal);
    assert(fatal_schema != nullptr);

    auto fatal_binding = TLogApiJsonLevelParserProfileFactory::MakeBinding(
        "default.json.fatal.parser.binding",
        "default.json.fatal.parser",
        "default.json.fatal",
        "default.json.minimal"
    );

    TLogApiJsonLevelParserProfile fatal_profile{};
    fatal_profile.parser_name = "default.json.fatal.parser";
    fatal_profile.schema = fatal_schema;
    fatal_profile.binding = &fatal_binding;

    const char fatal_payload[] = "{\"message\":\"Terminal failure\"}";
    TLogApiContentParseRequest fatal_request{};
    fatal_request.content = TLogApiContentInputRef{fatal_payload, sizeof(fatal_payload)};
    fatal_request.parser_binding = &fatal_binding;

    auto fatal_result = TFatalJsonContentParser::Parse(fatal_request, fatal_profile);
    assert(fatal_result.IsAccepted());
    assert(fatal_result.parsed_json.level.value == "fatal");

    std::cout << "LOGAPI-W14 smoke test passed\\n";
    return 0;
}
