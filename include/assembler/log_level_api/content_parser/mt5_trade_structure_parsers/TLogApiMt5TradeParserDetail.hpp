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

#include <string>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

#include "TLogApiMt5MqlTradeCheckResultInputView.hpp"
#include "TLogApiMt5MqlTradeRequestInputView.hpp"
#include "TLogApiMt5MqlTradeResultInputView.hpp"
#include "TLogApiMt5MqlTradeTransactionInputView.hpp"
#include "TLogApiMt5TradeParseResult.hpp"
#include "TLogApiMt5TradeParserProfile.hpp"

namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers::detail {

[[nodiscard]] inline TLogApiMt5TradeParsedField I64(const char* name, std::int64_t value, TLogApiMt5TradeParsedScalarKind kind = TLogApiMt5TradeParsedScalarKind::SignedInteger) {
    TLogApiMt5TradeParsedField f{};
    f.field_name = name;
    f.kind = kind;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5TradeParsedField U64(const char* name, std::uint64_t value) {
    TLogApiMt5TradeParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5TradeParsedScalarKind::UnsignedInteger;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5TradeParsedField F64(const char* name, double value) {
    TLogApiMt5TradeParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5TradeParsedScalarKind::FloatingPoint;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5TradeParsedField S(const char* name, const std::string& value) {
    TLogApiMt5TradeParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5TradeParsedScalarKind::String;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5TradeParseResult Reject(const char* code, const char* message) {
    TLogApiMt5TradeParseResult result{};
    result.issues.push_back({code, message, true});
    return result;
}

[[nodiscard]] inline void CompleteCore(TLogApiMt5TradeParseResult& result, const void* source, std::size_t size) {
    using namespace assembler::log_level_api::content_parser;
    result.core_result.parsed_content.parsed_kind = TLogApiParsedContentKind::Mt5StructureView;
    result.core_result.parsed_content.source_content = {source, size};
    result.core_result.parsed_content.parsed = true;
}

[[nodiscard]] inline TLogApiMt5TradeParseResult ParseTradeRequest(
    const TLogApiMt5MqlTradeRequestInputView& input,
    const TLogApiMt5TradeParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlTradeRequest) {
        return Reject("LOGAPI_MT5_TRADE_REQUEST_PARSE_NOT_READY", "MqlTradeRequest parser requires matching input/schema profile.");
    }

    TLogApiMt5TradeParseResult result{};
    result.parsed_trade.parser_kind = TLogApiMt5TradeParserKind::MqlTradeRequest;
    result.parsed_trade.schema = profile.schema;
    result.parsed_trade.fields = {
        I64("action", input.action, TLogApiMt5TradeParsedScalarKind::Enum),
        U64("magic", input.magic),
        U64("order", input.order),
        S("symbol", input.symbol),
        F64("volume", input.volume),
        F64("price", input.price),
        F64("stoplimit", input.stoplimit),
        F64("sl", input.sl),
        F64("tp", input.tp),
        U64("deviation", input.deviation),
        I64("type", input.type, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("type_filling", input.type_filling, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("type_time", input.type_time, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("expiration", input.expiration, TLogApiMt5TradeParsedScalarKind::DateTime),
        S("comment", input.comment),
        U64("position", input.position),
        U64("position_by", input.position_by)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

[[nodiscard]] inline TLogApiMt5TradeParseResult ParseTradeCheckResult(
    const TLogApiMt5MqlTradeCheckResultInputView& input,
    const TLogApiMt5TradeParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlTradeCheckResult) {
        return Reject("LOGAPI_MT5_TRADE_CHECK_PARSE_NOT_READY", "MqlTradeCheckResult parser requires matching input/schema profile.");
    }

    TLogApiMt5TradeParseResult result{};
    result.parsed_trade.parser_kind = TLogApiMt5TradeParserKind::MqlTradeCheckResult;
    result.parsed_trade.schema = profile.schema;
    result.parsed_trade.fields = {
        U64("retcode", input.retcode),
        F64("balance", input.balance),
        F64("equity", input.equity),
        F64("profit", input.profit),
        F64("margin", input.margin),
        F64("margin_free", input.margin_free),
        F64("margin_level", input.margin_level),
        S("comment", input.comment)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

[[nodiscard]] inline TLogApiMt5TradeParseResult ParseTradeResult(
    const TLogApiMt5MqlTradeResultInputView& input,
    const TLogApiMt5TradeParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlTradeResult) {
        return Reject("LOGAPI_MT5_TRADE_RESULT_PARSE_NOT_READY", "MqlTradeResult parser requires matching input/schema profile.");
    }

    TLogApiMt5TradeParseResult result{};
    result.parsed_trade.parser_kind = TLogApiMt5TradeParserKind::MqlTradeResult;
    result.parsed_trade.schema = profile.schema;
    result.parsed_trade.fields = {
        U64("retcode", input.retcode),
        U64("deal", input.deal),
        U64("order", input.order),
        F64("volume", input.volume),
        F64("price", input.price),
        F64("bid", input.bid),
        F64("ask", input.ask),
        S("comment", input.comment),
        U64("request_id", input.request_id),
        I64("retcode_external", input.retcode_external)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

[[nodiscard]] inline TLogApiMt5TradeParseResult ParseTradeTransaction(
    const TLogApiMt5MqlTradeTransactionInputView& input,
    const TLogApiMt5TradeParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlTradeTransaction) {
        return Reject("LOGAPI_MT5_TRADE_TRANSACTION_PARSE_NOT_READY", "MqlTradeTransaction parser requires matching input/schema profile.");
    }

    TLogApiMt5TradeParseResult result{};
    result.parsed_trade.parser_kind = TLogApiMt5TradeParserKind::MqlTradeTransaction;
    result.parsed_trade.schema = profile.schema;
    result.parsed_trade.fields = {
        U64("deal", input.deal),
        U64("order", input.order),
        S("symbol", input.symbol),
        I64("type", input.type, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("order_type", input.order_type, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("order_state", input.order_state, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("deal_type", input.deal_type, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("time_type", input.time_type, TLogApiMt5TradeParsedScalarKind::Enum),
        I64("time_expiration", input.time_expiration, TLogApiMt5TradeParsedScalarKind::DateTime),
        F64("price", input.price),
        F64("price_trigger", input.price_trigger),
        F64("price_sl", input.price_sl),
        F64("price_tp", input.price_tp),
        F64("volume", input.volume),
        U64("position", input.position),
        U64("position_by", input.position_by)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

} // namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers::detail
