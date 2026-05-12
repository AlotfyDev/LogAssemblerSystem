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

#include <string>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureSchemaDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"

#include "TLogApiMt5TradeParserKind.hpp"

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers {

struct TLogApiMt5TradeParserProfile final {
    TLogApiMt5TradeParserKind parser_kind{TLogApiMt5TradeParserKind::Unknown};
    std::string parser_name{};
    const assembler::log_level_api::content::mt5_extended_schemas::TLogApiMt5StructureSchemaDescriptor* schema{nullptr};
    const assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor* binding{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return parser_kind != TLogApiMt5TradeParserKind::Unknown
            && !parser_name.empty()
            && schema != nullptr
            && schema->IsDeclared()
            && binding != nullptr
            && binding->IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
