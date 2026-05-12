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
#include <vector>

#include "TLogApiMetadataDefaultFieldPackView.hpp"
#include "TLogApiMetadataDefaultFieldPackSet.hpp"

namespace assembler::log_level_api::metadata_injector::default_field_packs {

struct TLogApiMetadataDefaultFieldPackSetView final {
    std::size_t pack_count{0};
    std::vector<TLogApiMetadataDefaultFieldPackView> packs{};
    bool declared{false};

    [[nodiscard]] static TLogApiMetadataDefaultFieldPackSetView From(const TLogApiMetadataDefaultFieldPackSet& set) {
        TLogApiMetadataDefaultFieldPackSetView view{};
        view.pack_count = set.packs.size();
        view.declared = set.IsDeclared();

        for (const auto& pack : set.packs) {
            view.packs.push_back(TLogApiMetadataDefaultFieldPackView::From(pack));
        }

        return view;
    }
};

} // namespace assembler::log_level_api::metadata_injector::default_field_packs
