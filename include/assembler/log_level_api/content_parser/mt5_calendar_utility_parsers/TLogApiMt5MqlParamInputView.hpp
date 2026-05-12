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

namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers {

struct TLogApiMt5MqlParamInputView final {
    std::int32_t type{0};
    std::int64_t integer_value{0};
    double double_value{0.0};
    std::string string_value{};
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept { return present; }
};

} // namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers
