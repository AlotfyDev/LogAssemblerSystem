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
#include <string>
#include <variant>

#include "TLogApiMt5ParsedScalarKind.hpp"

namespace assembler::log_level_api::content_parser::mt5_market_data_parsers {

using TLogApiMt5ParsedValue = std::variant<
    std::monostate,
    std::int64_t,
    std::uint64_t,
    double
>;

struct TLogApiMt5ParsedField final {
    std::string field_name{};
    TLogApiMt5ParsedScalarKind kind{TLogApiMt5ParsedScalarKind::Unknown};
    TLogApiMt5ParsedValue value{};
    bool present{false};

    [[nodiscard]] bool IsUsable() const noexcept {
        return !field_name.empty()
            && kind != TLogApiMt5ParsedScalarKind::Unknown
            && present
            && !std::holds_alternative<std::monostate>(value);
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers
