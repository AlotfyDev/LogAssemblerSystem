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

#include "TLogApiMt5SchemaPack.hpp"

namespace assembler::log_level_api::content::mt5_extended_schemas {

struct TLogApiMt5SchemaPackView final {
    std::string pack_id{};
    std::string pack_name{};
    std::string pack_version{};
    std::size_t schema_count{0};
    bool declared{false};

    [[nodiscard]] static TLogApiMt5SchemaPackView From(const TLogApiMt5SchemaPack& pack) {
        TLogApiMt5SchemaPackView view{};
        view.pack_id = pack.id.ToString();
        view.pack_name = pack.pack_name;
        view.pack_version = pack.pack_version;
        view.schema_count = pack.schemas.size();
        view.declared = pack.IsDeclared();
        return view;
    }
};

} // namespace assembler::log_level_api::content::mt5_extended_schemas
