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

#include "assembler/log_level_api/content/json_schemas/TLogApiDefaultJsonSchemaFactory.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserCapabilityKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserInputKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserStatus.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

#include "TLogApiJsonLevelParserProfile.hpp"

namespace assembler::log_level_api::content_parser::json_level_parsers {

class TLogApiJsonLevelParserProfileFactory final {
public:
    [[nodiscard]] static assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor MakeBinding(
        const char* binding_name,
        const char* parser_name,
        const char* supported_schema_name,
        const char* content_profile_name
    ) {
        using namespace assembler::log_level_api::content_parser;

        TLogApiContentParserProfile profile{};
        profile.id = TLogApiContentParserId{100};
        profile.status = TLogApiContentParserStatus::Resolved;
        profile.parser_kind = TLogApiContentParserKind::JsonLevelSpecific;
        profile.input_kind = TLogApiContentParserInputKind::JsonText;
        profile.output_kind = TLogApiParsedContentKind::JsonFieldView;
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

} // namespace assembler::log_level_api::content_parser::json_level_parsers
