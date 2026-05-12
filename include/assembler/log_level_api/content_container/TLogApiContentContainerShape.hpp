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

#include "TLogApiContentContainerElementKind.hpp"
#include "TLogApiContentContainerKind.hpp"

namespace assembler::log_level_api::content_container {

struct TLogApiContentContainerShape final {
    TLogApiContentContainerKind container_kind{TLogApiContentContainerKind::Unknown};
    TLogApiContentContainerElementKind element_kind{TLogApiContentContainerElementKind::Unknown};

    std::uint64_t element_count{0};
    std::uint64_t element_size_bytes{0};
    bool contiguous{true};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return container_kind != TLogApiContentContainerKind::Unknown
            && element_kind != TLogApiContentContainerElementKind::Unknown
            && element_count > 0;
    }

    [[nodiscard]] bool HasFixedElementSize() const noexcept {
        return element_size_bytes > 0;
    }
};

} // namespace assembler::log_level_api::content_container
