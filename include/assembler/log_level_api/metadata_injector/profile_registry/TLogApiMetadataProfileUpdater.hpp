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

#include "TLogApiMetadataProfileRegistry.hpp"
#include "TLogApiMetadataProfileUpdateResult.hpp"
#include "TLogApiMetadataProfileUpdateSet.hpp"

namespace assembler::log_level_api::metadata_injector::profile_registry {

/*
    Applies metadata profile updates.

    This component updates metadata configuration values. It is intentionally not
    a policy engine.
*/
class TLogApiMetadataProfileUpdater final {
public:
    [[nodiscard]] static TLogApiMetadataProfileUpdateResult Apply(
        const TLogApiMetadataProfileRegistry& source,
        const TLogApiMetadataProfileUpdateSet& update_set
    ) {
        TLogApiMetadataProfileUpdateResult result{};
        result.registry = source;

        if (!update_set.IsValid()) {
            result.issues.push_back({
                "LOGAPI_METADATA_PROFILE_UPDATE_SET_INVALID",
                "Metadata profile update set is invalid.",
                true
            });
            return result;
        }

        for (const auto& update : update_set.updates) {
            bool profile_found = false;

            for (auto& profile : result.registry.profiles) {
                if (profile.profile_name != update.target_profile_name) continue;
                profile_found = true;

                if (update.kind == TLogApiMetadataProfileUpdateKind::ActivateProfile) {
                    profile.status = TLogApiMetadataProfileStatus::Active;
                    continue;
                }

                if (update.kind == TLogApiMetadataProfileUpdateKind::SuspendProfile) {
                    profile.status = TLogApiMetadataProfileStatus::Suspended;
                    continue;
                }

                if (update.IsValueUpdate()) {
                    bool value_found = false;
                    for (auto& current : profile.config.default_values.values) {
                        if (current.field_id.value == update.field_value.field_id.value) {
                            current = update.field_value;
                            value_found = true;
                            break;
                        }
                    }

                    if (!value_found) {
                        profile.config.default_values.values.push_back(update.field_value);
                    }
                }
            }

            if (!profile_found) {
                result.issues.push_back({
                    "LOGAPI_METADATA_PROFILE_NOT_FOUND",
                    "Target metadata profile was not found for update.",
                    true
                });
            }
        }

        return result;
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
