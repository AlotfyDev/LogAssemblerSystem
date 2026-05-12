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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers {

struct TLogApiMt5MqlTradeRequestInputView final {
    std::int32_t action{0};
    std::uint64_t magic{0};
    std::uint64_t order{0};
    std::string symbol{};
    double volume{0.0};
    double price{0.0};
    double stoplimit{0.0};
    double sl{0.0};
    double tp{0.0};
    std::uint64_t deviation{0};
    std::int32_t type{0};
    std::int32_t type_filling{0};
    std::int32_t type_time{0};
    std::int64_t expiration{0};
    std::string comment{};
    std::uint64_t position{0};
    std::uint64_t position_by{0};
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept { return present; }
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
