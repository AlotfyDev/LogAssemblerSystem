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

#include <cstddef>

#include "TLogApiContentContainerId.hpp"
#include "TLogApiContentContainerShape.hpp"

namespace assembler::log_level_api::content_container {

/*
    Generic content container reference.

    This reference describes an externally provided batch/container. It does not
    inspect elements and does not select parsers at runtime.
*/
struct TLogApiContentContainerRef final {
    TLogApiContentContainerId id{};
    const void* data{nullptr};
    std::size_t size_bytes{0};
    TLogApiContentContainerShape shape{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return id.IsValid()
            && data != nullptr
            && size_bytes > 0
            && shape.IsDeclared();
    }

    [[nodiscard]] bool IsFixedContiguousArrayReady() const noexcept {
        if (!IsPresent()) return false;
        if (!shape.contiguous || !shape.HasFixedElementSize()) return false;
        return size_bytes >= static_cast<std::size_t>(shape.element_count * shape.element_size_bytes);
    }
};

} // namespace assembler::log_level_api::content_container
