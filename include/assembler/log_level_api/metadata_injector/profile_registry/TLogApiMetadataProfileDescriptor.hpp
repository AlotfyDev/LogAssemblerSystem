#pragma once

/*
    LOGAPI-W19 — Metadata Profile Registry And Update Model

    Responsibility:
        Define production-hardening metadata profile registry, metadata profile
        identity, update model, profile lookup, update admission, and registry
        view/result carriers.

    Boundary:
        Metadata remains configuration/update concern, not policy.
        This wave does not implement content schemas, parsers, validators,
        timestamp stabilization, envelope assembly, circulation handoff, or
        policy assignment.

    Doctrine:
        Metadata is independent from content and timestamp.
        Metadata values may be updated through configured profile/update surfaces.
        Envelope assembly later composes content + metadata + stabilized timestamp.
*/

#include <string>

#include "assembler/log_level_api/metadata_injector/TLogApiMetadataInjectorConfig.hpp"

#include "TLogApiMetadataProfileId.hpp"
#include "TLogApiMetadataProfileStatus.hpp"

namespace assembler::log_level_api::metadata_injector::profile_registry {

/*
    Metadata profile descriptor.

    It wraps a metadata injector configuration with production-facing profile
    identity and status.
*/
struct TLogApiMetadataProfileDescriptor final {
    TLogApiMetadataProfileId id{};
    TLogApiMetadataProfileStatus status{TLogApiMetadataProfileStatus::Unknown};
    std::string profile_name{};
    assembler::log_level_api::metadata_injector::TLogApiMetadataInjectorConfig config{};

    [[nodiscard]] bool IsUsable() const noexcept {
        return id.IsValid()
            && (status == TLogApiMetadataProfileStatus::Registered
                || status == TLogApiMetadataProfileStatus::Active)
            && !profile_name.empty()
            && config.IsReady();
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
