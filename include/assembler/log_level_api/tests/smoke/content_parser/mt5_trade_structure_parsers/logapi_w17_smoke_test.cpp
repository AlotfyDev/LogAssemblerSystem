#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5ExtendedSchemaSurface.hpp"
#include "assembler/log_level_api/content_parser/mt5_trade_structure_parsers/TLogApiMt5TradeParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers;

    auto pack = TLogApiMt5SchemaFactory::MakeDefaultPack();

    auto req_binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_request.parser.binding",
        "mt5.trade_request.parser",
        "mt5.mql_trade_request",
        "mt5.trade"
    );
    TLogApiMt5TradeParserProfile req_profile{};
    req_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeRequest;
    req_profile.parser_name = "mt5.trade_request.parser";
    req_profile.schema = pack.Find(TLogApiMt5StructureKind::MqlTradeRequest);
    req_profile.binding = &req_binding;
    assert(req_profile.IsReady());

    TLogApiMt5MqlTradeRequestInputView req{};
    req.present = true;
    req.action = 1;
    req.magic = 42;
    req.order = 1001;
    req.symbol = "EURUSD";
    req.volume = 1.5;
    req.price = 1.2345;
    req.stoplimit = 0.0;
    req.sl = 1.2;
    req.tp = 1.3;
    req.deviation = 10;
    req.type = 2;
    req.type_filling = 1;
    req.type_time = 0;
    req.expiration = 1700000000;
    req.comment = "unit-test";
    req.position = 77;
    req.position_by = 0;

    auto req_result = TMqlTradeRequestContentParser::Parse(req, req_profile);
    assert(req_result.IsAccepted());
    assert(req_result.parsed_trade.Find("action") != nullptr);
    assert(req_result.parsed_trade.Find("symbol") != nullptr);
    assert(req_result.parsed_trade.Find("position_by") != nullptr);

    auto check_binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_check_result.parser.binding",
        "mt5.trade_check_result.parser",
        "mt5.mql_trade_check_result",
        "mt5.trade"
    );
    TLogApiMt5TradeParserProfile check_profile{};
    check_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeCheckResult;
    check_profile.parser_name = "mt5.trade_check_result.parser";
    check_profile.schema = pack.Find(TLogApiMt5StructureKind::MqlTradeCheckResult);
    check_profile.binding = &check_binding;
    assert(check_profile.IsReady());

    TLogApiMt5MqlTradeCheckResultInputView check{};
    check.present = true;
    check.retcode = 0;
    check.balance = 1000.0;
    check.equity = 1001.0;
    check.profit = 1.0;
    check.margin = 50.0;
    check.margin_free = 950.0;
    check.margin_level = 200.0;
    check.comment = "ok";

    auto check_result = TMqlTradeCheckResultContentParser::Parse(check, check_profile);
    assert(check_result.IsAccepted());
    assert(check_result.parsed_trade.Find("margin_level") != nullptr);

    auto result_binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_result.parser.binding",
        "mt5.trade_result.parser",
        "mt5.mql_trade_result",
        "mt5.trade"
    );
    TLogApiMt5TradeParserProfile result_profile{};
    result_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeResult;
    result_profile.parser_name = "mt5.trade_result.parser";
    result_profile.schema = pack.Find(TLogApiMt5StructureKind::MqlTradeResult);
    result_profile.binding = &result_binding;
    assert(result_profile.IsReady());

    TLogApiMt5MqlTradeResultInputView trade_result{};
    trade_result.present = true;
    trade_result.retcode = 10009;
    trade_result.deal = 2001;
    trade_result.order = 1001;
    trade_result.volume = 1.5;
    trade_result.price = 1.2346;
    trade_result.bid = 1.2345;
    trade_result.ask = 1.2347;
    trade_result.comment = "done";
    trade_result.request_id = 55;
    trade_result.retcode_external = 0;

    auto parsed_result = TMqlTradeResultContentParser::Parse(trade_result, result_profile);
    assert(parsed_result.IsAccepted());
    assert(parsed_result.parsed_trade.Find("request_id") != nullptr);

    auto tx_binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_transaction.parser.binding",
        "mt5.trade_transaction.parser",
        "mt5.mql_trade_transaction",
        "mt5.trade"
    );
    TLogApiMt5TradeParserProfile tx_profile{};
    tx_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeTransaction;
    tx_profile.parser_name = "mt5.trade_transaction.parser";
    tx_profile.schema = pack.Find(TLogApiMt5StructureKind::MqlTradeTransaction);
    tx_profile.binding = &tx_binding;
    assert(tx_profile.IsReady());

    TLogApiMt5MqlTradeTransactionInputView tx{};
    tx.present = true;
    tx.deal = 2001;
    tx.order = 1001;
    tx.symbol = "EURUSD";
    tx.type = 1;
    tx.order_type = 2;
    tx.order_state = 3;
    tx.deal_type = 4;
    tx.time_type = 0;
    tx.time_expiration = 1700000001;
    tx.price = 1.2346;
    tx.price_trigger = 0.0;
    tx.price_sl = 1.2;
    tx.price_tp = 1.3;
    tx.volume = 1.5;
    tx.position = 77;
    tx.position_by = 0;

    auto tx_result = TMqlTradeTransactionContentParser::Parse(tx, tx_profile);
    assert(tx_result.IsAccepted());
    assert(tx_result.parsed_trade.Find("deal_type") != nullptr);
    assert(tx_result.parsed_trade.Find("position_by") != nullptr);

    auto view = TLogApiMt5TradeParserView::From(req_profile);
    assert(view.ready);
    assert(view.schema_name == "mt5.mql_trade_request");

    std::cout << "LOGAPI-W17 smoke test passed\\n";
    return 0;
}
