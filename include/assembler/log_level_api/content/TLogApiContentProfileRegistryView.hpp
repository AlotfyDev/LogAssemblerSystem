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
#include <vector>

#include "TLogApiContentProfileDescriptor.hpp"

namespace assembler::log_level_api::content {

/*
    Read-only view over registered content profiles.

    This is not a runtime registry implementation. It is a view/carrier used by
    configuration-time code and tests.
*/
struct TLogApiContentProfileRegistryView final {
    std::vector<TLogApiContentProfileDescriptor> profiles{};

    [[nodiscard]] const TLogApiContentProfileDescriptor* FindByName(const std::string& name) const noexcept {
        for (const auto& profile : profiles) {
            if (profile.profile_name == name) return &profile;
        }
        return nullptr;
    }

    [[nodiscard]] bool HasReadyProfile(const std::string& name) const noexcept {
        const auto* profile = FindByName(name);
        return profile != nullptr && profile->IsReadyForConfigurationUse();
    }
};

} // namespace assembler::log_level_api::content
