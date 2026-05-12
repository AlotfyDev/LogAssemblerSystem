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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::content {

struct TLogApiContentProfileId final {
    std::uint64_t value{0};

    constexpr TLogApiContentProfileId() = default;
    constexpr explicit TLogApiContentProfileId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-content-profile-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::content
