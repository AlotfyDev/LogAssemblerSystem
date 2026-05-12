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

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers {

enum class TLogApiMt5TradeParserKind {
    Unknown = 0,
    MqlTradeRequest,
    MqlTradeCheckResult,
    MqlTradeResult,
    MqlTradeTransaction
};

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers
