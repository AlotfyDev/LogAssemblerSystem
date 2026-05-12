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
    MqlBookInfo input view.

    Mirrors the documented market book fields without depending on the MQL5 runtime.
*/
struct TLogApiMt5MqlBookInfoInputView final {
    std::int32_t type{0};
    double price{0.0};
    std::int64_t volume{0};
    double volume_real{0.0};

    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept { return present; }
};

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers
