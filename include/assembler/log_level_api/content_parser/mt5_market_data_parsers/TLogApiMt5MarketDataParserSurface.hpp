#pragma once

/*
    LOGAPI-W16 — MT5 Market Data Parsers

    Responsibility:
        Define dedicated parser surfaces for MetaTrader 5 market-data structures:
        MqlTick, MqlRates, and MqlBookInfo.

    Boundary:
        This wave does not implement MQL5 runtime binding, binary ABI parsing,
        concrete validators, metadata injection, timestamp stabilization, envelope
        assembly, circulation binding, or policy assignment.

    Hot-path doctrine:
        Each MT5 market data structure has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include "TMqlBookInfoContentParser.hpp"
#include "TMqlRatesContentParser.hpp"
#include "TMqlTickContentParser.hpp"
#include "TLogApiMt5MarketDataParsedContent.hpp"
#include "TLogApiMt5MarketDataParseIssue.hpp"
#include "TLogApiMt5MarketDataParseResult.hpp"
#include "TLogApiMt5MarketDataParserDetail.hpp"
#include "TLogApiMt5MarketDataParserKind.hpp"
#include "TLogApiMt5MarketDataParserProfile.hpp"
#include "TLogApiMt5MarketDataParserProfileFactory.hpp"
#include "TLogApiMt5MarketDataParserView.hpp"
#include "TLogApiMt5MqlBookInfoInputView.hpp"
#include "TLogApiMt5MqlRatesInputView.hpp"
#include "TLogApiMt5MqlTickInputView.hpp"
#include "TLogApiMt5ParsedField.hpp"
#include "TLogApiMt5ParsedScalarKind.hpp"
