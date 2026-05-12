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

struct TLogApiMt5MqlCalendarEventInputView final {
    std::uint64_t id{0};
    std::int32_t type{0};
    std::int32_t sector{0};
    std::int32_t frequency{0};
    std::int32_t time_mode{0};
    std::uint64_t country_id{0};
    std::string unit{};
    std::int32_t importance{0};
    std::int32_t multiplier{0};
    std::uint32_t digits{0};
    std::string source_url{};
    std::string event_code{};
    std::string name{};
    bool present{false};

    [[nodiscard]] bool IsPresent() const noexcept { return present; }
};

} // namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers
