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

#include "assembler/log_level_api/content_container/TLogApiContainerParserProfile.hpp"

#include "TLogApiMt5CalendarUtilityContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers {

class TLogApiMt5CalendarUtilityContainerParserProfileFactory final {
public:
    [[nodiscard]] static TLogApiMt5CalendarUtilityContainerParserProfile MakeDateTimeArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5CalendarUtilityContainerParserProfile p{};
        p.parser_kind = TLogApiMt5CalendarUtilityContainerParserKind::MqlDateTimeArray;
        p.parser_name = "mt5.mql_datetime.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{3001};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlDateTime;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.datetime.parser";
        p.core_profile.supported_schema_name = "mt5.mql_datetime";
        return p;
    }

    [[nodiscard]] static TLogApiMt5CalendarUtilityContainerParserProfile MakeParamArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5CalendarUtilityContainerParserProfile p{};
        p.parser_kind = TLogApiMt5CalendarUtilityContainerParserKind::MqlParamArray;
        p.parser_name = "mt5.mql_param.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{3002};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlParam;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.param.parser";
        p.core_profile.supported_schema_name = "mt5.mql_param";
        return p;
    }

    [[nodiscard]] static TLogApiMt5CalendarUtilityContainerParserProfile MakeCalendarCountryArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5CalendarUtilityContainerParserProfile p{};
        p.parser_kind = TLogApiMt5CalendarUtilityContainerParserKind::MqlCalendarCountryArray;
        p.parser_name = "mt5.mql_calendar_country.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{3003};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlCalendarCountry;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.calendar_country.parser";
        p.core_profile.supported_schema_name = "mt5.mql_calendar_country";
        return p;
    }

    [[nodiscard]] static TLogApiMt5CalendarUtilityContainerParserProfile MakeCalendarEventArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5CalendarUtilityContainerParserProfile p{};
        p.parser_kind = TLogApiMt5CalendarUtilityContainerParserKind::MqlCalendarEventArray;
        p.parser_name = "mt5.mql_calendar_event.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{3004};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlCalendarEvent;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.calendar_event.parser";
        p.core_profile.supported_schema_name = "mt5.mql_calendar_event";
        return p;
    }

    [[nodiscard]] static TLogApiMt5CalendarUtilityContainerParserProfile MakeCalendarValueArrayProfile() {
        using namespace assembler::log_level_api::content_container;
        TLogApiMt5CalendarUtilityContainerParserProfile p{};
        p.parser_kind = TLogApiMt5CalendarUtilityContainerParserKind::MqlCalendarValueArray;
        p.parser_name = "mt5.mql_calendar_value.array.container.parser";
        p.core_profile.id = TLogApiContainerParserId{3005};
        p.core_profile.status = TLogApiContainerParserStatus::Resolved;
        p.core_profile.container_kind = TLogApiContentContainerKind::Mt5StructureArray;
        p.core_profile.element_kind = TLogApiContentContainerElementKind::Mt5MqlCalendarValue;
        p.core_profile.parser_name = p.parser_name;
        p.core_profile.element_parser_name = "mt5.calendar_value.parser";
        p.core_profile.supported_schema_name = "mt5.mql_calendar_value";
        return p;
    }
};

} // namespace assembler::log_level_api::content_container::mt5_calendar_utility_container_parsers
