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
#include <vector>

#include "TLogApiMt5SchemaPackId.hpp"
#include "TLogApiMt5StructureSchemaDescriptor.hpp"

namespace assembler::log_level_api::content::mt5_extended_schemas {

struct TLogApiMt5SchemaPack final {
    TLogApiMt5SchemaPackId id{};
    std::string pack_name{};
    std::string pack_version{"v1"};
    std::vector<TLogApiMt5StructureSchemaDescriptor> schemas{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (!id.IsValid()) return false;
        if (pack_name.empty() || pack_version.empty()) return false;
        if (schemas.size() < 12) return false;
        for (const auto& schema : schemas) {
            if (!schema.IsDeclared()) return false;
        }
        return true;
    }

    [[nodiscard]] const TLogApiMt5StructureSchemaDescriptor* Find(TLogApiMt5StructureKind kind) const noexcept {
        for (const auto& schema : schemas) {
            if (schema.structure_kind == kind) return &schema;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::content::mt5_extended_schemas
