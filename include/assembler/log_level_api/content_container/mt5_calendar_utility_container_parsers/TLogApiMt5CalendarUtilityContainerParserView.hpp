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

#include "TLogApiMt5CalendarUtilityContainerParseResult.hpp"
#include "TLogApiMt5CalendarUtilityContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers {

struct TLogApiMt5CalendarUtilityContainerParserView final {
    std::string parser_name{};
    std::string element_parser_name{};
    std::uint64_t parsed_count{0};
    bool ready{false};
    bool accepted{false};

    [[nodiscard]] static TLogApiMt5CalendarUtilityContainerParserView From(
        const TLogApiMt5CalendarUtilityContainerParserProfile& profile,
        const TLogApiMt5CalendarUtilityContainerParseResult& result
    ) {
        TLogApiMt5CalendarUtilityContainerParserView view{};
        view.parser_name = profile.parser_name;
        view.element_parser_name = profile.core_profile.element_parser_name;
        view.parsed_count = result.parsed_count;
        view.ready = profile.IsReady();
        view.accepted = result.IsAccepted();
        return view;
    }
};

} // namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers
