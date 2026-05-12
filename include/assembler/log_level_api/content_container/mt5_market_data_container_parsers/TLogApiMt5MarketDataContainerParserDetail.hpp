#pragma once

/*
    LOGAPI-W32 — MT5 Market Data Container Parsers

    Responsibility:
        Define dedicated container parsers for MT5 market data arrays:
            - MqlTick[]
            - MqlRates[]
            - MqlBookInfo[]

    Boundary:
        This wave does not implement generic runtime dispatch, validators,
        metadata injection, timestamp stabilization, envelope assembly,
        circulation handoff, policy assignment, or real MT5 runtime binding.

    Doctrine:
        Container parser owns the loop.
        Element parser owns one element.
        Each container parser is bound to exactly one element kind.
*/

#include <cstddef>
#include <vector>

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5SchemaFactory.hpp"
#include "assembler/log_level_api/content_container/TLogApiContainerParseRequest.hpp"
#include "assembler/log_level_api/content_container/TLogApiParsedContentBatchRef.hpp"
#include "assembler/log_level_api/content_parser/mt5_market_data_parsers/TLogApiMt5MarketDataParserSurface.hpp"

#include "TLogApiMt5MarketDataContainerParseResult.hpp"
#include "TLogApiMt5MarketDataContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers::detail {

template <class Element>
[[nodiscard]] inline const Element* ElementAt(const assembler::log_level_api::content_container::TLogApiContentContainerRef& ref, std::uint64_t index) noexcept {
    const auto* base = static_cast<const unsigned char*>(ref.data);
    return reinterpret_cast<const Element*>(base + static_cast<std::size_t>(index * ref.shape.element_size_bytes));
}

[[nodiscard]] inline TLogApiMt5MarketDataContainerParseResult Reject(const char* code, const char* message) {
    TLogApiMt5MarketDataContainerParseResult result{};
    result.issues.push_back({code, message, true});
    return result;
}

[[nodiscard]] inline TLogApiMt5MarketDataContainerParseResult FinishAccepted(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    std::uint64_t parsed_count
) {
    using namespace assembler::log_level_api::content_container;

    TLogApiMt5MarketDataContainerParseResult result{};
    result.attempted_count = request.container.shape.element_count;
    result.parsed_count = parsed_count;
    result.core_result.batch.id = TLogApiParsedContentBatchId{request.container.id.value};
    result.core_result.batch.source_container = request.container;
    result.core_result.batch.parsed_count = parsed_count;
    result.core_result.batch.parsed = true;
    return result;
}

[[nodiscard]] inline TLogApiMt5MarketDataContainerParseResult ParseTickArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5MarketDataContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_market_data_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_TICK_CONTAINER_NOT_READY", "MqlTick container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlTick);
    auto binding = TLogApiMt5MarketDataParserProfileFactory::MakeBinding(
        "mt5.tick.parser.binding",
        "mt5.tick.parser",
        "mt5.mql_tick",
        "mt5.market_data"
    );

    TLogApiMt5MarketDataParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5MarketDataParserKind::MqlTick;
    element_profile.parser_name = "mt5.tick.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlTickInputView>(request.container, i);
        auto result = TMqlTickContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_TICK_ELEMENT_PARSE_FAILED", "A MqlTick element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5MarketDataContainerParseResult ParseRatesArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5MarketDataContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_market_data_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_RATES_CONTAINER_NOT_READY", "MqlRates container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlRates);
    auto binding = TLogApiMt5MarketDataParserProfileFactory::MakeBinding(
        "mt5.rates.parser.binding",
        "mt5.rates.parser",
        "mt5.mql_rates",
        "mt5.market_data"
    );

    TLogApiMt5MarketDataParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5MarketDataParserKind::MqlRates;
    element_profile.parser_name = "mt5.rates.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlRatesInputView>(request.container, i);
        auto result = TMqlRatesContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_RATES_ELEMENT_PARSE_FAILED", "A MqlRates element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5MarketDataContainerParseResult ParseBookInfoArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5MarketDataContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_market_data_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_BOOK_INFO_CONTAINER_NOT_READY", "MqlBookInfo container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlBookInfo);
    auto binding = TLogApiMt5MarketDataParserProfileFactory::MakeBinding(
        "mt5.book.parser.binding",
        "mt5.book.parser",
        "mt5.mql_book_info",
        "mt5.market_data"
    );

    TLogApiMt5MarketDataParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5MarketDataParserKind::MqlBookInfo;
    element_profile.parser_name = "mt5.book.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlBookInfoInputView>(request.container, i);
        auto result = TMqlBookInfoContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_BOOK_INFO_ELEMENT_PARSE_FAILED", "A MqlBookInfo element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

} // namespace assembler::log_level_api::content_container::mt5_market_data_container_parsers::detail
