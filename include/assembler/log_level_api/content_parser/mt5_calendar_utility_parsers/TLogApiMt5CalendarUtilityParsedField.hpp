#pragma once

/*
    LOGAPI-W18 — MT5 Calendar And Utility Parsers

    Responsibility:
        Define dedicated parser surfaces for MetaTrader 5 utility and calendar
        structures:
            - MqlDateTime
            - MqlParam
            - MqlCalendarCountry
            - MqlCalendarEvent
            - MqlCalendarValue

    Boundary:
        This wave does not implement MQL5 runtime binding, binary ABI parsing,
        concrete validators, metadata injection, timestamp stabilization,
        envelope assembly, circulation binding, or policy assignment.

    Hot-path doctrine:
        Each MT5 utility/calendar structure has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include <cstdint>
#include <string>
#include <variant>

#include "TLogApiMt5CalendarUtilityParsedScalarKind.hpp"

namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers {

using TLogApiMt5CalendarUtilityParsedValue = std::variant<
    std::monostate,
    std::int64_t,
    std::uint64_t,
    double,
    std::string
>;

struct TLogApiMt5CalendarUtilityParsedField final {
    std::string field_name{};
    TLogApiMt5CalendarUtilityParsedScalarKind kind{TLogApiMt5CalendarUtilityParsedScalarKind::Unknown};
    TLogApiMt5CalendarUtilityParsedValue value{};
    bool present{false};

    [[nodiscard]] bool IsUsable() const noexcept {
        return !field_name.empty()
            && kind != TLogApiMt5CalendarUtilityParsedScalarKind::Unknown
            && present
            && !std::holds_alternative<std::monostate>(value);
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers
