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
#include <vector>

#include "TLogApiMetadataProfileRegistry.hpp"

namespace assembler::log_level_api::metadata_injector::profile_registry {

struct TLogApiMetadataProfileRegistryView final {
    std::size_t profile_count{0};
    std::vector<std::string> profile_names{};
    std::vector<std::string> active_profile_names{};

    [[nodiscard]] static TLogApiMetadataProfileRegistryView From(const TLogApiMetadataProfileRegistry& registry) {
        TLogApiMetadataProfileRegistryView view{};
        view.profile_count = registry.profiles.size();

        for (const auto& profile : registry.profiles) {
            view.profile_names.push_back(profile.profile_name);
            if (profile.status == TLogApiMetadataProfileStatus::Active) {
                view.active_profile_names.push_back(profile.profile_name);
            }
        }

        return view;
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
