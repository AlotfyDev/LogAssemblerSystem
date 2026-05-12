#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "assembler/ecosystem_governance/policy_registry/versioning/TPolicyRegistryVersionIndex.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryPublicationSnapshot.hpp
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
 *   TPolicyRegistryPublicationSnapshot captures a point-in-time registry-visible publication view derived from a version index. It supports audit, assignment-review, rollback analysis, and publication review without assigning policies, executing policies, or representing runtime state.
 */

struct TPolicyRegistryPublicationSnapshot final
{
    std::uint64_t snapshot_id{0};
    std::uint64_t snapshot_sequence{0};
    std::vector<TPolicyRegistryVersionIndexRecord> visible_records{};
    std::size_t published_count{0};
    std::size_t deprecated_count{0};
    std::size_t retired_count{0};
    std::size_t rollback_candidate_count{0};
    std::size_t forbidden_count{0};

    [[nodiscard]] bool IsValidSnapshot() const noexcept
    {
        return snapshot_id != 0 && snapshot_sequence != 0;
    }

    [[nodiscard]] bool Empty() const noexcept { return visible_records.empty(); }

    [[nodiscard]] static TPolicyRegistryPublicationSnapshot FromIndex(
        std::uint64_t id,
        std::uint64_t sequence,
        const TPolicyRegistryVersionIndex& index)
    {
        TPolicyRegistryPublicationSnapshot snapshot{};
        snapshot.snapshot_id = id;
        snapshot.snapshot_sequence = sequence;
        for (const auto& record : index.records)
        {
            if (!record.IsValid()) continue;
            const auto state = record.publication_record.publication_state;
            if (policy_type_system::IsAssignmentVisible(state) ||
                record.publication_record.visibility == policy_type_system::TPolicyRegistryVisibility::retired_visible ||
                record.publication_record.visibility == policy_type_system::TPolicyRegistryVisibility::forbidden_visible)
            {
                snapshot.visible_records.push_back(record);
            }
            if (state == policy_type_system::TPolicyPublicationState::published) ++snapshot.published_count;
            if (state == policy_type_system::TPolicyPublicationState::deprecated) ++snapshot.deprecated_count;
            if (state == policy_type_system::TPolicyPublicationState::retired) ++snapshot.retired_count;
            if (state == policy_type_system::TPolicyPublicationState::rollback_candidate) ++snapshot.rollback_candidate_count;
            if (state == policy_type_system::TPolicyPublicationState::forbidden) ++snapshot.forbidden_count;
        }
        return snapshot;
    }

    [[nodiscard]] bool HasProductionVisibleRecord() const noexcept
    {
        for (const auto& record : visible_records)
        {
            if (record.IsProductionVisible()) return true;
        }
        return false;
    }
};

} // namespace assembler::ecosystem_governance::policy_registry
