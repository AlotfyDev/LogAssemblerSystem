#pragma once

/*
    LOGAPI-W18 — MT5 Calendar And Utility Parsers

    Responsibility:
        Define dedicated parser surfaces for MetaTrader 5 utility and calendar
        structures:
            - MqlDateTime
            - MqlParam
            - MqlCalendarCountry
            - MqlCalendarEvent
            - MqlCalendarValue

    Boundary:
        This wave does not implement MQL5 runtime binding, binary ABI parsing,
        concrete validators, metadata injection, timestamp stabilization,
        envelope assembly, circulation binding, or policy assignment.

    Hot-path doctrine:
        Each MT5 utility/calendar structure has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include <string>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

#include "TLogApiMt5CalendarUtilityParseResult.hpp"
#include "TLogApiMt5CalendarUtilityParserProfile.hpp"
#include "TLogApiMt5MqlCalendarCountryInputView.hpp"
#include "TLogApiMt5MqlCalendarEventInputView.hpp"
#include "TLogApiMt5MqlCalendarValueInputView.hpp"
#include "TLogApiMt5MqlDateTimeInputView.hpp"
#include "TLogApiMt5MqlParamInputView.hpp"

namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers::detail {

[[nodiscard]] inline TLogApiMt5CalendarUtilityParsedField I64(const char* name, std::int64_t value, TLogApiMt5CalendarUtilityParsedScalarKind kind = TLogApiMt5CalendarUtilityParsedScalarKind::SignedInteger) {
    TLogApiMt5CalendarUtilityParsedField f{};
    f.field_name = name;
    f.kind = kind;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParsedField U64(const char* name, std::uint64_t value) {
    TLogApiMt5CalendarUtilityParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5CalendarUtilityParsedScalarKind::UnsignedInteger;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParsedField F64(const char* name, double value) {
    TLogApiMt5CalendarUtilityParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5CalendarUtilityParsedScalarKind::FloatingPoint;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParsedField S(const char* name, const std::string& value) {
    TLogApiMt5CalendarUtilityParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5CalendarUtilityParsedScalarKind::String;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParseResult Reject(const char* code, const char* message) {
    TLogApiMt5CalendarUtilityParseResult result{};
    result.issues.push_back({code, message, true});
    return result;
}

inline void CompleteCore(TLogApiMt5CalendarUtilityParseResult& result, const void* source, std::size_t size) {
    using namespace assembler::log_level_api::content_parser;
    result.core_result.parsed_content.parsed_kind = TLogApiParsedContentKind::Mt5StructureView;
    result.core_result.parsed_content.source_content = {source, size};
    result.core_result.parsed_content.parsed = true;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParseResult ParseDateTime(
    const TLogApiMt5MqlDateTimeInputView& input,
    const TLogApiMt5CalendarUtilityParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlDateTime) {
        return Reject("LOGAPI_MT5_DATETIME_PARSE_NOT_READY", "MqlDateTime parser requires matching input/schema profile.");
    }

    TLogApiMt5CalendarUtilityParseResult result{};
    result.parsed.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlDateTime;
    result.parsed.schema = profile.schema;
    result.parsed.fields = {
        I64("year", input.year), I64("mon", input.mon), I64("day", input.day),
        I64("hour", input.hour), I64("min", input.min), I64("sec", input.sec),
        I64("day_of_week", input.day_of_week), I64("day_of_year", input.day_of_year)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParseResult ParseParam(
    const TLogApiMt5MqlParamInputView& input,
    const TLogApiMt5CalendarUtilityParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlParam) {
        return Reject("LOGAPI_MT5_PARAM_PARSE_NOT_READY", "MqlParam parser requires matching input/schema profile.");
    }

    TLogApiMt5CalendarUtilityParseResult result{};
    result.parsed.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlParam;
    result.parsed.schema = profile.schema;
    result.parsed.fields = {
        I64("type", input.type, TLogApiMt5CalendarUtilityParsedScalarKind::Enum),
        I64("integer_value", input.integer_value),
        F64("double_value", input.double_value),
        S("string_value", input.string_value)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParseResult ParseCountry(
    const TLogApiMt5MqlCalendarCountryInputView& input,
    const TLogApiMt5CalendarUtilityParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlCalendarCountry) {
        return Reject("LOGAPI_MT5_CALENDAR_COUNTRY_PARSE_NOT_READY", "MqlCalendarCountry parser requires matching input/schema profile.");
    }

    TLogApiMt5CalendarUtilityParseResult result{};
    result.parsed.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlCalendarCountry;
    result.parsed.schema = profile.schema;
    result.parsed.fields = {
        U64("id", input.id), S("name", input.name), S("code", input.code),
        S("currency", input.currency), S("currency_symbol", input.currency_symbol),
        S("url_name", input.url_name)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParseResult ParseEvent(
    const TLogApiMt5MqlCalendarEventInputView& input,
    const TLogApiMt5CalendarUtilityParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlCalendarEvent) {
        return Reject("LOGAPI_MT5_CALENDAR_EVENT_PARSE_NOT_READY", "MqlCalendarEvent parser requires matching input/schema profile.");
    }

    TLogApiMt5CalendarUtilityParseResult result{};
    result.parsed.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlCalendarEvent;
    result.parsed.schema = profile.schema;
    result.parsed.fields = {
        U64("id", input.id),
        I64("type", input.type, TLogApiMt5CalendarUtilityParsedScalarKind::Enum),
        I64("sector", input.sector, TLogApiMt5CalendarUtilityParsedScalarKind::Enum),
        I64("frequency", input.frequency, TLogApiMt5CalendarUtilityParsedScalarKind::Enum),
        I64("time_mode", input.time_mode, TLogApiMt5CalendarUtilityParsedScalarKind::Enum),
        U64("country_id", input.country_id),
        S("unit", input.unit),
        I64("importance", input.importance, TLogApiMt5CalendarUtilityParsedScalarKind::Enum),
        I64("multiplier", input.multiplier, TLogApiMt5CalendarUtilityParsedScalarKind::Enum),
        U64("digits", input.digits),
        S("source_url", input.source_url),
        S("event_code", input.event_code),
        S("name", input.name)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

[[nodiscard]] inline TLogApiMt5CalendarUtilityParseResult ParseValue(
    const TLogApiMt5MqlCalendarValueInputView& input,
    const TLogApiMt5CalendarUtilityParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlCalendarValue) {
        return Reject("LOGAPI_MT5_CALENDAR_VALUE_PARSE_NOT_READY", "MqlCalendarValue parser requires matching input/schema profile.");
    }

    TLogApiMt5CalendarUtilityParseResult result{};
    result.parsed.parser_kind = TLogApiMt5CalendarUtilityParserKind::MqlCalendarValue;
    result.parsed.schema = profile.schema;
    result.parsed.fields = {
        U64("id", input.id),
        U64("event_id", input.event_id),
        I64("time", input.time, TLogApiMt5CalendarUtilityParsedScalarKind::DateTime),
        I64("period", input.period, TLogApiMt5CalendarUtilityParsedScalarKind::DateTime),
        I64("revision", input.revision),
        I64("actual_value", input.actual_value),
        I64("prev_value", input.prev_value),
        I64("revised_prev_value", input.revised_prev_value),
        I64("forecast_value", input.forecast_value),
        I64("impact_type", input.impact_type, TLogApiMt5CalendarUtilityParsedScalarKind::Enum)
    };
    CompleteCore(result, &input, sizeof(input));
    return result;
}

} // namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers::detail
