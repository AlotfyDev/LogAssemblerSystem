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

#include "assembler/log_level_api/content_container/TLogApiContainerParserProfile.hpp"

#include "TLogApiMt5TradeContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers {

class TLogApiMt5TradeContainerParserProfileFactory final {
public:
    [[nodiscard]] static TLogApiMt5TradeContainerParserProfile MakeTradeRequestArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5TradeContainerParserProfile p{};
        p.parser_kind = TLogApiMt5TradeContainerParserKind::MqlTradeRequestArray;
        p.parser_name = "mt5.mql_trade_request.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{2001};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeRequest;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.trade_request.parser";
        p.core_profile.supported_schema_name = "mt5.mql_trade_request";
        return p;
    }

    [[nodiscard]] static TLogApiMt5TradeContainerParserProfile MakeTradeCheckResultArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5TradeContainerParserProfile p{};
        p.parser_kind = TLogApiMt5TradeContainerParserKind::MqlTradeCheckResultArray;
        p.parser_name = "mt5.mql_trade_check_result.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{2002};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeCheckResult;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.trade_check_result.parser";
        p.core_profile.supported_schema_name = "mt5.mql_trade_check_result";
        return p;
    }

    [[nodiscard]] static TLogApiMt5TradeContainerParserProfile MakeTradeResultArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5TradeContainerParserProfile p{};
        p.parser_kind = TLogApiMt5TradeContainerParserKind::MqlTradeResultArray;
        p.parser_name = "mt5.mql_trade_result.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{2003};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeResult;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.trade_result.parser";
        p.core_profile.supported_schema_name = "mt5.mql_trade_result";
        return p;
    }

    [[nodiscard]] static TLogApiMt5TradeContainerParserProfile MakeTradeTransactionArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5TradeContainerParserProfile p{};
        p.parser_kind = TLogApiMt5TradeContainerParserKind::MqlTradeTransactionArray;
        p.parser_name = "mt5.mql_trade_transaction.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{2004};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeTransaction;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.trade_transaction.parser";
        p.core_profile.supported_schema_name = "mt5.mql_trade_transaction";
        return p;
    }
};

} // namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers
