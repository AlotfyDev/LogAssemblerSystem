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

#include <vector>

#include "TLogApiMetadataProfileDescriptor.hpp"
#include "TLogApiMetadataProfileLookupKey.hpp"
#include "TLogApiMetadataProfileLookupResult.hpp"

namespace assembler::log_level_api::metadata_injector::profile_registry {

/*
    Bounded in-memory metadata profile registry.

    This is not persistent storage and not a policy registry.
*/
struct TLogApiMetadataProfileRegistry final {
    std::vector<TLogApiMetadataProfileDescriptor> profiles{};

    [[nodiscard]] TLogApiMetadataProfileLookupResult Lookup(const TLogApiMetadataProfileLookupKey& key) const noexcept {
        if (!key.IsValid()) return {};
        for (const auto& profile : profiles) {
            if (profile.profile_name == key.profile_name) return {&profile};
        }
        return {};
    }

    [[nodiscard]] bool HasUsableProfile(const TLogApiMetadataProfileLookupKey& key) const noexcept {
        return Lookup(key).FoundUsable();
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
