#pragma once

/*
    LOGAPI-W02 — Content Profile And Schema Paths

    This header belongs to the Log Level API content-profile layer.

    Responsibility:
        Define content profile abstractions and schema path descriptors used by
        the configuration surface before the consuming hot path receives content.

    Boundary:
        This file must not define concrete JSON schemas, concrete C-style struct
        layouts, concrete validators, metadata struct implementation, timestamp
        stabilization algorithms, envelope assembly, circulation handoff, or
        policy assignment.

    Doctrine:
        Content schema paths are open and configurable.
        JSON and C-style struct primitive paths are separated.
        The consuming API receives content only and uses an already resolved
        active profile.
*/

#include <string>

#include "assembler/log_level_api/api_configurator/TLogApiSchemaPathKind.hpp"

#include "TLogApiContentSchemaPathStatus.hpp"

namespace assembler::log_level_api::content {

/*
    Describes which schema path a content profile uses.

    This descriptor separates the JSON schema path from the C-style struct
    primitive schema path without defining either concrete schema family.
*/
struct TLogApiContentSchemaPathDescriptor final {
    assembler::log_level_api::api_configurator::TLogApiSchemaPathKind kind{
        assembler::log_level_api::api_configurator::TLogApiSchemaPathKind::Unknown
    };

    TLogApiContentSchemaPathStatus status{TLogApiContentSchemaPathStatus::Unknown};

    std::string path_name{};
    std::string path_version{};

    [[nodiscard]] bool IsJsonPath() const noexcept {
        return kind == assembler::log_level_api::api_configurator::TLogApiSchemaPathKind::Json;
    }

    [[nodiscard]] bool IsCStyleStructPrimitivePath() const noexcept {
        return kind == assembler::log_level_api::api_configurator::TLogApiSchemaPathKind::CStyleStructPrimitives;
    }

    [[nodiscard]] bool IsResolved() const noexcept {
        return kind != assembler::log_level_api::api_configurator::TLogApiSchemaPathKind::Unknown
            && (status == TLogApiContentSchemaPathStatus::Resolved
                || status == TLogApiContentSchemaPathStatus::Active)
            && !path_name.empty();
    }
};

} // namespace assembler::log_level_api::content
