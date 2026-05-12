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

#include <string>
#include <vector>

#include "TLogApiDefaultJsonSchemaPack.hpp"

namespace assembler::log_level_api::content::json_schemas {

struct TLogApiJsonSchemaPackView final {
    std::string pack_id{};
    std::string pack_name{};
    std::string pack_version{};
    std::size_t schema_count{0};
    bool declared{false};

    [[nodiscard]] static TLogApiJsonSchemaPackView From(const TLogApiDefaultJsonSchemaPack& pack) {
        TLogApiJsonSchemaPackView view{};
        view.pack_id = pack.id.ToString();
        view.pack_name = pack.pack_name;
        view.pack_version = pack.pack_version;
        view.schema_count = pack.schemas.size();
        view.declared = pack.IsDeclared();
        return view;
    }
};

} // namespace assembler::log_level_api::content::json_schemas
