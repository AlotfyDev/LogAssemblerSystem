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

#include "TLogApiParsedContentBatchRef.hpp"

namespace assembler::log_level_api::content_container {

struct TLogApiParsedContentBatchView final {
    std::string batch_id{};
    std::string source_container_id{};
    std::uint64_t parsed_count{0};
    bool present{false};

    [[nodiscard]] static TLogApiParsedContentBatchView From(const TLogApiParsedContentBatchRef& ref) {
        TLogApiParsedContentBatchView view{};
        view.batch_id = ref.id.ToString();
        view.source_container_id = ref.source_container.id.ToString();
        view.parsed_count = ref.parsed_count;
        view.present = ref.IsPresent();
        return view;
    }
};

} // namespace assembler::log_level_api::content_container
