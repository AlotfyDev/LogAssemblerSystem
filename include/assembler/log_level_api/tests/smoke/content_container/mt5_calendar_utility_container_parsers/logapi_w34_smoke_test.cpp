#include <cassert>
#include <iostream>
#include <vector>

#include "assembler/log_level_api/content_container/TLogApiContentContainerCoreSurface.hpp"
#include "assembler/log_level_api/content_container/mt5_calendar_utility_container_parsers/TLogApiMt5CalendarUtilityContainerParserSurface.hpp"

int main() {
    using namespace assembler::log_level_api::content_container;
    using namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers;
    using namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers;

    std::vector<TLogApiMt5MqlDateTimeInputView> dts(2);
    for (std::size_t i = 0; i < dts.size(); ++i) {
        dts[i].present = true;
        dts[i].year = 2026;
        dts[i].mon = 5;
        dts[i].day = 7 + static_cast<int>(i);
        dts[i].hour = 12;
        dts[i].min = 30;
        dts[i].sec = 0;
        dts[i].day_of_week = 4;
        dts[i].day_of_year = 127 + static_cast<int>(i);
    }

    TLogApiContentContainerShape dt_shape{};
    dt_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    dt_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlDateTime;
    dt_shape.element_count = dts.size();
    dt_shape.element_size_bytes = sizeof(TLogApiMt5MqlDateTimeInputView);
    dt_shape.contiguous = true;

    TLogApiContentContainerRef dt_container{TLogApiContentContainerId{1}, dts.data(), dts.size() * sizeof(TLogApiMt5MqlDateTimeInputView), dt_shape};
    auto dt_profile = TLogApiMt5CalendarUtilityContainerParserProfileFactory::MakeDateTimeArrayProfile();
    TLogApiContainerParseRequest dt_req{dt_container, dt_profile.core_profile};
    auto dt_result = TMqlDateTimeArrayContainerParser::Parse(dt_req, dt_profile);
    assert(dt_result.IsAccepted());
    assert(dt_result.parsed_count == 2);

    std::vector<TLogApiMt5MqlParamInputView> params(1);
    params[0].present = true;
    params[0].type = 1;
    params[0].integer_value = 42;
    params[0].double_value = 3.14;
    params[0].string_value = "period";

    TLogApiContentContainerShape param_shape{};
    param_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    param_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlParam;
    param_shape.element_count = params.size();
    param_shape.element_size_bytes = sizeof(TLogApiMt5MqlParamInputView);
    param_shape.contiguous = true;

    TLogApiContentContainerRef param_container{TLogApiContentContainerId{2}, params.data(), params.size() * sizeof(TLogApiMt5MqlParamInputView), param_shape};
    auto param_profile = TLogApiMt5CalendarUtilityContainerParserProfileFactory::MakeParamArrayProfile();
    TLogApiContainerParseRequest param_req{param_container, param_profile.core_profile};
    auto param_result = TMqlParamArrayContainerParser::Parse(param_req, param_profile);
    assert(param_result.IsAccepted());
    assert(param_result.parsed_count == 1);

    std::vector<TLogApiMt5MqlCalendarCountryInputView> countries(1);
    countries[0].present = true;
    countries[0].id = 1;
    countries[0].name = "United States";
    countries[0].code = "US";
    countries[0].currency = "USD";
    countries[0].currency_symbol = "$";
    countries[0].url_name = "united-states";

    TLogApiContentContainerShape country_shape{};
    country_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    country_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlCalendarCountry;
    country_shape.element_count = countries.size();
    country_shape.element_size_bytes = sizeof(TLogApiMt5MqlCalendarCountryInputView);
    country_shape.contiguous = true;

    TLogApiContentContainerRef country_container{TLogApiContentContainerId{3}, countries.data(), countries.size() * sizeof(TLogApiMt5MqlCalendarCountryInputView), country_shape};
    auto country_profile = TLogApiMt5CalendarUtilityContainerParserProfileFactory::MakeCalendarCountryArrayProfile();
    TLogApiContainerParseRequest country_req{country_container, country_profile.core_profile};
    auto country_result = TMqlCalendarCountryArrayContainerParser::Parse(country_req, country_profile);
    assert(country_result.IsAccepted());
    assert(country_result.parsed_count == 1);

    std::vector<TLogApiMt5MqlCalendarEventInputView> events(2);
    for (std::size_t i = 0; i < events.size(); ++i) {
        events[i].present = true;
        events[i].id = 10 + i;
        events[i].type = 1;
        events[i].sector = 2;
        events[i].frequency = 3;
        events[i].time_mode = 1;
        events[i].country_id = 1;
        events[i].unit = "%";
        events[i].importance = 2;
        events[i].multiplier = 0;
        events[i].digits = 2;
        events[i].source_url = "https://example.test";
        events[i].event_code = "CPI";
        events[i].name = "Consumer Price Index";
    }

    TLogApiContentContainerShape event_shape{};
    event_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    event_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlCalendarEvent;
    event_shape.element_count = events.size();
    event_shape.element_size_bytes = sizeof(TLogApiMt5MqlCalendarEventInputView);
    event_shape.contiguous = true;

    TLogApiContentContainerRef event_container{TLogApiContentContainerId{4}, events.data(), events.size() * sizeof(TLogApiMt5MqlCalendarEventInputView), event_shape};
    auto event_profile = TLogApiMt5CalendarUtilityContainerParserProfileFactory::MakeCalendarEventArrayProfile();
    TLogApiContainerParseRequest event_req{event_container, event_profile.core_profile};
    auto event_result = TMqlCalendarEventArrayContainerParser::Parse(event_req, event_profile);
    assert(event_result.IsAccepted());
    assert(event_result.parsed_count == 2);

    std::vector<TLogApiMt5MqlCalendarValueInputView> values(3);
    for (std::size_t i = 0; i < values.size(); ++i) {
        values[i].present = true;
        values[i].id = 100 + i;
        values[i].event_id = 10;
        values[i].time = 1700000000 + static_cast<std::int64_t>(i);
        values[i].period = 1699990000;
        values[i].revision = 1;
        values[i].actual_value = 2500000;
        values[i].prev_value = 2400000;
        values[i].revised_prev_value = 2450000;
        values[i].forecast_value = 2480000;
        values[i].impact_type = 1;
    }

    TLogApiContentContainerShape value_shape{};
    value_shape.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
    value_shape.element_kind = TLogApiContentContainerElementKind::Mt5MqlCalendarValue;
    value_shape.element_count = values.size();
    value_shape.element_size_bytes = sizeof(TLogApiMt5MqlCalendarValueInputView);
    value_shape.contiguous = true;

    TLogApiContentContainerRef value_container{TLogApiContentContainerId{5}, values.data(), values.size() * sizeof(TLogApiMt5MqlCalendarValueInputView), value_shape};
    auto value_profile = TLogApiMt5CalendarUtilityContainerParserProfileFactory::MakeCalendarValueArrayProfile();
    TLogApiContainerParseRequest value_req{value_container, value_profile.core_profile};
    auto value_result = TMqlCalendarValueArrayContainerParser::Parse(value_req, value_profile);
    assert(value_result.IsAccepted());
    assert(value_result.parsed_count == 3);

    auto view = TLogApiMt5CalendarUtilityContainerParserView::From(value_profile, value_result);
    assert(view.accepted);
    assert(view.parsed_count == 3);
    assert(view.element_parser_name == "mt5.calendar_value.parser");

    std::cout << "LOGAPI-W34 smoke test passed\\n";
    return 0;
}
