#pragma once

#include <cstddef>
#include <cstdint>

#include "assembler/ecosystem_governance/policy_registry/versioning/TPolicyRegistryPublicationSnapshot.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryPublicationView.hpp
 * Wave: EG-POL-W17_Registry_Versioning_And_Publication_View
 * Domain: ecosystem_governance / policy_registry / versioning
 *
 * Architectural boundary:
 *   W17 implements the first registry-versioning and publication-view layer
 *   derived from EG-POL-ARCH-006_Policy_Source_Publication_And_Registry_Versioning
 *   and EG-POL-ARCH-008_Compliance_And_Validation_Matrix. It follows W11
 *   Policy Registry Basics and W16 Policy Source And Publication. The wave is
 *   descriptive and non-executing: it indexes registry descriptors by policy
 *   version and publication state, builds publication snapshots, performs
 *   versioned lookup, and exposes publication views without persisting a
 *   database, assigning policies, realizing policies, invoking targets, or
 *   mutating runtime behavior.
 *
 * Relationship to prior waves:
 *   - W01 supplies policy identity, family, scope, and version primitives.
 *   - W09 supplies TPolicy as semantic aggregate, not executor.
 *   - W10 supplies non-executing assignment basics; W17 does not activate
 *     assignments.
 *   - W11 supplies registry entry descriptors, registry entries, lookup keys,
 *     snapshots, and registry views; W17 adds versioning and publication views
 *     above that base catalog vocabulary.
 *   - W12-W15 supply family/scope, target capability, compatibility, and
 *     assignment lifecycle concepts consumed later by registry-aware workflows.
 *   - W16 supplies source descriptors, publication states, publication records,
 *     and version lineage records consumed by this wave.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-006 states that source is not validity, ingestion is not
 *   publication, publication is not assignment, assignment is not realization,
 *   registry is not a storage engine, and rollback readiness is not rollback
 *   execution. EG-POL-ARCH-008 requires registry versioning to be validated
 *   before runtime readiness and realizer work. This file preserves those
 *   non-collapse rules.
 *
 * Explicit non-responsibilities:
 *   This file does not implement source parsing, persistent registry storage,
 *   database registry, authority roles, assignment activation, realization
 *   contracts, runtime readiness, TPolicyRealizer, target invocation, material
 *   circulation behavior, communication binding, telemetry, logging, or
 *   persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation describes the complete architectural responsibility, while
 *   the implementation intentionally remains a small set of value carriers and
 *   structural helpers.
 *
 * File responsibility:
 *   TPolicyRegistryPublicationView is a compact read-only summary of a publication snapshot. It supports review and compliance by exposing counts and visibility posture only. It does not expose registry storage, does not publish policies, and does not authorize assignment or realization.
 */

struct TPolicyRegistryPublicationView final
{
    std::uint64_t snapshot_id{0};
    std::uint64_t snapshot_sequence{0};
    std::size_t visible_records{0};
    std::size_t published_count{0};
    std::size_t deprecated_count{0};
    std::size_t retired_count{0};
    std::size_t rollback_candidate_count{0};
    std::size_t forbidden_count{0};
    bool has_production_visible_record{false};

    [[nodiscard]] static TPolicyRegistryPublicationView FromSnapshot(
        const TPolicyRegistryPublicationSnapshot& snapshot) noexcept
    {
        TPolicyRegistryPublicationView view{};
        view.snapshot_id = snapshot.snapshot_id;
        view.snapshot_sequence = snapshot.snapshot_sequence;
        view.visible_records = snapshot.visible_records.size();
        view.published_count = snapshot.published_count;
        view.deprecated_count = snapshot.deprecated_count;
        view.retired_count = snapshot.retired_count;
        view.rollback_candidate_count = snapshot.rollback_candidate_count;
        view.forbidden_count = snapshot.forbidden_count;
        view.has_production_visible_record = snapshot.HasProductionVisibleRecord();
        return view;
    }

    [[nodiscard]] constexpr bool IsValidView() const noexcept
    {
        return snapshot_id != 0 && snapshot_sequence != 0;
    }

    [[nodiscard]] constexpr bool HasWarnings() const noexcept
    {
        return deprecated_count != 0 || rollback_candidate_count != 0;
    }

    [[nodiscard]] constexpr bool HasBlockingVisibility() const noexcept
    {
        return forbidden_count != 0;
    }
};

} // namespace assembler::ecosystem_governance::policy_registry
