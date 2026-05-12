#pragma once

/*
    LOGAPI-W06 — API Facade Content-Only Input

    This header belongs to the Log Level API consuming facade layer.

    Responsibility:
        Define the content-only API input surface and admission result carriers
        that consume a previously resolved active profile.

    Boundary:
        The API facade receives content only.
        It must not receive schema definitions, metadata struct definitions,
        validator bindings, timestamp stabilization rules, envelope assembly
        instructions, communication bindings, or policy assignment material with
        every payload.

    Doctrine:
        Configure first. Consume content only.
        The API facade uses an already resolved active profile.
*/

#include "assembler/log_level_api/api_configurator/TLogApiActiveProfile.hpp"
#include "assembler/log_level_api/content/TLogApiContentProfileDescriptor.hpp"
#include "assembler/log_level_api/validator/TLogApiValidatorBindingDescriptor.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataInjectorConfig.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampStabilizerConfig.hpp"

namespace assembler::log_level_api::api_facade {

/*
    Read-only configuration references used by the facade.

    The facade sees resolved configuration. It does not own or mutate the
    configuration sources.
*/
struct TLogApiFacadeConfigRef final {
    const assembler::log_level_api::api_configurator::TLogApiActiveProfile* active_profile{nullptr};
    const assembler::log_level_api::content::TLogApiContentProfileDescriptor* content_profile{nullptr};
    const assembler::log_level_api::validator::TLogApiValidatorBindingDescriptor* validator_binding{nullptr};
    const assembler::log_level_api::metadata_injector::TLogApiMetadataInjectorConfig* metadata_config{nullptr};
    const assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampStabilizerConfig* timestamp_config{nullptr};

    [[nodiscard]] bool IsReady() const noexcept {
        if (active_profile == nullptr || !active_profile->IsReadyForConsumingPath()) return false;
        if (content_profile == nullptr || !content_profile->IsReadyForConfigurationUse()) return false;

        if (active_profile->validation_required) {
            if (validator_binding == nullptr || !validator_binding->IsResolved()) return false;
        }

        if (active_profile->metadata_enabled) {
            if (metadata_config == nullptr || !metadata_config->IsReady()) return false;
        }

        if (active_profile->timestamp_stabilization_enabled) {
            if (timestamp_config == nullptr || !timestamp_config->IsResolved()) return false;
        }

        return true;
    }
};

} // namespace assembler::log_level_api::api_facade
