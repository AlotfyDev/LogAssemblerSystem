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

namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers {

enum class TLogApiMt5TradeContainerParserKind {
    Unknown = 0,
    MqlTradeRequestArray,
    MqlTradeCheckResultArray,
    MqlTradeResultArray,
    MqlTradeTransactionArray
};

} // namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers
