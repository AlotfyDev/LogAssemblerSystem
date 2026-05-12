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

#include "TLogApiMetadataProfileRegistry.hpp"
#include "TLogApiMetadataProfileUpdateIssue.hpp"

namespace assembler::log_level_api::metadata_injector::profile_registry {

struct TLogApiMetadataProfileUpdateResult final {
    TLogApiMetadataProfileRegistry registry{};
    std::vector<TLogApiMetadataProfileUpdateIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
