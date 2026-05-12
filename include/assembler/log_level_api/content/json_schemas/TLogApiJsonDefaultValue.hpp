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

#include <cstdint>
#include <string>
#include <variant>

#include "TLogApiJsonFieldValueKind.hpp"

namespace assembler::log_level_api::content::json_schemas {

using TLogApiJsonScalarDefaultValue = std::variant<
    std::monostate,
    std::string,
    std::int64_t,
    std::uint64_t,
    double,
    bool
>;

struct TLogApiJsonDefaultValue final {
    TLogApiJsonFieldValueKind value_kind{TLogApiJsonFieldValueKind::Unknown};
    TLogApiJsonScalarDefaultValue value{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return value_kind != TLogApiJsonFieldValueKind::Unknown
            && !std::holds_alternative<std::monostate>(value);
    }
};

} // namespace assembler::log_level_api::content::json_schemas
