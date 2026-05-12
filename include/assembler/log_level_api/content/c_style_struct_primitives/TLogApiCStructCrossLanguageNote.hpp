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

namespace assembler::log_level_api::content::c_style_struct_primitives {

/*
    Non-executable compatibility notes for foreign-language bindings.

    This is documentation-carrying metadata for the schema pack, not a code generator.
*/
struct TLogApiCStructCrossLanguageNote final {
    std::vector<std::string> languages{"C++", "MQL5", "C#", "Python"};
    std::string rule{
        "Schema layout is canonical by explicit offsets, sizes, endianness, and fixed-width fields; do not infer layout from compiler packing."
    };
};

} // namespace assembler::log_level_api::content::c_style_struct_primitives
