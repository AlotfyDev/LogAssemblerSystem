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

#include "assembler/log_level_api/content_container/TLogApiContainerParserProfile.hpp"

#include "TLogApiMt5MarketDataContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers {

class TLogApiMt5MarketDataContainerParserProfileFactory final {
public:
    [[nodiscard]] static TLogApiMt5MarketDataContainerParserProfile MakeTickArrayProfile() {
        using namespace assembler::log_level_api::content_container;

        TLogApiMt5MarketDataContainerParserProfile p{};
        p.parser_kind = TLogApiMt5MarketDataContainerParserKind::MqlTickArray;
        p.parser_name = "mt5.mql_tick.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{1001};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlTick;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.tick.parser";
        p.core_profile.supported_schema_name = "mt5.mql_tick";
        return p;
    }

    [[nodiscard]] static TLogApiMt5MarketDataContainerParserProfile MakeRatesArrayProfile() {
        using namespace assembler::log_level_api::content_container;

        TLogApiMt5MarketDataContainerParserProfile p{};
        p.parser_kind = TLogApiMt5MarketDataContainerParserKind::MqlRatesArray;
        p.parser_name = "mt5.mql_rates.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{1002};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlRates;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.rates.parser";
        p.core_profile.supported_schema_name = "mt5.mql_rates";
        return p;
    }

    [[nodiscard]] static TLogApiMt5MarketDataContainerParserProfile MakeBookInfoArrayProfile() {
        using namespace assembler::log_level_api::content_container;

        TLogApiMt5MarketDataContainerParserProfile p{};
        p.parser_kind = TLogApiMt5MarketDataContainerParserKind::MqlBookInfoArray;
        p.parser_name = "mt5.mql_book_info.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{1003};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlBookInfo;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.book_info.parser";
        p.core_profile.supported_schema_name = "mt5.mql_book_info";
        return p;
    }
};

} // namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers
