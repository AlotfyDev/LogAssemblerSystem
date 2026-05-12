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

#include <string>

#include "assembler/log_level_api/metadata_injector/TLogApiMetadataFieldDescriptor.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataValueSet.hpp"

#include "TLogApiMetadataFieldPackId.hpp"
#include "TLogApiMetadataFieldPackKind.hpp"
#include "TLogApiMetadataFieldPackStatus.hpp"

namespace assembler::log_level_api::metadata_injector::default_field_packs {

struct TLogApiMetadataDefaultFieldPack final {
    TLogApiMetadataFieldPackId id{};
    TLogApiMetadataFieldPackKind kind{TLogApiMetadataFieldPackKind::Unknown};
    TLogApiMetadataFieldPackStatus status{TLogApiMetadataFieldPackStatus::Unknown};

    std::string pack_name{};
    std::string pack_version{"v1"};

    std::vector<assembler::log_level_api::metadata_injector::TLogApiMetadataFieldDescriptor> fields{};
    assembler::log_level_api::metadata_injector::TLogApiMetadataValueSet values{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (!id.IsValid()) return false;
        if (kind == TLogApiMetadataFieldPackKind::Unknown) return false;
        if (status != TLogApiMetadataFieldPackStatus::Declared
            && status != TLogApiMetadataFieldPackStatus::Active) return false;
        if (pack_name.empty() || pack_version.empty()) return false;
        if (fields.empty()) return false;
        for (const auto& field : fields) {
            if (!field.IsDeclared()) return false;
            if (field.enabled && values.Find(field.id) == nullptr) return false;
        }
        return true;
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs
