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

#include <string>

#include "assembler/log_level_api/content_container/TLogApiContainerParserProfile.hpp"

#include "TLogApiMt5TradeContainerParserKind.hpp"

namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers {

struct TLogApiMt5TradeContainerParserProfile final {
    TLogApiMt5TradeContainerParserKind parser_kind{TLogApiMt5TradeContainerParserKind::Unknown};
    std::string parser_name{};
    assembler::log_level_api::content_container::TLogApiContainerParserProfile core_profile{};

    [[nodiscard]] bool IsReady() const noexcept {
        return parser_kind != TLogApiMt5TradeContainerParserKind::Unknown
            && !parser_name.empty()
            && core_profile.IsResolved();
    }
};

} // namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers
