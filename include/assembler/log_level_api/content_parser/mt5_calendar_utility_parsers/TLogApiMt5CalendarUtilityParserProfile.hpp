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

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureSchemaDescriptor.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserBindingDescriptor.hpp"

#include "TLogApiMt5CalendarUtilityParserKind.hpp"

namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers {

struct TLogApiMt5CalendarUtilityParserProfile final {
    TLogApiMt5CalendarUtilityParserKind parser_kind{TLogApiMt5CalendarUtilityParserKind::Unknown};
    std::string parser_name{};
    const assembler::log_level_api::content::mt5_extended_schemas::TLogApiMt5StructureSchemaDescriptor* schema{nullptr};
    const assembler::log_level_api::content_parser::TLogApiContentParserBindingDescriptor* binding{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return parser_kind != TLogApiMt5CalendarUtilityParserKind::Unknown
            && !parser_name.empty()
            && schema != nullptr
            && schema->IsDeclared()
            && binding != nullptr
            && binding->IsResolved();
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers
