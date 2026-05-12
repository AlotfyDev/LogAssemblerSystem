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

#include "TMqlCalendarCountryContentParser.hpp"
#include "TMqlCalendarEventContentParser.hpp"
#include "TMqlCalendarValueContentParser.hpp"
#include "TMqlDateTimeContentParser.hpp"
#include "TMqlParamContentParser.hpp"
#include "TLogApiMt5CalendarUtilityParsedContent.hpp"
#include "TLogApiMt5CalendarUtilityParsedField.hpp"
#include "TLogApiMt5CalendarUtilityParsedScalarKind.hpp"
#include "TLogApiMt5CalendarUtilityParseIssue.hpp"
#include "TLogApiMt5CalendarUtilityParseResult.hpp"
#include "TLogApiMt5CalendarUtilityParserDetail.hpp"
#include "TLogApiMt5CalendarUtilityParserKind.hpp"
#include "TLogApiMt5CalendarUtilityParserProfile.hpp"
#include "TLogApiMt5CalendarUtilityParserProfileFactory.hpp"
#include "TLogApiMt5CalendarUtilityParserView.hpp"
#include "TLogApiMt5MqlCalendarCountryInputView.hpp"
#include "TLogApiMt5MqlCalendarEventInputView.hpp"
#include "TLogApiMt5MqlCalendarValueInputView.hpp"
#include "TLogApiMt5MqlDateTimeInputView.hpp"
#include "TLogApiMt5MqlParamInputView.hpp"
