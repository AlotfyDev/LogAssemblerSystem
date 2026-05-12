#pragma once

/*
    LOGAPI-W20 — Metadata Default Field Packs

    Responsibility:
        Define default metadata field packs and helpers for composing reusable
        metadata field/value groups into metadata profile configurations.

    Boundary:
        Metadata field packs are configuration conveniences, not policy objects.
        This wave does not implement content schemas, parsers, validators,
        timestamp stabilization, envelope assembly, circulation handoff,
        persistence, or policy assignment.

    Doctrine:
        Metadata is independent from content and timestamp.
        Default field packs reduce repeated per-call payload authoring.
        Metadata values remain mutable through profile/update surfaces.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::metadata_injector::default_field_packs {

struct TLogApiMetadataFieldPackId final {
    std::uint64_t value{0};

    constexpr TLogApiMetadataFieldPackId() = default;
    constexpr explicit TLogApiMetadataFieldPackId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-metadata-field-pack-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs
