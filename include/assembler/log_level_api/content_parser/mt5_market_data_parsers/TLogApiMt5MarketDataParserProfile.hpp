#pragma once

/*
    LOGAPI-W16 — MT5 Market Data Parsers

    Responsibility:
        Define dedicated parser surfaces for MetaTrader 5 market-data structures:
        MqlTick, MqlRates, and MqlBookInfo.

    Boundary:
        This wave does not implement MQL5 runtime binding, binary ABI parsing,
        concrete validators, metadata injection, timestamp stabilization, envelope
        assembly, circulation binding, or policy assignment.

    Hot-path doctrine:
        Each MT5 market data structure has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include <string>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureSchemaDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"

#include "TLogApiMt5MarketDataParserKind.hpp"

namespace assembler::log_level_api::content_parser::mt5_market_data_parsers {

struct TLogApiMt5MarketDataParserProfile final {
    TLogApiMt5MarketDataParserKind parser_kind{TLogApiMt5MarketDataParserKind::Unknown};
    std::string parser_name{};
    const assembler::log_level_api::content::mt5_extended_schemas::TLogApiMt5StructureSchemaDescriptor* schema{nullptr};
    const assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor* binding{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return parser_kind != TLogApiMt5MarketDataParserKind::Unknown
            && !parser_name.empty()
            && schema != nullptr
            && schema->IsDeclared()
            && binding != nullptr
            && binding->IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers
