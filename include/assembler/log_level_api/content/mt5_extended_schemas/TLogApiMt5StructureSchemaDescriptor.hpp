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

#include "TLogApiMt5FieldSet.hpp"
#include "TLogApiMt5SchemaId.hpp"
#include "TLogApiMt5StructureKind.hpp"

namespace assembler::log_level_api::content::mt5_extended_schemas {

struct TLogApiMt5StructureSchemaDescriptor final {
    TLogApiMt5SchemaId id{};
    TLogApiMt5StructureKind structure_kind{TLogApiMt5StructureKind::Unknown};
    std::string schema_name{};
    std::string schema_version{"v1"};
    std::string source_family{"MetaTrader5"};
    TLogApiMt5FieldSet fields{};
    bool primary_tick_schema{false};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return id.IsValid()
            && structure_kind != TLogApiMt5StructureKind::Unknown
            && !schema_name.empty()
            && !schema_version.empty()
            && fields.IsDeclared();
    }
};

} // namespace assembler::log_level_api::content::mt5_extended_schemas
