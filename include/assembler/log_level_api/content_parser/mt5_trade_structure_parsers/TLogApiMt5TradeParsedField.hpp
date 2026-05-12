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
#include <variant>

#include "TLogApiMt5TradeParsedScalarKind.hpp"

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers {

using TLogApiMt5TradeParsedValue = std::variant<
    std::monostate,
    std::int64_t,
    std::uint64_t,
    double,
    std::string
>;

struct TLogApiMt5TradeParsedField final {
    std::string field_name{};
    TLogApiMt5TradeParsedScalarKind kind{TLogApiMt5TradeParsedScalarKind::Unknown};
    TLogApiMt5TradeParsedValue value{};
    bool present{false};

    [[nodiscard]] bool IsUsable() const noexcept {
        return !field_name.empty()
            && kind != TLogApiMt5TradeParsedScalarKind::Unknown
            && present
            && !std::holds_alternative<std::monostate>(value);
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
