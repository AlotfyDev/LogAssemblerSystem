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

#include <string>

#include "TLogApiBatchEnvelopeStrategyKind.hpp"

namespace assembler::log_level_api::content_container {

/*
    Describes how a parsed batch may later map to envelopes.

    This is only a descriptor. It does not implement envelope streaming or assembly.
*/
struct TLogApiBatchEnvelopeStrategyDescriptor final {
    TLogApiBatchEnvelopeStrategyKind kind{TLogApiBatchEnvelopeStrategyKind::Unknown};
    std::string strategy_name{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return kind != TLogApiBatchEnvelopeStrategyKind::Unknown
            && !strategy_name.empty();
    }

    [[nodiscard]] static TLogApiBatchEnvelopeStrategyDescriptor BatchAsSingle() {
        return {TLogApiBatchEnvelopeStrategyKind::BatchAsSingleEnvelope, "batch_as_single_envelope"};
    }

    [[nodiscard]] static TLogApiBatchEnvelopeStrategyDescriptor ElementStream() {
        return {TLogApiBatchEnvelopeStrategyKind::ElementAsEnvelopeStream, "element_as_envelope_stream"};
    }
};

} // namespace assembler::log_level_api::content_container
