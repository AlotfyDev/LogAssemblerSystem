#pragma once

/*
    LOGAPI-W01 — Configuration Surface And Default Profile

    This header belongs to the Log Level API configuration surface.

    Responsibility:
        Provide configuration-time types that allow Log Level API to be prepared
        before the consuming hot path receives content.

    Boundary:
        This file must not define concrete content schemas, concrete validators,
        metadata field implementation, timestamp stabilization algorithms,
        envelope assembly behavior, circulation handoff, or policy assignment.

    Doctrine:
        Configure first. Consume content only.
        The hot path uses an already resolved active profile.
*/

#include <optional>
#include <string>
#include <vector>

#include "TLogApiAssemblerFamilyKind.hpp"
#include "TLogApiSchemaPathKind.hpp"

namespace assembler::log_level_api::api_configurator {

/*
    Consumer-provided configuration changes.

    This is intentionally a configuration-time object.
    The consuming hot path must not receive this patch together with payload.
*/
struct TLogApiConfigurationPatch final {
    std::optional<TLogApiSchemaPathKind> schema_path{};
    std::optional<TLogApiAssemblerFamilyKind> assembler_family{};

    std::optional<bool> validation_required{};
    std::optional<bool> metadata_enabled{};
    std::optional<bool> timestamp_stabilization_enabled{};

    std::optional<std::string> content_profile_name{};
    std::optional<std::string> metadata_profile_name{};
    std::optional<std::string> timestamp_profile_name{};
    std::optional<std::string> validator_binding_name{};

    std::vector<std::string> notes{};
};

} // namespace assembler::log_level_api::api_configurator
