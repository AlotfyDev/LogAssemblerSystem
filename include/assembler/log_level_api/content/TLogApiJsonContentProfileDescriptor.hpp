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

#include "TLogApiContentSchemaPathDescriptor.hpp"
#include "TLogApiContentSchemaPathStatus.hpp"

namespace assembler::log_level_api::content {

/*
    Default-friendly descriptor for the JSON schema path.

    It does not define JSON fields, required fields, defaults, or concrete JSON validators.
    Those belong to later JSON schema add-on waves.
*/
struct TLogApiJsonContentProfileDescriptor final {
    std::string profile_name{"default.json.minimal"};
    std::string schema_family_name{"json"};
    std::string schema_preset_name{"minimal"};

    [[nodiscard]] TLogApiContentSchemaPathDescriptor ToPathDescriptor() const {
        TLogApiContentSchemaPathDescriptor d{};
        d.kind = assembler::log_level_api::api_configurator::TLogApiSchemaPathKind::Json;
        d.status = TLogApiContentSchemaPathStatus::Resolved;
        d.path_name = profile_name;
        d.path_version = "v1";
        return d;
    }
};

} // namespace assembler::log_level_api::content
