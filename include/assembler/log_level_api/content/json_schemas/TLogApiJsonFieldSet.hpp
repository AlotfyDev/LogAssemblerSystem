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

#include <vector>

#include "TLogApiJsonFieldDescriptor.hpp"
#include "TLogApiJsonFieldPresenceKind.hpp"

namespace assembler::log_level_api::content::json_schemas {

struct TLogApiJsonFieldSet final {
    std::vector<TLogApiJsonFieldDescriptor> fields{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        for (const auto& field : fields) {
            if (!field.IsDeclared()) return false;
        }
        return true;
    }

    [[nodiscard]] std::size_t RequiredCount() const noexcept {
        std::size_t count = 0;
        for (const auto& field : fields) {
            if (field.presence == TLogApiJsonFieldPresenceKind::Required) ++count;
        }
        return count;
    }

    [[nodiscard]] std::size_t DefaultedCount() const noexcept {
        std::size_t count = 0;
        for (const auto& field : fields) {
            if (field.presence == TLogApiJsonFieldPresenceKind::Defaulted) ++count;
        }
        return count;
    }
};

} // namespace assembler::log_level_api::content::json_schemas
