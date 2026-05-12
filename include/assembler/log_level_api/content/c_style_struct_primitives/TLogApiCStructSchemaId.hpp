#pragma once

/*
    LOGAPI-W11 — Default C-Style Struct Primitive Schemas

    This header belongs to the default C-style struct primitive content schema
    add-on pack.

    Responsibility:
        Define ABI/layout-sensitive primitive struct schema descriptors,
        fixed-width primitive field descriptors, explicit offsets, sizes,
        alignment, padding, endianness, presence/default flags, and level-specific
        primitive struct schema profiles.

    Boundary:
        This wave defines C-style struct primitive schema descriptors only.
        It must not implement binary parsing, concrete validators, metadata structs,
        timestamp stabilization, envelope assembly, API facade hot-path behavior,
        circulation bindings, or policy assignment.

    Doctrine:
        C-style struct schemas must be layout-specified, not compiler-implied.
        Defaults are bundled conveniences, not a closed content universe.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::content::c_style_struct_primitives {

struct TLogApiCStructSchemaId final {
    std::uint64_t value{0};

    constexpr TLogApiCStructSchemaId() = default;
    constexpr explicit TLogApiCStructSchemaId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-cstruct-schema-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
