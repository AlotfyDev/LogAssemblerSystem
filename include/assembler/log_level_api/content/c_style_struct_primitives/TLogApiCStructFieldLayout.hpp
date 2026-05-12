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

#include <cstddef>
#include <cstdint>

#include "TLogApiCStructPrimitiveKind.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

/*
    Explicit binary layout for a field.

    Offset and size are schema-defined and must not be inferred from a compiler's
    struct layout.
*/
struct TLogApiCStructFieldLayout final {
    std::uint32_t offset_bytes{0};
    std::uint32_t size_bytes{0};
    std::uint32_t alignment_bytes{1};
    TLogApiCStructPrimitiveKind primitive_kind{TLogApiCStructPrimitiveKind::Unknown};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return size_bytes > 0
            && alignment_bytes > 0
            && primitive_kind != TLogApiCStructPrimitiveKind::Unknown;
    }

    [[nodiscard]] std::uint32_t EndOffset() const noexcept {
        return offset_bytes + size_bytes;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
