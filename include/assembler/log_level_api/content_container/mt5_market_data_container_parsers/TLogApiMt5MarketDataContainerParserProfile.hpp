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

#include <string>

#include "assembler/log_level_api/content_container/TLogApiContainerParserProfile.hpp"

#include "TLogApiMt5MarketDataContainerParserKind.hpp"

namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers {

struct TLogApiMt5MarketDataContainerParserProfile final {
    TLogApiMt5MarketDataContainerParserKind parser_kind{TLogApiMt5MarketDataContainerParserKind::Unknown};
    std::string parser_name{};
    assembler::log_level_api::content_container::TLogApiContainerParserProfile core_profile{};

    [[nodiscard]] bool IsReady() const noexcept {
        return parser_kind != TLogApiMt5MarketDataContainerParserKind::Unknown
            && !parser_name.empty()
            && core_profile.IsResolved();
    }
};

} // namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers
