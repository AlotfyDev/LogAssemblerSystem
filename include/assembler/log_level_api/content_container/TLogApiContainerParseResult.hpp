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

#include <vector>

#include "TLogApiContainerParseIssue.hpp"
#include "TLogApiParsedContentBatchRef.hpp"

namespace assembler::log_level_api::content_container {

struct TLogApiContainerParseResult final {
    TLogApiParsedContentBatchRef batch{};
    std::vector<TLogApiContainerParseIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return batch.IsPresent() && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::content_container
