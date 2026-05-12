#pragma once

/*
    LOGAPI-W34 — MT5 Calendar And Utility Container Parsers

    Responsibility:
        Define dedicated container parsers for MT5 utility/calendar arrays:
            - MqlDateTime[]
            - MqlParam[]
            - MqlCalendarCountry[]
            - MqlCalendarEvent[]
            - MqlCalendarValue[]

    Boundary:
        This wave does not implement generic runtime dispatch, validators,
        metadata injection, timestamp stabilization, envelope assembly,
        circulation handoff, policy assignment, or real MT5 runtime binding.

    Doctrine:
        Container parser owns the loop.
        Element parser owns one element.
        Each container parser is bound to exactly one element kind.
*/

#include <cstddef>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5SchemaFactory.hpp"
#include "assembler/log_level_api/content_container/TLogApiContainerParseRequest.hpp"
#include "assembler/log_level_api/content_container/TLogApiParsedContentBatchRef.hpp"
#include "assembler/log_level_api/content_parser/mt5_calendar_utility_parsers/TLogApiMt5CalendarUtilityParserSurface.hpp"

#include "TLogApiMt5CalendarUtilityContainerParseResult.hpp"
#include "TLogApiMt5CalendarUtilityContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers::detail {

template <class Element>
[[nodiscard]] inline const Element* ElementAt(const assembler::log_level_api::content_container::TLogApiContentContainerRef& ref, std::uint64_t index) noexcept {
    const auto* base = static_cast<const unsigned char*>(ref.data);
    return reinterpret_cast<const Element*>(base + static_cast<std::size_t>(index * ref.shape.element_size_bytes));
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityContainerParseResult Reject(const char* code, const char* message) {
    TLogApiMt5CalendarUtilityContainerParseResult result{};
    result.issues.push_back({code, message, true});
    return result;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityContainerParseResult FinishAccepted(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    std::uint64_t parsed_count
) {
    using namespace assembler::log_level_api::content_container;
    TLogApiMt5CalendarUtilityContainerParseResult result{};
    result.attempted_count = request.container.shape.element_count;
    result.parsed_count = parsed_count;
    result.core_result.batch.id = TLogApiParsedContentBatchId{request.container.id.value};
    result.core_result.batch.source_container = request.container;
    result.core_result.batch.parsed_count = parsed_count;
    result.core_result.batch.parsed = true;
    return result;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityContainerParseResult ParseDateTimeArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5CalendarUtilityContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_DATETIME_CONTAINER_NOT_READY", "MqlDateTime container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlDateTime);
    auto binding = TLogApiMt5CalendarUtilityParserProfileFactory::MakeBinding(
        "mt5.datetime.parser.binding", "mt5.datetime.parser", "mt5.mql_datetime", "mt5.calendar_utility");

    TLogApiMt5CalendarUtilityParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlDateTime;
    element_profile.parser_name = "mt5.datetime.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlDateTimeInputView>(request.container, i);
        auto result = TMqlDateTimeContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_DATETIME_ELEMENT_PARSE_FAILED", "A MqlDateTime element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityContainerParseResult ParseParamArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5CalendarUtilityContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_PARAM_CONTAINER_NOT_READY", "MqlParam container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlParam);
    auto binding = TLogApiMt5CalendarUtilityParserProfileFactory::MakeBinding(
        "mt5.param.parser.binding", "mt5.param.parser", "mt5.mql_param", "mt5.calendar_utility");

    TLogApiMt5CalendarUtilityParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlParam;
    element_profile.parser_name = "mt5.param.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlParamInputView>(request.container, i);
        auto result = TMqlParamContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_PARAM_ELEMENT_PARSE_FAILED", "A MqlParam element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityContainerParseResult ParseCalendarCountryArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5CalendarUtilityContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_CALENDAR_COUNTRY_CONTAINER_NOT_READY", "MqlCalendarCountry container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlCalendarCountry);
    auto binding = TLogApiMt5CalendarUtilityParserProfileFactory::MakeBinding(
        "mt5.calendar_country.parser.binding", "mt5.calendar_country.parser", "mt5.mql_calendar_country", "mt5.calendar_utility");

    TLogApiMt5CalendarUtilityParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlCalendarCountry;
    element_profile.parser_name = "mt5.calendar_country.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlCalendarCountryInputView>(request.container, i);
        auto result = TMqlCalendarCountryContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_CALENDAR_COUNTRY_ELEMENT_PARSE_FAILED", "A MqlCalendarCountry element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityContainerParseResult ParseCalendarEventArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5CalendarUtilityContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_CALENDAR_EVENT_CONTAINER_NOT_READY", "MqlCalendarEvent container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlCalendarEvent);
    auto binding = TLogApiMt5CalendarUtilityParserProfileFactory::MakeBinding(
        "mt5.calendar_event.parser.binding", "mt5.calendar_event.parser", "mt5.mql_calendar_event", "mt5.calendar_utility");

    TLogApiMt5CalendarUtilityParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlCalendarEvent;
    element_profile.parser_name = "mt5.calendar_event.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlCalendarEventInputView>(request.container, i);
        auto result = TMqlCalendarEventContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_CALENDAR_EVENT_ELEMENT_PARSE_FAILED", "A MqlCalendarEvent element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityContainerParseResult ParseCalendarValueArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5CalendarUtilityContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_CALENDAR_VALUE_CONTAINER_NOT_READY", "MqlCalendarValue container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlCalendarValue);
    auto binding = TLogApiMt5CalendarUtilityParserProfileFactory::MakeBinding(
        "mt5.calendar_value.parser.binding", "mt5.calendar_value.parser", "mt5.mql_calendar_value", "mt5.calendar_utility");

    TLogApiMt5CalendarUtilityParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlCalendarValue;
    element_profile.parser_name = "mt5.calendar_value.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlCalendarValueInputView>(request.container, i);
        auto result = TMqlCalendarValueContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_CALENDAR_VALUE_ELEMENT_PARSE_FAILED", "A MqlCalendarValue element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

} // namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers::detail
