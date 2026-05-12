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

#include "TLogApiContentProfileId.hpp"
#include "TLogApiContentProfileStatus.hpp"
#include "TLogApiContentSchemaPathDescriptor.hpp"

namespace assembler::log_level_api::content {

/*
    Describes a content profile selected during configuration.

    It intentionally stores names/references to schema profile and validator binding
    rather than concrete schema definitions or concrete validator types.
*/
struct TLogApiContentProfileDescriptor final {
    TLogApiContentProfileId id{};
    TLogApiContentProfileStatus status{TLogApiContentProfileStatus::Unknown};

    std::string profile_name{};
    TLogApiContentSchemaPathDescriptor schema_path{};

    bool validation_required{false};
    std::string validator_binding_name{};

    [[nodiscard]] bool IsReadyForConfigurationUse() const noexcept {
        if (!id.IsValid()) return false;
        if (status != TLogApiContentProfileStatus::Resolved
            && status != TLogApiContentProfileStatus::Active) return false;
        if (profile_name.empty()) return false;
        if (!schema_path.IsResolved()) return false;
        if (validation_required && validator_binding_name.empty()) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::content
