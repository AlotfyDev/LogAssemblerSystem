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

#include "TLogApiMt5MarketDataParserProfile.hpp"

namespace assembler::log_level_api::content_parser::mt5_market_data_parsers {

struct TLogApiMt5MarketDataParserView final {
    std::string parser_name{};
    std::string schema_name{};
    bool ready{false};

    [[nodiscard]] static TLogApiMt5MarketDataParserView From(const TLogApiMt5MarketDataParserProfile& profile) {
        TLogApiMt5MarketDataParserView view{};
        view.parser_name = profile.parser_name;
        view.schema_name = profile.schema ? profile.schema->schema_name : "";
        view.ready = profile.IsReady();
        return view;
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers
