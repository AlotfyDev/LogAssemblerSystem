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

struct TLogApiMt5MqlTradeTransactionInputView final {
    std::uint64_t deal{0};
    std::uint64_t order{0};
    std::string symbol{};
    std::int32_t type{0};
    std::int32_t order_type{0};
    std::int32_t order_state{0};
    std::int32_t deal_type{0};
    std::int32_t time_type{0};
    std::int64_t time_expiration{0};
    double price{0.0};
    double price_trigger{0.0};
    double price_sl{0.0};
    double price_tp{0.0};
    double volume{0.0};
    std::uint64_t position{0};
    std::uint64_t position_by{0};
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept { return present; }
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
