#include <cassert>
#include <iostream>
#include <vector>

#include "assembler/log_level_api/content_container/TLogApiContentContainerCoreSurface.hpp"
#include "assembler/log_level_api/content_container/mt5_trade_structure_container_parsers/TLogApiMt5TradeContainerParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content_container;
    using namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers;
    using namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers;

    std::vector<TLogApiMt5MqlTradeRequestInputView> requests(2);
    for (std::size_t i = 0; i < requests.size(); ++i) {
        requests[i].present = true;
        requests[i].action = 1;
        requests[i].magic = 42;
        requests[i].order = 1000 + i;
        requests[i].symbol = "EURUSD";
        requests[i].volume = 1.0;
        requests[i].price = 1.2345;
        requests[i].stoplimit = 0.0;
        requests[i].sl = 1.2;
        requests[i].tp = 1.3;
        requests[i].deviation = 10;
        requests[i].type = 2;
        requests[i].type_filling = 1;
        requests[i].type_time = 0;
        requests[i].expiration = 1700000000;
        requests[i].comment = "batch";
        requests[i].position = 77;
        requests[i].position_by = 0;
    }

    TLogApiContentContainerShape req_shape{};
    req_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    req_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeRequest;
    req_shape.element_count = requests.size();
    req_shape.element_size_bytes = sizeof(TLogApiMt5MqlTradeRequestInputView);
    req_shape.contiguous = true;

    TLogApiContentContainerRef req_container{};
    req_container.id = TLogApiContentContainerId{1};
    req_container.data = requests.data();
    req_container.size_bytes = requests.size() * sizeof(TLogApiMt5MqlTradeRequestInputView);
    req_container.shape = req_shape;

    auto req_profile = TLogApiMt5TradeContainerParserProfileFactory::MakeTradeRequestArrayProfile();
    TLogApiContainerParseRequest req_parse{};
    req_parse.container = req_container;
    req_parse.parser_profile = req_profile.core_profile;
    auto req_result = TMqlTradeRequestArrayContainerParser::Parse(req_parse, req_profile);
    assert(req_result.IsAccepted());
    assert(req_result.parsed_count == 2);

    std::vector<TLogApiMt5MqlTradeCheckResultInputView> checks(1);
    checks[0].present = true;
    checks[0].retcode = 0;
    checks[0].balance = 1000.0;
    checks[0].equity = 1001.0;
    checks[0].profit = 1.0;
    checks[0].margin = 50.0;
    checks[0].margin_free = 950.0;
    checks[0].margin_level = 200.0;
    checks[0].comment = "ok";

    TLogApiContentContainerShape check_shape{};
    check_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    check_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeCheckResult;
    check_shape.element_count = checks.size();
    check_shape.element_size_bytes = sizeof(TLogApiMt5MqlTradeCheckResultInputView);
    check_shape.contiguous = true;

    TLogApiContentContainerRef check_container{};
    check_container.id = TLogApiContentContainerId{2};
    check_container.data = checks.data();
    check_container.size_bytes = checks.size() * sizeof(TLogApiMt5MqlTradeCheckResultInputView);
    check_container.shape = check_shape;

    auto check_profile = TLogApiMt5TradeContainerParserProfileFactory::MakeTradeCheckResultArrayProfile();
    TLogApiContainerParseRequest check_parse{};
    check_parse.container = check_container;
    check_parse.parser_profile = check_profile.core_profile;
    auto check_result = TMqlTradeCheckResultArrayContainerParser::Parse(check_parse, check_profile);
    assert(check_result.IsAccepted());
    assert(check_result.parsed_count == 1);

    std::vector<TLogApiMt5MqlTradeResultInputView> results(3);
    for (std::size_t i = 0; i < results.size(); ++i) {
        results[i].present = true;
        results[i].retcode = 10009;
        results[i].deal = 2000 + i;
        results[i].order = 1000 + i;
        results[i].volume = 1.0;
        results[i].price = 1.2345;
        results[i].bid = 1.2344;
        results[i].ask = 1.2346;
        results[i].comment = "done";
        results[i].request_id = static_cast<std::uint32_t>(i + 1);
        results[i].retcode_external = 0;
    }

    TLogApiContentContainerShape result_shape{};
    result_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    result_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeResult;
    result_shape.element_count = results.size();
    result_shape.element_size_bytes = sizeof(TLogApiMt5MqlTradeResultInputView);
    result_shape.contiguous = true;

    TLogApiContentContainerRef result_container{};
    result_container.id = TLogApiContentContainerId{3};
    result_container.data = results.data();
    result_container.size_bytes = results.size() * sizeof(TLogApiMt5MqlTradeResultInputView);
    result_container.shape = result_shape;

    auto result_profile = TLogApiMt5TradeContainerParserProfileFactory::MakeTradeResultArrayProfile();
    TLogApiContainerParseRequest result_parse{};
    result_parse.container = result_container;
    result_parse.parser_profile = result_profile.core_profile;
    auto parsed_results = TMqlTradeResultArrayContainerParser::Parse(result_parse, result_profile);
    assert(parsed_results.IsAccepted());
    assert(parsed_results.parsed_count == 3);

    std::vector<TLogApiMt5MqlTradeTransactionInputView> txs(1);
    txs[0].present = true;
    txs[0].deal = 2001;
    txs[0].order = 1001;
    txs[0].symbol = "EURUSD";
    txs[0].type = 1;
    txs[0].order_type = 2;
    txs[0].order_state = 3;
    txs[0].deal_type = 4;
    txs[0].time_type = 0;
    txs[0].time_expiration = 1700000000;
    txs[0].price = 1.2345;
    txs[0].price_trigger = 0.0;
    txs[0].price_sl = 1.2;
    txs[0].price_tp = 1.3;
    txs[0].volume = 1.0;
    txs[0].position = 77;
    txs[0].position_by = 0;

    TLogApiContentContainerShape tx_shape{};
    tx_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    tx_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlTradeTransaction;
    tx_shape.element_count = txs.size();
    tx_shape.element_size_bytes = sizeof(TLogApiMt5MqlTradeTransactionInputView);
    tx_shape.contiguous = true;

    TLogApiContentContainerRef tx_container{};
    tx_container.id = TLogApiContentContainerId{4};
    tx_container.data = txs.data();
    tx_container.size_bytes = txs.size() * sizeof(TLogApiMt5MqlTradeTransactionInputView);
    tx_container.shape = tx_shape;

    auto tx_profile = TLogApiMt5TradeContainerParserProfileFactory::MakeTradeTransactionArrayProfile();
    TLogApiContainerParseRequest tx_parse{};
    tx_parse.container = tx_container;
    tx_parse.parser_profile = tx_profile.core_profile;
    auto tx_result = TMqlTradeTransactionArrayContainerParser::Parse(tx_parse, tx_profile);
    assert(tx_result.IsAccepted());
    assert(tx_result.parsed_count == 1);

    auto view = TLogApiMt5TradeContainerParserView::From(result_profile, parsed_results);
    assert(view.accepted);
    assert(view.parsed_count == 3);
    assert(view.element_parser_name == "mt5.trade_result.parser");

    std::cout << "LOGAPI-W33 smoke test passed\\n";
    return 0;
}
