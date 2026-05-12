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

#include "TLogApiJsonLevelSchemaDescriptor.hpp"
#include "TLogApiJsonSchemaPackId.hpp"

namespace assembler::log_level_api::content::json_schemas {

struct TLogApiDefaultJsonSchemaPack final {
    TLogApiJsonSchemaPackId id{};
    std::string pack_name{};
    std::string pack_version{"v1"};
    std::vector<TLogApiJsonLevelSchemaDescriptor> schemas{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (!id.IsValid()) return false;
        if (pack_name.empty() || pack_version.empty()) return false;
        if (schemas.empty()) return false;
        for (const auto& schema : schemas) {
            if (!schema.IsDeclared()) return false;
        }
        return true;
    }

    [[nodiscard]] const TLogApiJsonLevelSchemaDescriptor* FindByLevel(TLogApiLogLevelKind level) const noexcept {
        for (const auto& schema : schemas) {
            if (schema.level == level) return &schema;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::content::json_schemas
