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
#include <vector>

#include "TLogApiCStructLevelSchemaDescriptor.hpp"
#include "TLogApiCStructSchemaPackId.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

struct TLogApiDefaultCStructSchemaPack final {
    TLogApiCStructSchemaPackId id{};
    std::string pack_name{};
    std::string pack_version{"v1"};
    std::vector<TLogApiCStructLevelSchemaDescriptor> schemas{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (!id.IsValid()) return false;
        if (pack_name.empty() || pack_version.empty()) return false;
        if (schemas.empty()) return false;
        for (const auto& schema : schemas) {
            if (!schema.IsDeclared()) return false;
        }
        return true;
    }

    [[nodiscard]] const TLogApiCStructLevelSchemaDescriptor* FindByLevel(TLogApiCStructLogLevelKind level) const noexcept {
        for (const auto& schema : schemas) {
            if (schema.level == level) return &schema;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
