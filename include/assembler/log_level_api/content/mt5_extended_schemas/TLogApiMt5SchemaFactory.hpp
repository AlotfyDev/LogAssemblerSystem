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

class TLogApiMt5SchemaFactory final {
private:
    [[nodiscard]] static TLogApiMt5FieldDescriptor F(
        std::uint64_t id,
        const char* name,
        const char* mql_type,
        TLogApiMt5FieldPrimitiveKind primitive,
        TLogApiMt5FieldPresenceKind presence = TLogApiMt5FieldPresenceKind::Required,
        const char* note = ""
    ) {
        TLogApiMt5FieldDescriptor f{};
        f.id = TLogApiMt5FieldId{id};
        f.field_name = name;
        f.mql5_type_name = mql_type;
        f.primitive_kind = primitive;
        f.presence = presence;
        f.note = note;
        return f;
    }

    [[nodiscard]] static TLogApiMt5StructureSchemaDescriptor S(
        std::uint64_t id,
        TLogApiMt5StructureKind kind,
        const char* name,
        std::vector<TLogApiMt5FieldDescriptor> fields,
        bool primary_tick = false
    ) {
        TLogApiMt5StructureSchemaDescriptor s{};
        s.id = TLogApiMt5SchemaId{id};
        s.structure_kind = kind;
        s.schema_name = name;
        s.schema_version = "v1";
        s.fields.fields = std::move(fields);
        s.primary_tick_schema = primary_tick;
        return s;
    }

public:
    [[nodiscard]] static TLogApiMt5SchemaPack MakeDefaultPack() {
        using P = TLogApiMt5FieldPrimitiveKind;
        using Q = TLogApiMt5FieldPresenceKind;

        TLogApiMt5SchemaPack pack{};
        pack.id = TLogApiMt5SchemaPackId{1};
        pack.pack_name = "default.logapi.mt5.extended.schema.pack";
        pack.pack_version = "v1";

        pack.schemas = {
            S(1, TLogApiMt5StructureKind::MqlDateTime, "mt5.mql_datetime", {
                F(1,"year","int",P::Int32), F(2,"mon","int",P::Int32), F(3,"day","int",P::Int32),
                F(4,"hour","int",P::Int32), F(5,"min","int",P::Int32), F(6,"sec","int",P::Int32),
                F(7,"day_of_week","int",P::Int32), F(8,"day_of_year","int",P::Int32)
            }),
            S(2, TLogApiMt5StructureKind::MqlParam, "mt5.mql_param", {
                F(1,"type","ENUM_DATATYPE",P::Enum), F(2,"integer_value","long",P::Int64),
                F(3,"double_value","double",P::Double), F(4,"string_value","string",P::String)
            }),
            S(3, TLogApiMt5StructureKind::MqlRates, "mt5.mql_rates", {
                F(1,"time","datetime",P::DateTime), F(2,"open","double",P::Double),
                F(3,"high","double",P::Double), F(4,"low","double",P::Double),
                F(5,"close","double",P::Double), F(6,"tick_volume","long",P::Int64),
                F(7,"spread","int",P::Int32), F(8,"real_volume","long",P::Int64)
            }),
            S(4, TLogApiMt5StructureKind::MqlBookInfo, "mt5.mql_book_info", {
                F(1,"type","ENUM_BOOK_TYPE",P::Enum), F(2,"price","double",P::Double),
                F(3,"volume","long",P::Int64), F(4,"volume_real","double",P::Double)
            }),
            S(5, TLogApiMt5StructureKind::MqlTradeRequest, "mt5.mql_trade_request", {
                F(1,"action","ENUM_TRADE_REQUEST_ACTIONS",P::Enum), F(2,"magic","ulong",P::UInt64),
                F(3,"order","ulong",P::UInt64), F(4,"symbol","string",P::String),
                F(5,"volume","double",P::Double), F(6,"price","double",P::Double),
                F(7,"stoplimit","double",P::Double), F(8,"sl","double",P::Double),
                F(9,"tp","double",P::Double), F(10,"deviation","ulong",P::UInt64),
                F(11,"type","ENUM_ORDER_TYPE",P::Enum), F(12,"type_filling","ENUM_ORDER_TYPE_FILLING",P::Enum),
                F(13,"type_time","ENUM_ORDER_TYPE_TIME",P::Enum), F(14,"expiration","datetime",P::DateTime),
                F(15,"comment","string",P::String), F(16,"position","ulong",P::UInt64),
                F(17,"position_by","ulong",P::UInt64)
            }),
            S(6, TLogApiMt5StructureKind::MqlTradeCheckResult, "mt5.mql_trade_check_result", {
                F(1,"retcode","uint",P::UInt32), F(2,"balance","double",P::Double),
                F(3,"equity","double",P::Double), F(4,"profit","double",P::Double),
                F(5,"margin","double",P::Double), F(6,"margin_free","double",P::Double),
                F(7,"margin_level","double",P::Double), F(8,"comment","string",P::String)
            }),
            S(7, TLogApiMt5StructureKind::MqlTradeResult, "mt5.mql_trade_result", {
                F(1,"retcode","uint",P::UInt32), F(2,"deal","ulong",P::UInt64),
                F(3,"order","ulong",P::UInt64), F(4,"volume","double",P::Double),
                F(5,"price","double",P::Double), F(6,"bid","double",P::Double),
                F(7,"ask","double",P::Double), F(8,"comment","string",P::String),
                F(9,"request_id","uint",P::UInt32), F(10,"retcode_external","int",P::Int32)
            }),
            S(8, TLogApiMt5StructureKind::MqlTradeTransaction, "mt5.mql_trade_transaction", {
                F(1,"deal","ulong",P::UInt64), F(2,"order","ulong",P::UInt64),
                F(3,"symbol","string",P::String), F(4,"type","ENUM_TRADE_TRANSACTION_TYPE",P::Enum),
                F(5,"order_type","ENUM_ORDER_TYPE",P::Enum), F(6,"order_state","ENUM_ORDER_STATE",P::Enum),
                F(7,"deal_type","ENUM_DEAL_TYPE",P::Enum), F(8,"time_type","ENUM_ORDER_TYPE_TIME",P::Enum),
                F(9,"time_expiration","datetime",P::DateTime), F(10,"price","double",P::Double),
                F(11,"price_trigger","double",P::Double), F(12,"price_sl","double",P::Double),
                F(13,"price_tp","double",P::Double), F(14,"volume","double",P::Double),
                F(15,"position","ulong",P::UInt64), F(16,"position_by","ulong",P::UInt64)
            }),
            S(9, TLogApiMt5StructureKind::MqlTick, "mt5.mql_tick", {
                F(1,"time","datetime",P::DateTime), F(2,"bid","double",P::Double),
                F(3,"ask","double",P::Double), F(4,"last","double",P::Double),
                F(5,"volume","ulong",P::UInt64), F(6,"time_msc","long",P::Int64),
                F(7,"flags","uint",P::UInt32), F(8,"volume_real","double",P::Double)
            }, true),
            S(10, TLogApiMt5StructureKind::MqlCalendarCountry, "mt5.mql_calendar_country", {
                F(1,"id","ulong",P::UInt64), F(2,"name","string",P::String),
                F(3,"code","string",P::String), F(4,"currency","string",P::String),
                F(5,"currency_symbol","string",P::String), F(6,"url_name","string",P::String)
            }),
            S(11, TLogApiMt5StructureKind::MqlCalendarEvent, "mt5.mql_calendar_event", {
                F(1,"id","ulong",P::UInt64), F(2,"type","ENUM_CALENDAR_EVENT_TYPE",P::Enum),
                F(3,"sector","ENUM_CALENDAR_EVENT_SECTOR",P::Enum), F(4,"frequency","ENUM_CALENDAR_EVENT_FREQUENCY",P::Enum),
                F(5,"time_mode","ENUM_CALENDAR_EVENT_TIMEMODE",P::Enum), F(6,"country_id","ulong",P::UInt64),
                F(7,"unit","string",P::String), F(8,"importance","ENUM_CALENDAR_EVENT_IMPORTANCE",P::Enum),
                F(9,"multiplier","ENUM_CALENDAR_EVENT_MULTIPLIER",P::Enum), F(10,"digits","uint",P::UInt32),
                F(11,"source_url","string",P::String), F(12,"event_code","string",P::String),
                F(13,"name","string",P::String)
            }),
            S(12, TLogApiMt5StructureKind::MqlCalendarValue, "mt5.mql_calendar_value", {
                F(1,"id","ulong",P::UInt64), F(2,"event_id","ulong",P::UInt64),
                F(3,"time","datetime",P::DateTime), F(4,"period","datetime",P::DateTime),
                F(5,"revision","int",P::Int32), F(6,"actual_value","long",P::Int64),
                F(7,"prev_value","long",P::Int64), F(8,"revised_prev_value","long",P::Int64),
                F(9,"forecast_value","long",P::Int64), F(10,"impact_type","ENUM_CALENDAR_EVENT_IMPACT",P::Enum)
            })
        };
        return pack;
    }
};

} // namespace assembler::log_level_api::content::mt5_extended_schemas
