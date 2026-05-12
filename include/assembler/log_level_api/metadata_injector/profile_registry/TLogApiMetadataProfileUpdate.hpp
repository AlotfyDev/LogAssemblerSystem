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

#include "assembler/log_level_api/metadata_injector/TLogApiMetadataFieldValue.hpp"

#include "TLogApiMetadataProfileUpdateKind.hpp"

namespace assembler::log_level_api::metadata_injector::profile_registry {

struct TLogApiMetadataProfileUpdate final {
    TLogApiMetadataProfileUpdateKind kind{TLogApiMetadataProfileUpdateKind::Unknown};
    std::string target_profile_name{};
    assembler::log_level_api::metadata_injector::TLogApiMetadataFieldValue field_value{};

    [[nodiscard]] bool IsValueUpdate() const noexcept {
        return kind == TLogApiMetadataProfileUpdateKind::ReplaceFieldValue
            || kind == TLogApiMetadataProfileUpdateKind::AddOrReplaceFieldValue;
    }

    [[nodiscard]] bool IsValid() const noexcept {
        if (target_profile_name.empty()) return false;
        if (kind == TLogApiMetadataProfileUpdateKind::Unknown) return false;
        if (IsValueUpdate() && !field_value.IsPresent()) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::metadata_injector::profile_registry
