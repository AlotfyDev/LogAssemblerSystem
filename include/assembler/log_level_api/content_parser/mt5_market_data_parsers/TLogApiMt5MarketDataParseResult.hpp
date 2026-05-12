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

#include "assembler/log_level_api/content_parser/TLogApiContentParseResult.hpp"

#include "TLogApiMt5MarketDataParsedContent.hpp"
#include "TLogApiMt5MarketDataParseIssue.hpp"

namespace assembler::log_level_api::content_parser::mt5_market_data_parsers {

struct TLogApiMt5MarketDataParseResult final {
    assembler::log_level_api::content_parser::TLogApiContentParseResult core_result{};
    TLogApiMt5MarketDataParsedContent parsed_market_data{};
    std::vector<TLogApiMt5MarketDataParseIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (core_result.HasBlockingIssue()) return true;
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return core_result.IsAccepted()
            && parsed_market_data.IsPresent()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers
