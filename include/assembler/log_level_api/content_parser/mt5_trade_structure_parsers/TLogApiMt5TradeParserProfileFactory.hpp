#pragma once

/*
    LOGAPI-W17 — MT5 Trade Structure Parsers

    Responsibility:
        Define dedicated parser surfaces for MetaTrader 5 trade-related structures:
        MqlTradeRequest, MqlTradeCheckResult, MqlTradeResult, and
        MqlTradeTransaction.

    Boundary:
        This wave does not implement MQL5 runtime binding, binary ABI parsing,
        concrete validators, metadata injection, timestamp stabilization,
        envelope assembly, circulation binding, or policy assignment.

    Hot-path doctrine:
        Each MT5 trade structure has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserCapabilityKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserInputKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserStatus.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers {

class TLogApiMt5TradeParserProfileFactory final {
public:
    [[nodiscard]] static assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor MakeBinding(
        const char* binding_name,
        const char* parser_name,
        const char* supported_schema_name,
        const char* content_profile_name
    ) {
        using namespace assembler::log_level_api::content_parser;

        TLogApiContentParserProfile profile{};
        profile.id = TLogApiContentParserId{400};
        profile.status = TLogApiContentParserStatus::Resolved;
        profile.parser_kind = TLogApiContentParserKind::Mt5StructureSpecific;
        profile.input_kind = TLogApiContentParserInputKind::ExternalBuffer;
        profile.output_kind = TLogApiParsedContentKind::Mt5StructureView;
        profile.parser_name = parser_name;
        profile.supported_content_profile_name = content_profile_name;
        profile.supported_schema_name = supported_schema_name;
        profile.capabilities.capabilities = {
            TLogApiContentParserCapabilityKind::ProduceParsedContentRef,
            TLogApiContentParserCapabilityKind::ProduceSchemaSpecificFieldView,
            TLogApiContentParserCapabilityKind::ReportParseIssues
        };

        TLogApiContentParserBindingDescriptor binding{};
        binding.binding_name = binding_name;
        binding.profile = profile;
        return binding;
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
