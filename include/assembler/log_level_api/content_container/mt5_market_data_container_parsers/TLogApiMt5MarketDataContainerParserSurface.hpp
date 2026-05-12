#pragma once

/*
    LOGAPI-W32 — MT5 Market Data Container Parsers

    Responsibility:
        Define dedicated container parsers for MT5 market data arrays:
            - MqlTick[]
            - MqlRates[]
            - MqlBookInfo[]

    Boundary:
        This wave does not implement generic runtime dispatch, validators,
        metadata injection, timestamp stabilization, envelope assembly,
        circulation handoff, policy assignment, or real MT5 runtime binding.

    Doctrine:
        Container parser owns the loop.
        Element parser owns one element.
        Each container parser is bound to exactly one element kind.
*/

#include "TMqlBookInfoArrayContainerParser.hpp"
#include "TMqlRatesArrayContainerParser.hpp"
#include "TMqlTickArrayContainerParser.hpp"
#include "TLogApiMt5MarketDataContainerParseIssue.hpp"
#include "TLogApiMt5MarketDataContainerParseResult.hpp"
#include "TLogApiMt5MarketDataContainerParserDetail.hpp"
#include "TLogApiMt5MarketDataContainerParserKind.hpp"
#include "TLogApiMt5MarketDataContainerParserProfile.hpp"
#include "TLogApiMt5MarketDataContainerParserProfileFactory.hpp"
#include "TLogApiMt5MarketDataContainerParserView.hpp"
