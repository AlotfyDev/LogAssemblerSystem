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

#include "assembler/log_level_api/metadata_injector/TLogApiDefaultMetadataProfile.hpp"

#include "TLogApiMetadataProfileDescriptor.hpp"
#include "TLogApiMetadataProfileRegistry.hpp"

namespace assembler::log_level_api::metadata_injector::profile_registry {

struct TLogApiDefaultMetadataProfileRegistry final {
    [[nodiscard]] static TLogApiMetadataProfileRegistry Make() {
        TLogApiMetadataProfileDescriptor default_profile{};
        default_profile.id = TLogApiMetadataProfileId{1};
        default_profile.status = TLogApiMetadataProfileStatus::Active;
        default_profile.profile_name = "default.metadata.struct";
        default_profile.config = assembler::log_level_api::metadata_injector::TLogApiDefaultMetadataProfile::Make();

        TLogApiMetadataProfileRegistry registry{};
        registry.profiles.push_back(default_profile);
        return registry;
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
