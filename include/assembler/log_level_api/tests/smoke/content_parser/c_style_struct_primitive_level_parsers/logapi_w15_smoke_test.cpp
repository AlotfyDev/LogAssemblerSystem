#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "assembler/log_level_api/content/c_style_struct_primitives/TLogApiCStructPrimitiveSchemaSurface.hpp"
#include "assembler/log_level_api/content_parser/c_style_struct_primitive_level_parsers/TLogApiCStructPrimitiveLevelParserSurface.hpp"

static void put_le(std::vector<unsigned char>& buffer, std::size_t offset, std::uint64_t value, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        buffer[offset + i] = static_cast<unsigned char>((value >> (8u * i)) & 0xffu);
    }
}

int main() {
    using namespace assembler::log_level_api::content;
    using namespace assembler::log_level_api::content::c_style_struct_primitives;
    using namespace assembler::log_level_api::content_parser;
    using namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers;

    auto pack = TLogApiDefaultCStructSchemaFactory::MakeDefaultPack();
    const auto* info_schema = pack.FindByLevel(TLogApiCStructLogLevelKind::Info);
    assert(info_schema != nullptr);
    assert(info_schema->IsDeclared());

    std::vector<unsigned char> buffer(128, 0);
    put_le(buffer, 0, 0xCAFE, 2);     // schema_marker
    buffer[2] = 0;                    // level_code ignored, schema default wins
    buffer[3] = 3;                    // flags
    put_le(buffer, 4, 1024, 4);       // message_id
    put_le(buffer, 8, 77, 8);         // numeric_code
    put_le(buffer, 16, 123456, 8);    // payload_timestamp

    TLogApiContentInputRef content{buffer.data(), buffer.size()};

    auto binding = TLogApiCStructLevelParserProfileFactory::MakeBinding(
        "default.cstruct.info.parser.binding",
        "default.cstruct.info.parser",
        "default.cstruct.info",
        "default.c_style_struct_primitives.minimal"
    );

    TLogApiCStructLevelParserProfile profile{};
    profile.parser_name = "default.cstruct.info.parser";
    profile.schema = info_schema;
    profile.binding = &binding;
    assert(profile.IsReady());

    TLogApiContentParseRequest request{};
    request.content = content;
    request.parser_binding = &binding;
    assert(request.IsReady());

    auto result = TInfoCStructPrimitiveParser::Parse(request, profile);
    assert(result.IsAccepted());
    assert(result.parsed_struct.schema_marker.present);
    assert(std::get<std::uint64_t>(result.parsed_struct.schema_marker.value) == 0xCAFE);
    assert(result.parsed_struct.level_code.defaulted);
    assert(std::get<std::uint64_t>(result.parsed_struct.level_code.value) == static_cast<std::uint64_t>(TLogApiCStructLogLevelKind::Info));
    assert(result.parsed_struct.message_id.present);
    assert(std::get<std::uint64_t>(result.parsed_struct.message_id.value) == 1024);
    assert(result.parsed_struct.numeric_code.present);
    assert(std::get<std::int64_t>(result.parsed_struct.numeric_code.value) == 77);
    assert(result.parsed_struct.payload_timestamp.present);
    assert(std::get<std::int64_t>(result.parsed_struct.payload_timestamp.value) == 123456);
    assert(result.core_result.parsed_content.parsed_kind == TLogApiParsedContentKind::CStructFieldView);

    const auto* fatal_schema = pack.FindByLevel(TLogApiCStructLogLevelKind::Fatal);
    assert(fatal_schema != nullptr);

    auto fatal_binding = TLogApiCStructLevelParserProfileFactory::MakeBinding(
        "default.cstruct.fatal.parser.binding",
        "default.cstruct.fatal.parser",
        "default.cstruct.fatal",
        "default.c_style_struct_primitives.minimal"
    );

    TLogApiCStructLevelParserProfile fatal_profile{};
    fatal_profile.parser_name = "default.cstruct.fatal.parser";
    fatal_profile.schema = fatal_schema;
    fatal_profile.binding = &fatal_binding;

    TLogApiContentParseRequest fatal_request{};
    fatal_request.content = content;
    fatal_request.parser_binding = &fatal_binding;

    auto fatal_result = TFatalCStructPrimitiveParser::Parse(fatal_request, fatal_profile);
    assert(fatal_result.IsAccepted());
    assert(fatal_result.parsed_struct.level_code.defaulted);
    assert(std::get<std::uint64_t>(fatal_result.parsed_struct.level_code.value) == static_cast<std::uint64_t>(TLogApiCStructLogLevelKind::Fatal));

    std::cout << "LOGAPI-W15 smoke test passed\\n";
    return 0;
}
