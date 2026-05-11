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

#include "TLogApiActiveProfile.hpp"
#include "TLogApiConfigurationIssue.hpp"
#include "TLogApiConfigurationPatch.hpp"
#include "TLogApiConfigurationResult.hpp"
#include "TLogApiConfigurationStatus.hpp"
#include "TLogApiDefaultConfiguration.hpp"

namespace assembler::log_level_api::api_configurator {

/*
    Configuration-time resolver.

    This class resolves default configuration plus optional consumer patch into
    TLogApiActiveProfile. It does not consume content and does not execute the
    Log Level API hot path.
*/
class TLogApiConfigurator final {
public:
    [[nodiscard]] static TLogApiConfigurationResult Resolve(
        const TLogApiDefaultConfiguration& defaults,
        const TLogApiConfigurationPatch& patch = {}
    ) {
        TLogApiActiveProfile profile{};
        profile.configuration_id = defaults.id;
        profile.status = TLogApiConfigurationStatus::Resolved;

        profile.schema_path = patch.schema_path.value_or(defaults.schema_path);
        profile.assembler_family = patch.assembler_family.value_or(defaults.assembler_family);

        profile.validation_required = patch.validation_required.value_or(defaults.validation_required);
        profile.metadata_enabled = patch.metadata_enabled.value_or(defaults.metadata_enabled);
        profile.timestamp_stabilization_enabled = patch.timestamp_stabilization_enabled.value_or(defaults.timestamp_stabilization_enabled);

        profile.content_profile_name = patch.content_profile_name.value_or(defaults.content_profile_name);
        profile.metadata_profile_name = patch.metadata_profile_name.value_or(defaults.metadata_profile_name);
        profile.timestamp_profile_name = patch.timestamp_profile_name.value_or(defaults.timestamp_profile_name);
        profile.validator_binding_name = patch.validator_binding_name.value_or(defaults.validator_binding_name);

        TLogApiConfigurationResult result{};
        result.profile = profile;

        if (profile.schema_path == TLogApiSchemaPathKind::Unknown) {
            result.issues.push_back({"LOGAPI_CFG_SCHEMA_PATH_UNKNOWN", "Schema path must be resolved before consuming content.", true});
        }

        if (profile.assembler_family == TLogApiAssemblerFamilyKind::Unknown) {
            result.issues.push_back({"LOGAPI_CFG_ASSEMBLER_UNKNOWN", "Assembler family must be selected before the hot path begins.", true});
        }

        if (profile.content_profile_name.empty()) {
            result.issues.push_back({"LOGAPI_CFG_CONTENT_PROFILE_EMPTY", "Content profile must be named before consuming content.", true});
        }

        if (profile.validation_required && profile.validator_binding_name.empty()) {
            result.issues.push_back({"LOGAPI_CFG_VALIDATOR_BINDING_EMPTY", "Validation-required profile must resolve a validator binding before consumption.", true});
        }

        if (profile.metadata_enabled && profile.metadata_profile_name.empty()) {
            result.issues.push_back({"LOGAPI_CFG_METADATA_PROFILE_EMPTY", "Metadata-enabled profile must resolve a metadata profile before consumption.", true});
        }

        if (profile.timestamp_stabilization_enabled && profile.timestamp_profile_name.empty()) {
            result.issues.push_back({"LOGAPI_CFG_TIMESTAMP_PROFILE_EMPTY", "Timestamp-stabilized profile must resolve a timestamp profile before consumption.", true});
        }

        return result;
    }
};

} // namespace assembler::log_level_api::api_configurator
