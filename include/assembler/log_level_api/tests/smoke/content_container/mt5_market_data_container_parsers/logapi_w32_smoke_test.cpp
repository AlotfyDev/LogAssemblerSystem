#include <cassert>
#include <iostream>
#include <vector>

#include "assembler/log_level_api/content_container/TLogApiContentContainerCoreSurface.hpp"
#include "assembler/log_level_api/content_container/mt5_market_data_container_parsers/TLogApiMt5MarketDataContainerParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content_container;
    using namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers;
    using namespace assembler::log_level_api::content_parser::mt5_market_data_parsers;

    std::vector<TLogApiMt5MqlTickInputView> ticks(3);
    for (std::size_t i = 0; i < ticks.size(); ++i) {
        ticks[i].present = true;
        ticks[i].time = 1700000000 + static_cast<std::int64_t>(i);
        ticks[i].bid = 1.0 + static_cast<double>(i);
        ticks[i].ask = 1.1 + static_cast<double>(i);
        ticks[i].last = 1.05 + static_cast<double>(i);
        ticks[i].volume = 100 + i;
        ticks[i].time_msc = 1700000000000 + static_cast<std::int64_t>(i);
        ticks[i].flags = 3;
        ticks[i].volume_real = 100.5 + static_cast<double>(i);
    }

    TLogApiContentContainerShape tick_shape{};
    tick_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    tick_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlTick;
    tick_shape.element_count = ticks.size();
    tick_shape.element_size_bytes = sizeof(TLogApiMt5MqlTickInputView);
    tick_shape.contiguous = true;

    TLogApiContentContainerRef tick_container{};
    tick_container.id = TLogApiContentContainerId{1};
    tick_container.data = ticks.data();
    tick_container.size_bytes = ticks.size() * sizeof(TLogApiMt5MqlTickInputView);
    tick_container.shape = tick_shape;
    assert(tick_container.IsFixedContiguousArrayReady());

    auto tick_profile = TLogApiMt5MarketDataContainerParserProfileFactory::MakeTickArrayProfile();
    assert(tick_profile.IsReady());

    TLogApiContainerParseRequest tick_request{};
    tick_request.container = tick_container;
    tick_request.parser_profile = tick_profile.core_profile;
    assert(tick_request.IsReady());

    auto tick_result = TMqlTickArrayContainerParser::Parse(tick_request, tick_profile);
    assert(tick_result.IsAccepted());
    assert(tick_result.parsed_count == 3);
    assert(tick_result.core_result.batch.IsPresent());

    auto tick_view = TLogApiMt5MarketDataContainerParserView::From(tick_profile, tick_result);
    assert(tick_view.accepted);
    assert(tick_view.parsed_count == 3);
    assert(tick_view.element_parser_name == "mt5.tick.parser");

    std::vector<TLogApiMt5MqlRatesInputView> rates(2);
    for (std::size_t i = 0; i < rates.size(); ++i) {
        rates[i].present = true;
        rates[i].time = 1700000100 + static_cast<std::int64_t>(i);
        rates[i].open = 1.0;
        rates[i].high = 2.0;
        rates[i].low = 0.5;
        rates[i].close = 1.5;
        rates[i].tick_volume = 200;
        rates[i].spread = 10;
        rates[i].real_volume = 300;
    }

    TLogApiContentContainerShape rates_shape{};
    rates_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    rates_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlRates;
    rates_shape.element_count = rates.size();
    rates_shape.element_size_bytes = sizeof(TLogApiMt5MqlRatesInputView);
    rates_shape.contiguous = true;

    TLogApiContentContainerRef rates_container{};
    rates_container.id = TLogApiContentContainerId{2};
    rates_container.data = rates.data();
    rates_container.size_bytes = rates.size() * sizeof(TLogApiMt5MqlRatesInputView);
    rates_container.shape = rates_shape;

    auto rates_profile = TLogApiMt5MarketDataContainerParserProfileFactory::MakeRatesArrayProfile();
    TLogApiContainerParseRequest rates_request{};
    rates_request.container = rates_container;
    rates_request.parser_profile = rates_profile.core_profile;

    auto rates_result = TMqlRatesArrayContainerParser::Parse(rates_request, rates_profile);
    assert(rates_result.IsAccepted());
    assert(rates_result.parsed_count == 2);

    std::vector<TLogApiMt5MqlBookInfoInputView> book(1);
    book[0].present = true;
    book[0].type = 1;
    book[0].price = 1.25;
    book[0].volume = 10;
    book[0].volume_real = 10.25;

    TLogApiContentContainerShape book_shape{};
    book_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    book_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlBookInfo;
    book_shape.element_count = book.size();
    book_shape.element_size_bytes = sizeof(TLogApiMt5MqlBookInfoInputView);
    book_shape.contiguous = true;

    TLogApiContentContainerRef book_container{};
    book_container.id = TLogApiContentContainerId{3};
    book_container.data = book.data();
    book_container.size_bytes = book.size() * sizeof(TLogApiMt5MqlBookInfoInputView);
    book_container.shape = book_shape;

    auto book_profile = TLogApiMt5MarketDataContainerParserProfileFactory::MakeBookInfoArrayProfile();
    TLogApiContainerParseRequest book_request{};
    book_request.container = book_container;
    book_request.parser_profile = book_profile.core_profile;

    auto book_result = TMqlBookInfoArrayContainerParser::Parse(book_request, book_profile);
    assert(book_result.IsAccepted());
    assert(book_result.parsed_count == 1);

    std::cout << "LOGAPI-W32 smoke test passed\\n";
    return 0;
}
