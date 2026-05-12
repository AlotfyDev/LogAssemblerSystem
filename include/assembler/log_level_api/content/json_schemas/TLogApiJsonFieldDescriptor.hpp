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

#include "TLogApiJsonDefaultValue.hpp"
#include "TLogApiJsonFieldId.hpp"
#include "TLogApiJsonFieldPresenceKind.hpp"
#include "TLogApiJsonFieldValueKind.hpp"

namespace assembler::log_level_api::content::json_schemas {

/*
    JSON field descriptor.

    This is a schema descriptor, not a parsed JSON field and not a metadata field.
*/
struct TLogApiJsonFieldDescriptor final {
    TLogApiJsonFieldId id{};
    std::string field_name{};
    TLogApiJsonFieldValueKind value_kind{TLogApiJsonFieldValueKind::Unknown};
    TLogApiJsonFieldPresenceKind presence{TLogApiJsonFieldPresenceKind::Unknown};
    TLogApiJsonDefaultValue default_value{};
    bool override_allowed{true};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (!id.IsValid()) return false;
        if (field_name.empty()) return false;
        if (value_kind == TLogApiJsonFieldValueKind::Unknown) return false;
        if (presence == TLogApiJsonFieldPresenceKind::Unknown) return false;
        if (presence == TLogApiJsonFieldPresenceKind::Defaulted && !default_value.IsPresent()) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::content::json_schemas
