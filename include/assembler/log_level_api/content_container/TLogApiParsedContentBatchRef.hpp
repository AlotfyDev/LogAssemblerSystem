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

#include <cstdint>

#include "TLogApiContentContainerRef.hpp"
#include "TLogApiParsedContentBatchId.hpp"

namespace assembler::log_level_api::content_container {

/*
    Parsed content batch reference.

    This references the parsed result of a container parse. It does not own
    individual parsed element records in this core wave.
*/
struct TLogApiParsedContentBatchRef final {
    TLogApiParsedContentBatchId id{};
    TLogApiContentContainerRef source_container{};
    std::uint64_t parsed_count{0};
    bool parsed{false};

    [[nodiscard]] bool IsPresent() const noexcept {
        return id.IsValid()
            && source_container.IsPresent()
            && parsed
            && parsed_count == source_container.shape.element_count;
    }
};

} // namespace assembler::log_level_api::content_container
