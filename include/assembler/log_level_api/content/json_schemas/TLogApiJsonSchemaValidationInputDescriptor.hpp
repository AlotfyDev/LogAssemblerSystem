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

#include "TLogApiJsonLevelSchemaDescriptor.hpp"

namespace assembler::log_level_api::content::json_schemas {

/*
    Schema-side validator input descriptor.

    This is not a concrete validator. It exposes required/default field sets to
    the validator binding layer.
*/
struct TLogApiJsonSchemaValidationInputDescriptor final {
    const TLogApiJsonLevelSchemaDescriptor* schema{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        return schema != nullptr && schema->IsDeclared();
    }

    [[nodiscard]] std::size_t RequiredFieldCount() const noexcept {
        return IsReady() ? schema->fields.RequiredCount() : 0;
    }

    [[nodiscard]] std::size_t DefaultedFieldCount() const noexcept {
        return IsReady() ? schema->fields.DefaultedCount() : 0;
    }
};

} // namespace assembler::log_level_api::content::json_schemas
