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

#include <vector>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureSchemaDescriptor.hpp"

#include "TLogApiMt5MarketDataParserKind.hpp"
#include "TLogApiMt5ParsedField.hpp"

namespace assembler::log_level_api::content_parser::mt5_market_data_parsers {

struct TLogApiMt5MarketDataParsedContent final {
    TLogApiMt5MarketDataParserKind parser_kind{TLogApiMt5MarketDataParserKind::Unknown};
    const assembler::log_level_api::content::mt5_extended_schemas::TLogApiMt5StructureSchemaDescriptor* schema{nullptr};
    std::vector<TLogApiMt5ParsedField> fields{};

    [[nodiscard]] bool IsPresent() const noexcept {
        if (parser_kind == TLogApiMt5MarketDataParserKind::Unknown) return false;
        if (schema == nullptr || !schema->IsDeclared()) return false;
        if (fields.empty()) return false;
        for (const auto& field : fields) {
            if (!field.IsUsable()) return false;
        }
        return true;
    }

    [[nodiscard]] const TLogApiMt5ParsedField* Find(const char* name) const noexcept {
        for (const auto& field : fields) {
            if (field.field_name == name) return &field;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers
