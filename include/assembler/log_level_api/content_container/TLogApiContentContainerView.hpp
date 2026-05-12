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

#include "TLogApiContentContainerRef.hpp"

namespace assembler::log_level_api::content_container {

struct TLogApiContentContainerView final {
    std::string container_id{};
    std::uint64_t element_count{0};
    std::uint64_t element_size_bytes{0};
    bool present{false};
    bool fixed_contiguous_ready{false};

    [[nodiscard]] static TLogApiContentContainerView From(const TLogApiContentContainerRef& ref) {
        TLogApiContentContainerView view{};
        view.container_id = ref.id.ToString();
        view.element_count = ref.shape.element_count;
        view.element_size_bytes = ref.shape.element_size_bytes;
        view.present = ref.IsPresent();
        view.fixed_contiguous_ready = ref.IsFixedContiguousArrayReady();
        return view;
    }
};

} // namespace assembler::log_level_api::content_container
