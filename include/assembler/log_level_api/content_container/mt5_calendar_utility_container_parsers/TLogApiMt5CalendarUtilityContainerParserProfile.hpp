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

#include <string>

#include "assembler/log_level_api/content_container/TLogApiContainerParserProfile.hpp"

#include "TLogApiMt5CalendarUtilityContainerParserKind.hpp"

namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers {

struct TLogApiMt5CalendarUtilityContainerParserProfile final {
    TLogApiMt5CalendarUtilityContainerParserKind parser_kind{TLogApiMt5CalendarUtilityContainerParserKind::Unknown};
    std::string parser_name{};
    assembler::log_level_api::content_container::TLogApiContainerParserProfile core_profile{};

    [[nodiscard]] bool IsReady() const noexcept {
        return parser_kind != TLogApiMt5CalendarUtilityContainerParserKind::Unknown
            && !parser_name.empty()
            && core_profile.IsResolved();
    }
};

} // namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers
