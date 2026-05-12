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

#include "TLogApiMt5MarketDataContainerParserDetail.hpp"

namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers {

class TMqlRatesArrayContainerParser final {
public:
    [[nodiscard]] static TLogApiMt5MarketDataContainerParseResult Parse(
        const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
        const TLogApiMt5MarketDataContainerParserProfile& profile
    ) {
        return detail::ParseRatesArray(request, profile);
    }
};

} // namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers
