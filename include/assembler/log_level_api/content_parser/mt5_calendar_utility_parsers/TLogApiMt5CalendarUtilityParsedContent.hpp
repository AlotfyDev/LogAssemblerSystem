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

#include <vector>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureSchemaDescriptor.hpp"

#include "TLogApiMt5CalendarUtilityParserKind.hpp"
#include "TLogApiMt5CalendarUtilityParsedField.hpp"

namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers {

struct TLogApiMt5CalendarUtilityParsedContent final {
    TLogApiMt5CalendarUtilityParserKind parser_kind{TLogApiMt5CalendarUtilityParserKind::Unknown};
    const assembler::log_level_api::content::mt5_extended_schemas::TLogApiMt5StructureSchemaDescriptor* schema{nullptr};
    std::vector<TLogApiMt5CalendarUtilityParsedField> fields{};

    [[nodiscard]] bool IsPresent() const noexcept {
        if (parser_kind == TLogApiMt5CalendarUtilityParserKind::Unknown) return false;
        if (schema == nullptr || !schema->IsDeclared()) return false;
        if (fields.empty()) return false;
        for (const auto& field : fields) {
            if (!field.IsUsable()) return false;
        }
        return true;
    }

    [[nodiscard]] const TLogApiMt5CalendarUtilityParsedField* Find(const char* name) const noexcept {
        for (const auto& field : fields) {
            if (field.field_name == name) return &field;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::content_parser::mt5_calendar_utility_parsers
