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

#include "TLogApiMt5MarketDataContainerParseResult.hpp"
#include "TLogApiMt5MarketDataContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers {

struct TLogApiMt5MarketDataContainerParserView final {
    std::string parser_name{};
    std::string element_parser_name{};
    std::uint64_t parsed_count{0};
    bool ready{false};
    bool accepted{false};

    [[nodiscard]] static TLogApiMt5MarketDataContainerParserView From(
        const TLogApiMt5MarketDataContainerParserProfile& profile,
        const TLogApiMt5MarketDataContainerParseResult& result
    ) {
        TLogApiMt5MarketDataContainerParserView view{};
        view.parser_name = profile.parser_name;
        view.element_parser_name = profile.core_profile.element_parser_name;
        view.parsed_count = result.parsed_count;
        view.ready = profile.IsReady();
        view.accepted = result.IsAccepted();
        return view;
    }
};

} // namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers
