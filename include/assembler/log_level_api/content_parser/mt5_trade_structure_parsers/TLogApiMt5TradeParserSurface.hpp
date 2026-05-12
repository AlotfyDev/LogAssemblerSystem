#pragma once

/*
    LOGAPI-W17 — MT5 Trade Structure Parsers

    Responsibility:
        Define dedicated parser surfaces for MetaTrader 5 trade-related structures:
        MqlTradeRequest, MqlTradeCheckResult, MqlTradeResult, and
        MqlTradeTransaction.

    Boundary:
        This wave does not implement MQL5 runtime binding, binary ABI parsing,
        concrete validators, metadata injection, timestamp stabilization,
        envelope assembly, circulation binding, or policy assignment.

    Hot-path doctrine:
        Each MT5 trade structure has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include "TMqlTradeCheckResultContentParser.hpp"
#include "TMqlTradeRequestContentParser.hpp"
#include "TMqlTradeResultContentParser.hpp"
#include "TMqlTradeTransactionContentParser.hpp"
#include "TLogApiMt5MqlTradeCheckResultInputView.hpp"
#include "TLogApiMt5MqlTradeRequestInputView.hpp"
#include "TLogApiMt5MqlTradeResultInputView.hpp"
#include "TLogApiMt5MqlTradeTransactionInputView.hpp"
#include "TLogApiMt5TradeParseIssue.hpp"
#include "TLogApiMt5TradeParseResult.hpp"
#include "TLogApiMt5TradeParsedContent.hpp"
#include "TLogApiMt5TradeParsedField.hpp"
#include "TLogApiMt5TradeParsedScalarKind.hpp"
#include "TLogApiMt5TradeParserDetail.hpp"
#include "TLogApiMt5TradeParserKind.hpp"
#include "TLogApiMt5TradeParserProfile.hpp"
#include "TLogApiMt5TradeParserProfileFactory.hpp"
#include "TLogApiMt5TradeParserView.hpp"
