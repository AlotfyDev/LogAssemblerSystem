#pragma once

/*
    LOGAPI-W31 — Content Container Core And Batch Parse Model

    Responsibility:
        Define content container references, container shape descriptors,
        batch parse requests/results, parsed content batch references/views,
        and container envelope emission strategy descriptors.

    Boundary:
        This wave does not implement MT5-specific container parsers, JSON batch
        parsers, C-style struct batch parsers, validators, metadata injection,
        timestamp stabilization, envelope assembly, circulation handoff, policy
        assignment, or runtime dispatch.

    Doctrine:
        Container parser selection is configuration-time.
        Container parser execution is hot-path.
        A container parser handles one known container type.
        Element parser handles one known element type.
        No runtime parser dispatch inside the batch loop.
*/

namespace assembler::log_level_api::content_container {

enum class TLogApiContentContainerElementKind {
    Unknown = 0,
    OpaquePayload,
    JsonLevelPayload,
    CStyleStructPrimitivePayload,
    Mt5MqlTick,
    Mt5MqlRates,
    Mt5MqlBookInfo,
    Mt5MqlTradeRequest,
    Mt5MqlTradeCheckResult,
    Mt5MqlTradeResult,
    Mt5MqlTradeTransaction,
    Mt5MqlDateTime,
    Mt5MqlParam,
    Mt5MqlCalendarCountry,
    Mt5MqlCalendarEvent,
    Mt5MqlCalendarValue,
    ExternalElement
};

} // namespace assembler::log_level_api::content_container
