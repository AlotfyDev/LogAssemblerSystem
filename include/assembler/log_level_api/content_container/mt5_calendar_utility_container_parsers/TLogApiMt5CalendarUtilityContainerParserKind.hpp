#pragma once

/*
    LOGAPI-W34 — MT5 Calendar And Utility Container Parsers

    Responsibility:
        Define dedicated container parsers for MT5 utility/calendar arrays:
            - MqlDateTime[]
            - MqlParam[]
            - MqlCalendarCountry[]
            - MqlCalendarEvent[]
            - MqlCalendarValue[]

    Boundary:
        This wave does not implement generic runtime dispatch, validators,
        metadata injection, timestamp stabilization, envelope assembly,
        circulation handoff, policy assignment, or real MT5 runtime binding.

    Doctrine:
        Container parser owns the loop.
        Element parser owns one element.
        Each container parser is bound to exactly one element kind.
*/

namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers {

enum class TLogApiMt5CalendarUtilityContainerParserKind {
    Unknown = 0,
    MqlDateTimeArray,
    MqlParamArray,
    MqlCalendarCountryArray,
    MqlCalendarEventArray,
    MqlCalendarValueArray
};

} // namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers
