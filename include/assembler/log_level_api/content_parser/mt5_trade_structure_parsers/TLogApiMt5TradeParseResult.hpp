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

#include "assembler/log_level_api/content_parser/TLogApiContentParseResult.hpp"

#include "TLogApiMt5TradeParseIssue.hpp"
#include "TLogApiMt5TradeParsedContent.hpp"

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers {

struct TLogApiMt5TradeParseResult final {
    assembler::log_level_api::content_parser::TLogApiContentParseResult core_result{};
    TLogApiMt5TradeParsedContent parsed_trade{};
    std::vector<TLogApiMt5TradeParseIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (core_result.HasBlockingIssue()) return true;
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return core_result.IsAccepted()
            && parsed_trade.IsPresent()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
