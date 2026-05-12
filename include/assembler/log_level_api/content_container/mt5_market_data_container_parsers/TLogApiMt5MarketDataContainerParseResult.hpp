#pragma once

/*
    LOGAPI-W32 — MT5 Market Data Container Parsers

    Responsibility:
        Define dedicated container parsers for MT5 market data arrays:
            - MqlTick[]
            - MqlRates[]
            - MqlBookInfo[]

    Boundary:
        This wave does not implement generic runtime dispatch, validators,
        metadata injection, timestamp stabilization, envelope assembly,
        circulation handoff, policy assignment, or real MT5 runtime binding.

    Doctrine:
        Container parser owns the loop.
        Element parser owns one element.
        Each container parser is bound to exactly one element kind.
*/

#include <vector>

#include "assembler/log_level_api/content_container/TLogApiContainerParseResult.hpp"
#include "TLogApiMt5MarketDataContainerParseIssue.hpp"

namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers {

struct TLogApiMt5MarketDataContainerParseResult final {
    assembler::log_level_api::content_container::TLogApiContainerParseResult core_result{};
    std::uint64_t attempted_count{0};
    std::uint64_t parsed_count{0};
    std::vector<TLogApiMt5MarketDataContainerParseIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        if (core_result.HasBlockingIssue()) return true;
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return core_result.IsAccepted()
            && attempted_count == parsed_count
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers
