#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5ExtendedSchemaSurface.hpp"
#include "assembler/log_level_api/content_parser/mt5_market_data_parsers/TLogApiMt5MarketDataParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_market_data_parsers;

    auto pack = TLogApiMt5SchemaFactory::MakeDefaultPack();

    auto tick_binding = TLogApiMt5MarketDataParserProfileFactory::MakeBinding(
        "mt5.tick.parser.binding",
        "mt5.tick.parser",
        "mt5.mql_tick",
        "mt5.market_data"
    );
    TLogApiMt5MarketDataParserProfile tick_profile{};
    tick_profile.parser_kind = TLogApiMt5MarketDataParserKind::MqlTick;
    tick_profile.parser_name = "mt5.tick.parser";
    tick_profile.schema = pack.Find(TLogApiMt5StructureKind::MqlTick);
    tick_profile.binding = &tick_binding;
    assert(tick_profile.IsReady());

    TLogApiMt5MqlTickInputView tick{};
    tick.present = true;
    tick.time = 1700000000;
    tick.bid = 1.2345;
    tick.ask = 1.2347;
    tick.last = 1.2346;
    tick.volume = 100;
    tick.time_msc = 1700000000123;
    tick.flags = 3;
    tick.volume_real = 100.5;

    auto tick_result = TMqlTickContentParser::Parse(tick, tick_profile);
    assert(tick_result.IsAccepted());
    assert(tick_result.parsed_market_data.Find("bid") != nullptr);
    assert(tick_result.parsed_market_data.Find("ask") != nullptr);
    assert(tick_result.parsed_market_data.Find("volume_real") != nullptr);

    auto rates_binding = TLogApiMt5MarketDataParserProfileFactory::MakeBinding(
        "mt5.rates.parser.binding",
        "mt5.rates.parser",
        "mt5.mql_rates",
        "mt5.market_data"
    );
    TLogApiMt5MarketDataParserProfile rates_profile{};
    rates_profile.parser_kind = TLogApiMt5MarketDataParserKind::MqlRates;
    rates_profile.parser_name = "mt5.rates.parser";
    rates_profile.schema = pack.Find(TLogApiMt5StructureKind::MqlRates);
    rates_profile.binding = &rates_binding;
    assert(rates_profile.IsReady());

    TLogApiMt5MqlRatesInputView rates{};
    rates.present = true;
    rates.time = 1700000100;
    rates.open = 1.0;
    rates.high = 2.0;
    rates.low = 0.5;
    rates.close = 1.5;
    rates.tick_volume = 200;
    rates.spread = 10;
    rates.real_volume = 300;

    auto rates_result = TMqlRatesContentParser::Parse(rates, rates_profile);
    assert(rates_result.IsAccepted());
    assert(rates_result.parsed_market_data.Find("open") != nullptr);
    assert(rates_result.parsed_market_data.Find("real_volume") != nullptr);

    auto book_binding = TLogApiMt5MarketDataParserProfileFactory::MakeBinding(
        "mt5.book.parser.binding",
        "mt5.book.parser",
        "mt5.mql_book_info",
        "mt5.market_data"
    );
    TLogApiMt5MarketDataParserProfile book_profile{};
    book_profile.parser_kind = TLogApiMt5MarketDataParserKind::MqlBookInfo;
    book_profile.parser_name = "mt5.book.parser";
    book_profile.schema = pack.Find(TLogApiMt5StructureKind::MqlBookInfo);
    book_profile.binding = &book_binding;
    assert(book_profile.IsReady());

    TLogApiMt5MqlBookInfoInputView book{};
    book.present = true;
    book.type = 1;
    book.price = 1.25;
    book.volume = 10;
    book.volume_real = 10.25;

    auto book_result = TMqlBookInfoContentParser::Parse(book, book_profile);
    assert(book_result.IsAccepted());
    assert(book_result.parsed_market_data.Find("price") != nullptr);
    assert(book_result.parsed_market_data.Find("volume_real") != nullptr);

    auto view = TLogApiMt5MarketDataParserView::From(tick_profile);
    assert(view.ready);
    assert(view.schema_name == "mt5.mql_tick");

    std::cout << "LOGAPI-W16 smoke test passed\\n";
    return 0;
}
