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
    Default editable bootstrap configuration.

    This does not define concrete JSON schemas or C-style struct primitive schemas.
    It only chooses the default path and points to named profiles that later waves
    may define in their owning folders.
*/
struct TLogApiDefaultConfiguration final {
    TLogApiConfigurationId id{1};
    TLogApiConfigurationStatus status{TLogApiConfigurationStatus::Defaulted};

    TLogApiSchemaPathKind schema_path{TLogApiSchemaPathKind::Json};
    TLogApiAssemblerFamilyKind assembler_family{TLogApiAssemblerFamilyKind::ValidatorComposedEnvelopeAssembler};

    bool validation_required{true};
    bool metadata_enabled{true};
    bool timestamp_stabilization_enabled{true};

    std::string content_profile_name{"default.json.minimal"};
    std::string metadata_profile_name{"default.metadata.struct"};
    std::string timestamp_profile_name{"default.timestamp.stabilizer"};
    std::string validator_binding_name{"default.json.validator.binding"};
};

} // namespace assembler::log_level_api::api_configurator
