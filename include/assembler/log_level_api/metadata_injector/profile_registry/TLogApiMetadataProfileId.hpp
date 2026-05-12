#pragma once

/*
    LOGAPI-W19 — Metadata Profile Registry And Update Model

    Responsibility:
        Define production-hardening metadata profile registry, metadata profile
        identity, update model, profile lookup, update admission, and registry
        view/result carriers.

    Boundary:
        Metadata remains configuration/update concern, not policy.
        This wave does not implement content schemas, parsers, validators,
        timestamp stabilization, envelope assembly, circulation handoff, or
        policy assignment.

    Doctrine:
        Metadata is independent from content and timestamp.
        Metadata values may be updated through configured profile/update surfaces.
        Envelope assembly later composes content + metadata + stabilized timestamp.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::metadata_injector::profile_registry {

struct TLogApiMetadataProfileId final {
    std::uint64_t value{0};

    constexpr TLogApiMetadataProfileId() = default;
    constexpr explicit TLogApiMetadataProfileId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-metadata-profile-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
