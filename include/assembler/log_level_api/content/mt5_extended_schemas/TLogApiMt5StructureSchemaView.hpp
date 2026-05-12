#pragma once

/*
    LOGAPI-W12 — Extended Tick Content Schema

    This header belongs to the MetaTrader 5 extended content schema add-on pack.

    Responsibility:
        Define MT5-oriented content schema descriptors, including MqlTick and the
        predefined MQL5 data structures used for date/time, indicator parameters,
        rates, market book, trade request/check/result/transaction, price tick,
        and economic calendar records.

    Boundary:
        This wave defines schema descriptors only.
        It must not implement MQL5 runtime bindings, binary parsing, concrete
        validators, metadata struct implementation, timestamp stabilization,
        envelope assembly, circulation bindings, or policy assignment.

    Doctrine:
        MT5 schemas are default/add-on schema descriptions, not a closed content
        universe. MqlTick is the fast current-price schema, but the pack covers
        the related predefined MT5 structures needed for broader market/trade
        event logging.
*/

#include <string>

#include "TLogApiMt5StructureSchemaDescriptor.hpp"

namespace assembler::log_level_api::content::mt5_extended_schemas {

struct TLogApiMt5StructureSchemaView final {
    std::string schema_id{};
    std::string schema_name{};
    std::string schema_version{};
    std::size_t field_count{0};
    bool primary_tick_schema{false};
    bool declared{false};

    [[nodiscard]] static TLogApiMt5StructureSchemaView From(const TLogApiMt5StructureSchemaDescriptor& schema) {
        TLogApiMt5StructureSchemaView view{};
        view.schema_id = schema.id.ToString();
        view.schema_name = schema.schema_name;
        view.schema_version = schema.schema_version;
        view.field_count = schema.fields.fields.size();
        view.primary_tick_schema = schema.primary_tick_schema;
        view.declared = schema.IsDeclared();
        return view;
    }
};

} // namespace assembler::log_level_api::content::mt5_extended_schemas
