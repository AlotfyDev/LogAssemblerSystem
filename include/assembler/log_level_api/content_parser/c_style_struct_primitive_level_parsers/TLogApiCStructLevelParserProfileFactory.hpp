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

#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserCapabilityKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserInputKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserStatus.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers {

class TLogApiCStructLevelParserProfileFactory final {
public:
    [[nodiscard]] static assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor MakeBinding(
        const char* binding_name,
        const char* parser_name,
        const char* supported_schema_name,
        const char* content_profile_name
    ) {
        using namespace assembler::log_level_api::content_parser;

        TLogApiContentParserProfile profile{};
        profile.id = TLogApiContentParserId{200};
        profile.status = TLogApiContentParserStatus::Resolved;
        profile.parser_kind = TLogApiContentParserKind::CStyleStructPrimitiveLevelSpecific;
        profile.input_kind = TLogApiContentParserInputKind::BinaryStructBuffer;
        profile.output_kind = TLogApiParsedContentKind::CStructFieldView;
        profile.parser_name = parser_name;
        profile.supported_content_profile_name = content_profile_name;
        profile.supported_schema_name = supported_schema_name;
        profile.capabilities.capabilities = {
            TLogApiContentParserCapabilityKind::ProduceParsedContentRef,
            TLogApiContentParserCapabilityKind::ProduceLevelFieldView,
            TLogApiContentParserCapabilityKind::ProduceMessageFieldView,
            TLogApiContentParserCapabilityKind::ProducePayloadTimestampView,
            TLogApiContentParserCapabilityKind::ReportParseIssues
        };

        TLogApiContentParserBindingDescriptor binding{};
        binding.binding_name = binding_name;
        binding.profile = profile;
        return binding;
    }
};

} // namespace assembler::log_level_api::content_parser::c_style_struct_primitive_level_parsers
