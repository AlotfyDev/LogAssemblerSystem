#pragma once

/*
    LOGAPI-W33 — MT5 Trade Structure Container Parsers

    Responsibility:
        Define dedicated container parsers for MT5 trade structure arrays:
            - MqlTradeRequest[]
            - MqlTradeCheckResult[]
            - MqlTradeResult[]
            - MqlTradeTransaction[]

    Boundary:
        This wave does not implement generic runtime dispatch, validators,
        metadata injection, timestamp stabilization, envelope assembly,
        circulation handoff, policy assignment, or real MT5 runtime binding.

    Doctrine:
        Container parser owns the loop.
        Element parser owns one element.
        Each container parser is bound to exactly one element kind.
*/

#include "TMqlTradeCheckResultArrayContainerParser.hpp"
#include "TMqlTradeRequestArrayContainerParser.hpp"
#include "TMqlTradeResultArrayContainerParser.hpp"
#include "TMqlTradeTransactionArrayContainerParser.hpp"
#include "TLogApiMt5TradeContainerParseIssue.hpp"
#include "TLogApiMt5TradeContainerParseResult.hpp"
#include "TLogApiMt5TradeContainerParserDetail.hpp"
#include "TLogApiMt5TradeContainerParserKind.hpp"
#include "TLogApiMt5TradeContainerParserProfile.hpp"
#include "TLogApiMt5TradeContainerParserProfileFactory.hpp"
#include "TLogApiMt5TradeContainerParserView.hpp"
