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

#include "TLogApiMt5FieldId.hpp"
#include "TLogApiMt5FieldPresenceKind.hpp"
#include "TLogApiMt5FieldPrimitiveKind.hpp"

namespace assembler::log_level_api::content::mt5_extended_schemas {

struct TLogApiMt5FieldDescriptor final {
    TLogApiMt5FieldId id{};
    std::string field_name{};
    std::string mql5_type_name{};
    TLogApiMt5FieldPrimitiveKind primitive_kind{TLogApiMt5FieldPrimitiveKind::Unknown};
    TLogApiMt5FieldPresenceKind presence{TLogApiMt5FieldPresenceKind::Unknown};
    std::string note{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return id.IsValid()
            && !field_name.empty()
            && !mql5_type_name.empty()
            && primitive_kind != TLogApiMt5FieldPrimitiveKind::Unknown
            && presence != TLogApiMt5FieldPresenceKind::Unknown;
    }
};

} // namespace assembler::log_level_api::content::mt5_extended_schemas
