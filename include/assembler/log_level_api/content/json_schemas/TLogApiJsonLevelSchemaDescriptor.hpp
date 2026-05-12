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

#include "TLogApiJsonFieldSet.hpp"
#include "TLogApiJsonSchemaId.hpp"
#include "TLogApiJsonUnknownFieldPolicy.hpp"
#include "TLogApiLogLevelKind.hpp"

namespace assembler::log_level_api::content::json_schemas {

/*
    Level-specific JSON schema descriptor.

    The schema id/family/version/kind metadata is ultimately carried in the
    metadata block, but this descriptor names the JSON schema definition used
    by the configuration/add-on path.
*/
struct TLogApiJsonLevelSchemaDescriptor final {
    TLogApiJsonSchemaId id{};
    TLogApiLogLevelKind level{TLogApiLogLevelKind::Unknown};

    std::string schema_name{};
    std::string schema_version{"v1"};
    TLogApiJsonUnknownFieldPolicy unknown_field_policy{TLogApiJsonUnknownFieldPolicy::PreserveButDoNotValidate};

    TLogApiJsonFieldSet fields{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return id.IsValid()
            && level != TLogApiLogLevelKind::Unknown
            && !schema_name.empty()
            && !schema_version.empty()
            && unknown_field_policy != TLogApiJsonUnknownFieldPolicy::Unknown
            && fields.IsDeclared()
            && fields.RequiredCount() > 0;
    }
};

} // namespace assembler::log_level_api::content::json_schemas
