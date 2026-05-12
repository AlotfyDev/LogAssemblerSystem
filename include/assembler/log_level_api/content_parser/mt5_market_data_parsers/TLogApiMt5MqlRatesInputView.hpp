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

#include <cstdint>

namespace assembler::log_level_api::content_parser::mt5_market_data_parsers {

/*
    MqlRates input view.

    Mirrors the documented MqlRates market-history fields without depending on
    the MQL5 runtime.
*/
struct TLogApiMt5MqlRatesInputView final {
    std::int64_t time{0};
    double open{0.0};
    double high{0.0};
    double low{0.0};
    double close{0.0};
    std::int64_t tick_volume{0};
    std::int32_t spread{0};
    std::int64_t real_volume{0};

    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept { return present; }
};

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers
