#pragma once

/*
    LOGAPI-W02 — Content Profile And Schema Paths

    This header belongs to the Log Level API content-profile layer.

    Responsibility:
        Define content profile abstractions and schema path descriptors used by
        the configuration surface before the consuming hot path receives content.

    Boundary:
        This file must not define concrete JSON schemas, concrete C-style struct
        layouts, concrete validators, metadata struct implementation, timestamp
        stabilization algorithms, envelope assembly, circulation handoff, or
        policy assignment.

    Doctrine:
        Content schema paths are open and configurable.
        JSON and C-style struct primitive paths are separated.
        The consuming API receives content only and uses an already resolved
        active profile.
*/

#include <cstddef>
#include <cstdint>

namespace assembler::log_level_api::content {

/*
    Hot-path content reference.

    The consuming API receives content only. This reference intentionally carries
    no schema definition, metadata struct definition, timestamp rule, or validator binding.
*/
struct TLogApiContentInputRef final {
    const void* data{nullptr};
    std::size_t size_bytes{0};

    [[nodiscard]] bool IsPresent() const noexcept {
        return data != nullptr && size_bytes > 0;
    }
};

} // namespace assembler::log_level_api::content
