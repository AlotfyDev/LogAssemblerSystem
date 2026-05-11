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

#include <string>

#include "TLogApiAssemblerFamilyKind.hpp"
#include "TLogApiConfigurationId.hpp"
#include "TLogApiConfigurationStatus.hpp"
#include "TLogApiSchemaPathKind.hpp"

namespace assembler::log_level_api::api_configurator {

/*
    Resolved profile used by the consuming path.

    The API facade receives content only. It should read a previously resolved
    TLogApiActiveProfile and never require callers to resend schema definitions,
    metadata structures, timestamp rules, or validator bindings with each content payload.
*/
struct TLogApiActiveProfile final {
    TLogApiConfigurationId configuration_id{};
    TLogApiConfigurationStatus status{TLogApiConfigurationStatus::Unknown};

    TLogApiSchemaPathKind schema_path{TLogApiSchemaPathKind::Unknown};
    TLogApiAssemblerFamilyKind assembler_family{TLogApiAssemblerFamilyKind::Unknown};

    bool validation_required{false};
    bool metadata_enabled{false};
    bool timestamp_stabilization_enabled{false};

    std::string content_profile_name{};
    std::string metadata_profile_name{};
    std::string timestamp_profile_name{};
    std::string validator_binding_name{};

    [[nodiscard]] bool IsReadyForConsumingPath() const noexcept {
        if (!configuration_id.IsValid()) return false;
        if (status != TLogApiConfigurationStatus::Resolved && status != TLogApiConfigurationStatus::Active) return false;
        if (schema_path == TLogApiSchemaPathKind::Unknown) return false;
        if (assembler_family == TLogApiAssemblerFamilyKind::Unknown) return false;
        if (content_profile_name.empty()) return false;
        if (metadata_enabled && metadata_profile_name.empty()) return false;
        if (timestamp_stabilization_enabled && timestamp_profile_name.empty()) return false;
        if (validation_required && validator_binding_name.empty()) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::api_configurator
