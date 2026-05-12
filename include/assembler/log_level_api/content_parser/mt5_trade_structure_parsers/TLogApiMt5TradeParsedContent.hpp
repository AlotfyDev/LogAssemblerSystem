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

#include <vector>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureSchemaDescriptor.hpp"

#include "TLogApiMt5TradeParserKind.hpp"
#include "TLogApiMt5TradeParsedField.hpp"

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers {

struct TLogApiMt5TradeParsedContent final {
    TLogApiMt5TradeParserKind parser_kind{TLogApiMt5TradeParserKind::Unknown};
    const assembler::log_level_api::content::mt5_extended_schemas::TLogApiMt5StructureSchemaDescriptor* schema{nullptr};
    std::vector<TLogApiMt5TradeParsedField> fields{};

    [[nodiscard]] bool IsPresent() const noexcept {
        if (parser_kind == TLogApiMt5TradeParserKind::Unknown) return false;
        if (schema == nullptr || !schema->IsDeclared()) return false;
        if (fields.empty()) return false;
        for (const auto& field : fields) {
            if (!field.IsUsable()) return false;
        }
        return true;
    }

    [[nodiscard]] const TLogApiMt5TradeParsedField* Find(const char* name) const noexcept {
        for (const auto& field : fields) {
            if (field.field_name == name) return &field;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
