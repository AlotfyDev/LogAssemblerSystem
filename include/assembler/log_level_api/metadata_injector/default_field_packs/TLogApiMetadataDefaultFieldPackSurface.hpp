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

#include "TLogApiMetadataDefaultFieldPack.hpp"
#include "TLogApiMetadataDefaultFieldPackFactory.hpp"
#include "TLogApiMetadataDefaultFieldPackSet.hpp"
#include "TLogApiMetadataDefaultFieldPackSetView.hpp"
#include "TLogApiMetadataDefaultFieldPackView.hpp"
#include "TLogApiMetadataFieldPackComposer.hpp"
#include "TLogApiMetadataFieldPackComposerIssue.hpp"
#include "TLogApiMetadataFieldPackCompositionResult.hpp"
#include "TLogApiMetadataFieldPackId.hpp"
#include "TLogApiMetadataFieldPackKind.hpp"
#include "TLogApiMetadataFieldPackStatus.hpp"
