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

#include "TLogApiCStructLevelSchemaDescriptor.hpp"

namespace assembler::log_level_api::content::c_style_struct_primitives {

struct TLogApiCStructLevelSchemaView final {
    std::string schema_id{};
    std::string schema_name{};
    std::string schema_version{};
    std::uint32_t total_size_bytes{0};
    std::uint32_t alignment_bytes{0};
    std::size_t required_count{0};
    std::size_t defaulted_count{0};
    std::size_t field_count{0};
    bool declared{false};

    [[nodiscard]] static TLogApiCStructLevelSchemaView From(const TLogApiCStructLevelSchemaDescriptor& schema) {
        TLogApiCStructLevelSchemaView view{};
        view.schema_id = schema.id.ToString();
        view.schema_name = schema.schema_name;
        view.schema_version = schema.schema_version;
        view.total_size_bytes = schema.layout.total_size_bytes;
        view.alignment_bytes = schema.layout.alignment_bytes;
        view.required_count = schema.layout.RequiredCount();
        view.defaulted_count = schema.layout.DefaultedCount();
        view.field_count = schema.layout.fields.size();
        view.declared = schema.IsDeclared();
        return view;
    }
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
