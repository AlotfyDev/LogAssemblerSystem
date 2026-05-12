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

#include "TLogApiMetadataDefaultFieldPack.hpp"

namespace assembler::log_level_api::metadata_injector::default_field_packs {

struct TLogApiMetadataDefaultFieldPackSet final {
    std::vector<TLogApiMetadataDefaultFieldPack> packs{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (packs.empty()) return false;
        for (const auto& pack : packs) {
            if (!pack.IsDeclared()) return false;
        }
        return true;
    }

    [[nodiscard]] const TLogApiMetadataDefaultFieldPack* Find(TLogApiMetadataFieldPackKind kind) const noexcept {
        for (const auto& pack : packs) {
            if (pack.kind == kind) return &pack;
        }
        return nullptr;
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs
