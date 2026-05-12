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

#include "TLogApiDefaultCStructSchemaPack.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

struct TLogApiCStructSchemaPackView final {
    std::string pack_id{};
    std::string pack_name{};
    std::string pack_version{};
    std::size_t schema_count{0};
    bool declared{false};

    [[nodiscard]] static TLogApiCStructSchemaPackView From(const TLogApiDefaultCStructSchemaPack& pack) {
        TLogApiCStructSchemaPackView view{};
        view.pack_id = pack.id.ToString();
        view.pack_name = pack.pack_name;
        view.pack_version = pack.pack_version;
        view.schema_count = pack.schemas.size();
        view.declared = pack.IsDeclared();
        return view;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
