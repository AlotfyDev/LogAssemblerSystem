#pragma once

/*
    LOGAPI-W33 — MT5 Trade Structure Container Parsers

    Responsibility:
        Define dedicated container parsers for MT5 trade structure arrays:
            - MqlTradeRequest[]
            - MqlTradeCheckResult[]
            - MqlTradeResult[]
            - MqlTradeTransaction[]

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

#include "assembler/log_level_api/content/mt5_extended_schemas/TLogApiMt5SchemaFactory.hpp"
#include "assembler/log_level_api/content_container/TLogApiContainerParseRequest.hpp"
#include "assembler/log_level_api/content_container/TLogApiParsedContentBatchRef.hpp"
#include "assembler/log_level_api/content_parser/mt5_trade_structure_parsers/TLogApiMt5TradeParserSurface.hpp"

#include "TLogApiMt5TradeContainerParseResult.hpp"
#include "TLogApiMt5TradeContainerParserProfile.hpp"

namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers::detail {

template <class Element>
[[nodiscard]] inline const Element* ElementAt(const assembler::log_level_api::content_container::TLogApiContentContainerRef& ref, std::uint64_t index) noexcept {
    const auto* base = static_cast<const unsigned char*>(ref.data);
    return reinterpret_cast<const Element*>(base + static_cast<std::size_t>(index * ref.shape.element_size_bytes));
}

[[nodiscard]] inline TLogApiMt5TradeContainerParseResult Reject(const char* code, const char* message) {
    TLogApiMt5TradeContainerParseResult result{};
    result.issues.push_back({code, message, true});
    return result;
}

[[nodiscard]] inline TLogApiMt5TradeContainerParseResult FinishAccepted(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    std::uint64_t parsed_count
) {
    using namespace assembler::log_level_api::content_container;
    TLogApiMt5TradeContainerParseResult result{};
    result.attempted_count = request.container.shape.element_count;
    result.parsed_count = parsed_count;
    result.core_result.batch.id = TLogApiParsedContentBatchId{request.container.id.value};
    result.core_result.batch.source_container = request.container;
    result.core_result.batch.parsed_count = parsed_count;
    result.core_result.batch.parsed = true;
    return result;
}

[[nodiscard]] inline TLogApiMt5TradeContainerParseResult ParseTradeRequestArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5TradeContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_TRADE_REQUEST_CONTAINER_NOT_READY", "MqlTradeRequest container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlTradeRequest);
    auto binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_request.parser.binding",
        "mt5.trade_request.parser",
        "mt5.mql_trade_request",
        "mt5.trade"
    );

    TLogApiMt5TradeParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeRequest;
    element_profile.parser_name = "mt5.trade_request.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlTradeRequestInputView>(request.container, i);
        auto result = TMqlTradeRequestContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_TRADE_REQUEST_ELEMENT_PARSE_FAILED", "A MqlTradeRequest element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5TradeContainerParseResult ParseTradeCheckResultArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5TradeContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_TRADE_CHECK_RESULT_CONTAINER_NOT_READY", "MqlTradeCheckResult container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlTradeCheckResult);
    auto binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_check_result.parser.binding",
        "mt5.trade_check_result.parser",
        "mt5.mql_trade_check_result",
        "mt5.trade"
    );

    TLogApiMt5TradeParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeCheckResult;
    element_profile.parser_name = "mt5.trade_check_result.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlTradeCheckResultInputView>(request.container, i);
        auto result = TMqlTradeCheckResultContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_TRADE_CHECK_RESULT_ELEMENT_PARSE_FAILED", "A MqlTradeCheckResult element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5TradeContainerParseResult ParseTradeResultArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5TradeContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_TRADE_RESULT_CONTAINER_NOT_READY", "MqlTradeResult container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlTradeResult);
    auto binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_result.parser.binding",
        "mt5.trade_result.parser",
        "mt5.mql_trade_result",
        "mt5.trade"
    );

    TLogApiMt5TradeParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeResult;
    element_profile.parser_name = "mt5.trade_result.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlTradeResultInputView>(request.container, i);
        auto result = TMqlTradeResultContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_TRADE_RESULT_ELEMENT_PARSE_FAILED", "A MqlTradeResult element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

[[nodiscard]] inline TLogApiMt5TradeContainerParseResult ParseTradeTransactionArray(
    const assembler::log_level_api::content_container::TLogApiContainerParseRequest& request,
    const TLogApiMt5TradeContainerParserProfile& profile
) {
    using namespace assembler::log_level_api::content::mt5_extended_schemas;
    using namespace assembler::log_level_api::content_parser::mt5_trade_structure_parsers;

    if (!request.IsReady() || !profile.IsReady() || !request.container.IsFixedContiguousArrayReady()) {
        return Reject("LOGAPI_MT5_TRADE_TRANSACTION_CONTAINER_NOT_READY", "MqlTradeTransaction container parser requires ready fixed contiguous container.");
    }

    auto schema_pack = TLogApiMt5SchemaFactory::MakeDefaultPack();
    auto* schema = schema_pack.Find(TLogApiMt5StructureKind::MqlTradeTransaction);
    auto binding = TLogApiMt5TradeParserProfileFactory::MakeBinding(
        "mt5.trade_transaction.parser.binding",
        "mt5.trade_transaction.parser",
        "mt5.mql_trade_transaction",
        "mt5.trade"
    );

    TLogApiMt5TradeParserProfile element_profile{};
    element_profile.parser_kind = TLogApiMt5TradeParserKind::MqlTradeTransaction;
    element_profile.parser_name = "mt5.trade_transaction.parser";
    element_profile.schema = schema;
    element_profile.binding = &binding;

    std::uint64_t parsed = 0;
    for (std::uint64_t i = 0; i < request.container.shape.element_count; ++i) {
        const auto* element = ElementAt<TLogApiMt5MqlTradeTransactionInputView>(request.container, i);
        auto result = TMqlTradeTransactionContentParser::Parse(*element, element_profile);
        if (!result.IsAccepted()) return Reject("LOGAPI_MT5_TRADE_TRANSACTION_ELEMENT_PARSE_FAILED", "A MqlTradeTransaction element failed parsing.");
        ++parsed;
    }

    return FinishAccepted(request, parsed);
}

} // namespace assembler::log_level_api::content_container::mt5_trade_structure_container_parsers::detail
