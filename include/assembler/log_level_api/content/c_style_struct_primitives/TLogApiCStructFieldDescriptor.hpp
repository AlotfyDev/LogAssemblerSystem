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

#include "TLogApiCStructDefaultValue.hpp"
#include "TLogApiCStructFieldId.hpp"
#include "TLogApiCStructFieldLayout.hpp"
#include "TLogApiCStructFieldPresenceKind.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

struct TLogApiCStructFieldDescriptor final {
    TLogApiCStructFieldId id{};
    std::string field_name{};
    TLogApiCStructFieldPresenceKind presence{TLogApiCStructFieldPresenceKind::Unknown};
    TLogApiCStructFieldLayout layout{};
    TLogApiCStructDefaultValue default_value{};
    bool override_allowed{true};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (!id.IsValid()) return false;
        if (field_name.empty()) return false;
        if (presence == TLogApiCStructFieldPresenceKind::Unknown) return false;
        if (!layout.IsDeclared()) return false;
        if (presence == TLogApiCStructFieldPresenceKind::Defaulted && !default_value.IsPresent()) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
