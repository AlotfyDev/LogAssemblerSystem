#pragma once

/*
    LOGAPI-W10 — Default JSON Content Schemas

    This header belongs to the default JSON content schema add-on pack.

    Responsibility:
        Define default JSON content schema descriptors, JSON field descriptors,
        required field sets, default field values, and level-specific default
        JSON schema profiles.

    Boundary:
        This wave defines JSON schema descriptors only.
        It must not implement concrete JSON parsing, concrete validators, metadata
        structs, timestamp stabilization, envelope assembly, API facade hot-path
        behavior, circulation bindings, or policy assignment.

    Doctrine:
        Default JSON schemas are bundled conveniences, not a closed content universe.
        The consuming API still receives content only.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::content::json_schemas {

struct TLogApiJsonSchemaPackId final {
    std::uint64_t value{0};

    constexpr TLogApiJsonSchemaPackId() = default;
    constexpr explicit TLogApiJsonSchemaPackId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-json-schema-pack-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::content::json_schemas
