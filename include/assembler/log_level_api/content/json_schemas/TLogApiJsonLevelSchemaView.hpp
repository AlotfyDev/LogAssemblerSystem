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

#include "TLogApiJsonLevelSchemaDescriptor.hpp"

namespace assembler::log_level_api::content::json_schemas {

struct TLogApiJsonLevelSchemaView final {
    std::string schema_id{};
    std::string schema_name{};
    std::string schema_version{};
    std::size_t required_count{0};
    std::size_t defaulted_count{0};
    std::size_t field_count{0};
    bool declared{false};

    [[nodiscard]] static TLogApiJsonLevelSchemaView From(const TLogApiJsonLevelSchemaDescriptor& schema) {
        TLogApiJsonLevelSchemaView view{};
        view.schema_id = schema.id.ToString();
        view.schema_name = schema.schema_name;
        view.schema_version = schema.schema_version;
        view.required_count = schema.fields.RequiredCount();
        view.defaulted_count = schema.fields.DefaultedCount();
        view.field_count = schema.fields.fields.size();
        view.declared = schema.IsDeclared();
        return view;
    }
};

} // namespace assembler::log_level_api::content::json_schemas
