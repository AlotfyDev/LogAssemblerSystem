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

#include "TMqlCalendarCountryArrayContainerParser.hpp"
#include "TMqlCalendarEventArrayContainerParser.hpp"
#include "TMqlCalendarValueArrayContainerParser.hpp"
#include "TMqlDateTimeArrayContainerParser.hpp"
#include "TMqlParamArrayContainerParser.hpp"
#include "TLogApiMt5CalendarUtilityContainerParseIssue.hpp"
#include "TLogApiMt5CalendarUtilityContainerParseResult.hpp"
#include "TLogApiMt5CalendarUtilityContainerParserDetail.hpp"
#include "TLogApiMt5CalendarUtilityContainerParserKind.hpp"
#include "TLogApiMt5CalendarUtilityContainerParserProfile.hpp"
#include "TLogApiMt5CalendarUtilityContainerParserProfileFactory.hpp"
#include "TLogApiMt5CalendarUtilityContainerParserView.hpp"
