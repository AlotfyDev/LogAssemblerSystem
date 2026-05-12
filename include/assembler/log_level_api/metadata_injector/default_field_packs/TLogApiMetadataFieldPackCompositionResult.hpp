#pragma once

/*
    LOGAPI-W20 — Metadata Default Field Packs

    Responsibility:
        Define default metadata field packs and helpers for composing reusable
        metadata field/value groups into metadata profile configurations.

    Boundary:
        Metadata field packs are configuration conveniences, not policy objects.
        This wave does not implement content schemas, parsers, validators,
        timestamp stabilization, envelope assembly, circulation handoff,
        persistence, or policy assignment.

    Doctrine:
        Metadata is independent from content and timestamp.
        Default field packs reduce repeated per-call payload authoring.
        Metadata values remain mutable through profile/update surfaces.
*/

#include <vector>

#include "assembler/log_level_api/metadata_injector/TLogApiMetadataInjectorConfig.hpp"

#include "TLogApiMetadataFieldPackComposerIssue.hpp"

namespace assembler::log_level_api::metadata_injector::default_field_packs {

struct TLogApiMetadataFieldPackCompositionResult final {
    assembler::log_level_api::metadata_injector::TLogApiMetadataInjectorConfig config{};
    std::vector<TLogApiMetadataFieldPackComposerIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return config.IsReady() && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs
