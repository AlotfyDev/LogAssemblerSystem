#pragma once

/*
    LOGAPI-W16 — MT5 Market Data Parsers

    Responsibility:
        Define dedicated parser surfaces for MetaTrader 5 market-data structures:
        MqlTick, MqlRates, and MqlBookInfo.

    Boundary:
        This wave does not implement MQL5 runtime binding, binary ABI parsing,
        concrete validators, metadata injection, timestamp stabilization, envelope
        assembly, circulation binding, or policy assignment.

    Hot-path doctrine:
        Each MT5 market data structure has a dedicated parser type.
        No generic parser dispatcher selects a parser in the hot path.
        Parser selection is configuration-time.
*/

#include <string>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5StructureKind.hpp"
#include "assembler/log_level_api/content_parser/TLogApiParsedContentKind.hpp"

#include "TLogApiMt5MarketDataParseResult.hpp"
#include "TLogApiMt5MarketDataParserProfile.hpp"
#include "TLogApiMt5MqlBookInfoInputView.hpp"
#include "TLogApiMt5MqlRatesInputView.hpp"
#include "TLogApiMt5MqlTickInputView.hpp"

namespace assembler::log_level_api::content_parser::mt5_market_data_parsers::detail {

[[nodiscard]] inline TLogApiMt5ParsedField I64(const char* name, std::int64_t value, TLogApiMt5ParsedScalarKind kind = TLogApiMt5ParsedScalarKind::SignedInteger) {
    TLogApiMt5ParsedField f{};
    f.field_name = name;
    f.kind = kind;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5ParsedField U64(const char* name, std::uint64_t value) {
    TLogApiMt5ParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5ParsedScalarKind::UnsignedInteger;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5ParsedField F64(const char* name, double value) {
    TLogApiMt5ParsedField f{};
    f.field_name = name;
    f.kind = TLogApiMt5ParsedScalarKind::FloatingPoint;
    f.value = value;
    f.present = true;
    return f;
}

[[nodiscard]] inline TLogApiMt5MarketDataParseResult Reject(const char* code, const char* message) {
    TLogApiMt5MarketDataParseResult result{};
    result.issues.push_back({code, message, true});
    return result;
}

[[nodiscard]] inline TLogApiMt5MarketDataParseResult ParseTick(
    const TLogApiMt5MqlTickInputView& input,
    const TLogApiMt5MarketDataParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser;

    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlTick) {
        return Reject("LOGAPI_MT5_TICK_PARSE_NOT_READY", "MqlTick parser requires MqlTick input and MqlTick schema profile.");
    }

    TLogApiMt5MarketDataParseResult result{};
    result.parsed_market_data.parser_kind = TLogApiMt5MarketDataParserKind::MqlTick;
    result.parsed_market_data.schema = profile.schema;
    result.parsed_market_data.fields = {
        I64("time", input.time, TLogApiMt5ParsedScalarKind::DateTime),
        F64("bid", input.bid),
        F64("ask", input.ask),
        F64("last", input.last),
        U64("volume", input.volume),
        I64("time_msc", input.time_msc),
        U64("flags", input.flags),
        F64("volume_real", input.volume_real)
    };
    result.core_result.parsed_content.parsed_kind = TLogApiParsedContentKind::Mt5StructureView;
    result.core_result.parsed_content.source_content = {
        static_cast<const void*>(&input),
        sizeof(input)
    };
    result.core_result.parsed_content.parsed = true;
    return result;
}

[[nodiscard]] inline TLogApiMt5MarketDataParseResult ParseRates(
    const TLogApiMt5MqlRatesInputView& input,
    const TLogApiMt5MarketDataParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser;

    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlRates) {
        return Reject("LOGAPI_MT5_RATES_PARSE_NOT_READY", "MqlRates parser requires MqlRates input and MqlRates schema profile.");
    }

    TLogApiMt5MarketDataParseResult result{};
    result.parsed_market_data.parser_kind = TLogApiMt5MarketDataParserKind::MqlRates;
    result.parsed_market_data.schema = profile.schema;
    result.parsed_market_data.fields = {
        I64("time", input.time, TLogApiMt5ParsedScalarKind::DateTime),
        F64("open", input.open),
        F64("high", input.high),
        F64("low", input.low),
        F64("close", input.close),
        I64("tick_volume", input.tick_volume),
        I64("spread", input.spread),
        I64("real_volume", input.real_volume)
    };
    result.core_result.parsed_content.parsed_kind = TLogApiParsedContentKind::Mt5StructureView;
    result.core_result.parsed_content.source_content = {
        static_cast<const void*>(&input),
        sizeof(input)
    };
    result.core_result.parsed_content.parsed = true;
    return result;
}

[[nodiscard]] inline TLogApiMt5MarketDataParseResult ParseBookInfo(
    const TLogApiMt5MqlBookInfoInputView& input,
    const TLogApiMt5MarketDataParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser;

    if (!input.IsPresent() || !profile.IsReady() || profile.schema->structure_kind != TLogApiMt5StructureKind::MqlBookInfo) {
        return Reject("LOGAPI_MT5_BOOK_PARSE_NOT_READY", "MqlBookInfo parser requires MqlBookInfo input and MqlBookInfo schema profile.");
    }

    TLogApiMt5MarketDataParseResult result{};
    result.parsed_market_data.parser_kind = TLogApiMt5MarketDataParserKind::MqlBookInfo;
    result.parsed_market_data.schema = profile.schema;
    result.parsed_market_data.fields = {
        I64("type", input.type, TLogApiMt5ParsedScalarKind::Enum),
        F64("price", input.price),
        I64("volume", input.volume),
        F64("volume_real", input.volume_real)
    };
    result.core_result.parsed_content.parsed_kind = TLogApiParsedContentKind::Mt5StructureView;
    result.core_result.parsed_content.source_content = {
        static_cast<const void*>(&input),
        sizeof(input)
    };
    result.core_result.parsed_content.parsed = true;
    return result;
}

} // namespace assembler::log_level_api::content_parser::mt5_market_data_parsers::detail
