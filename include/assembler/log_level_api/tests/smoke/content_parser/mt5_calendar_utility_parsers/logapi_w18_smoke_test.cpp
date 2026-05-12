#include <cassert>
#include <iostream>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5ExtendedSchemaSurface.hpp"
#include "assembler/log_level_api/content_parser/mt5_calendar_utility_parsers/TLogApiMt5CalendarUtilityParserSurface.hpp"

using namespace assembler::log_level_api::content::mt5_extended_schemas;
using namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers;

static TLogApiMt5CalendarUtilityParserProfile make_profile(
    const TLogApiMt5SchemaPack& pack,
    TLogApiMt5CalendarUtilityParserKind parser_kind,
    TLogApiMt5StructureKind schema_kind,
    const char* parser_name,
    const char* schema_name,
    const char* binding_name
) {
    auto binding = new assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor(
        TLogApiMt5CalendarUtilityParserProfileFactory::MakeBinding(
            binding_name,
            parser_name,
            schema_name,
            "mt5.calendar_utility"
        )
    );

    TLogApiMt5CalendarUtilityParserProfile profile{};
    profile.parser_kind = parser_kind;
    profile.parser_name = parser_name;
    profile.schema = pack.Find(schema_kind);
    profile.binding = binding;
    return profile;
}

int main() {
    auto pack = TLogApiMt5SchemaFactory::MakeDefaultPack();

    auto datetime_profile = make_profile(pack, TLogApiMt5CalendarUtilityParserKind::MqlDateTime, TLogApiMt5StructureKind::MqlDateTime, "mt5.datetime.parser", "mt5.mql_datetime", "mt5.datetime.binding");
    TLogApiMt5MqlDateTimeInputView dt{};
    dt.present = true;
    dt.year = 2026;
    dt.mon = 5;
    dt.day = 7;
    dt.hour = 12;
    dt.min = 30;
    dt.sec = 15;
    dt.day_of_week = 4;
    dt.day_of_year = 127;
    auto dt_result = TMqlDateTimeContentParser::Parse(dt, datetime_profile);
    assert(dt_result.IsAccepted());
    assert(dt_result.parsed.Find("year") != nullptr);
    assert(dt_result.parsed.Find("day_of_year") != nullptr);

    auto param_profile = make_profile(pack, TLogApiMt5CalendarUtilityParserKind::MqlParam, TLogApiMt5StructureKind::MqlParam, "mt5.param.parser", "mt5.mql_param", "mt5.param.binding");
    TLogApiMt5MqlParamInputView param{};
    param.present = true;
    param.type = 1;
    param.integer_value = 42;
    param.double_value = 3.14;
    param.string_value = "period";
    auto param_result = TMqlParamContentParser::Parse(param, param_profile);
    assert(param_result.IsAccepted());
    assert(param_result.parsed.Find("string_value") != nullptr);

    auto country_profile = make_profile(pack, TLogApiMt5CalendarUtilityParserKind::MqlCalendarCountry, TLogApiMt5StructureKind::MqlCalendarCountry, "mt5.calendar_country.parser", "mt5.mql_calendar_country", "mt5.calendar_country.binding");
    TLogApiMt5MqlCalendarCountryInputView country{};
    country.present = true;
    country.id = 1;
    country.name = "United States";
    country.code = "US";
    country.currency = "USD";
    country.currency_symbol = "$";
    country.url_name = "united-states";
    auto country_result = TMqlCalendarCountryContentParser::Parse(country, country_profile);
    assert(country_result.IsAccepted());
    assert(country_result.parsed.Find("currency") != nullptr);

    auto event_profile = make_profile(pack, TLogApiMt5CalendarUtilityParserKind::MqlCalendarEvent, TLogApiMt5StructureKind::MqlCalendarEvent, "mt5.calendar_event.parser", "mt5.mql_calendar_event", "mt5.calendar_event.binding");
    TLogApiMt5MqlCalendarEventInputView event{};
    event.present = true;
    event.id = 10;
    event.type = 1;
    event.sector = 2;
    event.frequency = 3;
    event.time_mode = 1;
    event.country_id = 1;
    event.unit = "%";
    event.importance = 2;
    event.multiplier = 0;
    event.digits = 2;
    event.source_url = "https://example.test";
    event.event_code = "CPI";
    event.name = "Consumer Price Index";
    auto event_result = TMqlCalendarEventContentParser::Parse(event, event_profile);
    assert(event_result.IsAccepted());
    assert(event_result.parsed.Find("event_code") != nullptr);
    assert(event_result.parsed.Find("importance") != nullptr);

    auto value_profile = make_profile(pack, TLogApiMt5CalendarUtilityParserKind::MqlCalendarValue, TLogApiMt5StructureKind::MqlCalendarValue, "mt5.calendar_value.parser", "mt5.mql_calendar_value", "mt5.calendar_value.binding");
    TLogApiMt5MqlCalendarValueInputView value{};
    value.present = true;
    value.id = 100;
    value.event_id = 10;
    value.time = 1700000000;
    value.period = 1699990000;
    value.revision = 1;
    value.actual_value = 2500000;
    value.prev_value = 2400000;
    value.revised_prev_value = 2450000;
    value.forecast_value = 2480000;
    value.impact_type = 1;
    auto value_result = TMqlCalendarValueContentParser::Parse(value, value_profile);
    assert(value_result.IsAccepted());
    assert(value_result.parsed.Find("actual_value") != nullptr);
    assert(value_result.parsed.Find("impact_type") != nullptr);

    auto view = TLogApiMt5CalendarUtilityParserView::From(value_profile);
    assert(view.ready);
    assert(view.schema_name == "mt5.mql_calendar_value");

    std::cout << "LOGAPI-W18 smoke test passed\\n";
    return 0;
}
