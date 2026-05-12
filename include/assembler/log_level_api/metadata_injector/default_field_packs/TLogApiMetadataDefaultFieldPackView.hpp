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

#include "TLogApiMetadataDefaultFieldPack.hpp"

namespace assembler::log_level_api::metadata_injector::default_field_packs {

struct TLogApiMetadataDefaultFieldPackView final {
    std::string pack_id{};
    std::string pack_name{};
    std::string pack_version{};
    std::size_t field_count{0};
    bool declared{false};

    [[nodiscard]] static TLogApiMetadataDefaultFieldPackView From(const TLogApiMetadataDefaultFieldPack& pack) {
        TLogApiMetadataDefaultFieldPackView view{};
        view.pack_id = pack.id.ToString();
        view.pack_name = pack.pack_name;
        view.pack_version = pack.pack_version;
        view.field_count = pack.fields.size();
        view.declared = pack.IsDeclared();
        return view;
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs
