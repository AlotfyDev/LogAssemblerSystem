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

#include <string>

#include "TLogApiCStructLayoutDescriptor.hpp"
#include "TLogApiCStructLogLevelKind.hpp"
#include "TLogApiCStructSchemaId.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

struct TLogApiCStructLevelSchemaDescriptor final {
    TLogApiCStructSchemaId id{};
    TLogApiCStructLogLevelKind level{TLogApiCStructLogLevelKind::Unknown};

    std::string schema_name{};
    std::string schema_version{"v1"};

    TLogApiCStructLayoutDescriptor layout{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return id.IsValid()
            && level != TLogApiCStructLogLevelKind::Unknown
            && !schema_name.empty()
            && !schema_version.empty()
            && layout.IsDeclared()
            && layout.RequiredCount() > 0;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
