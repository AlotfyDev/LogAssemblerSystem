#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "assembler/ecosystem_governance/policy_registry/TPolicyRegistryEntryDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/source_publication/TPolicyPublicationRecord.hpp"
#include "assembler/ecosystem_governance/policy_type_system/source_publication/TPolicyVersionLineage.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryVersionIndex.hpp
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
 *   TPolicyRegistryVersionIndex defines the first in-memory version index over registry descriptors, publication records, and version lineage. It supports exact version lookup, latest published lookup, and rollback-candidate discovery. It is not registry persistence, not source ingestion, not assignment, and not runtime rollback execution.
 */

struct TPolicyRegistryVersionIndexRecord final
{
    TPolicyRegistryEntryDescriptor registry_descriptor{};
    policy_type_system::TPolicyPublicationRecord publication_record{};
    policy_type_system::TPolicyVersionLineage lineage{};
    bool rollback_candidate{false};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return registry_descriptor.IsStructurallyUsable() &&
               publication_record.IsValidRecord() &&
               registry_descriptor.policy_id == publication_record.policy_id &&
               registry_descriptor.version == publication_record.policy_version;
    }

    [[nodiscard]] bool IsAssignmentVisible() const noexcept
    {
        return IsValid() &&
               policy_type_system::IsAssignmentVisible(publication_record.publication_state);
    }

    [[nodiscard]] bool IsProductionVisible() const noexcept
    {
        return IsValid() && publication_record.IsProductionVisible();
    }
};

struct TPolicyRegistryVersionIndex final
{
    std::vector<TPolicyRegistryVersionIndexRecord> records{};

    [[nodiscard]] std::size_t Count() const noexcept { return records.size(); }
    [[nodiscard]] bool Empty() const noexcept { return records.empty(); }

    void Add(TPolicyRegistryVersionIndexRecord record)
    {
        if (record.IsValid()) records.push_back(std::move(record));
    }

    [[nodiscard]] const TPolicyRegistryVersionIndexRecord* FindExact(
        policy_type_system::TPolicyId policy_id,
        policy_type_system::TPolicyVersion version) const noexcept
    {
        for (const auto& record : records)
        {
            if (record.registry_descriptor.policy_id == policy_id &&
                record.registry_descriptor.version == version)
            {
                return &record;
            }
        }
        return nullptr;
    }

    [[nodiscard]] const TPolicyRegistryVersionIndexRecord* FindLatestPublishedForFamily(
        policy_type_system::TPolicyFamilyId family_id,
        policy_type_system::TPolicyScope scope = policy_type_system::TPolicyScope::unspecified) const noexcept
    {
        const TPolicyRegistryVersionIndexRecord* best = nullptr;
        for (const auto& record : records)
        {
            const bool scope_matches = scope == policy_type_system::TPolicyScope::unspecified ||
                                       record.registry_descriptor.scope == scope;
            if (record.registry_descriptor.family_id == family_id &&
                scope_matches &&
                policy_type_system::IsPublished(record.publication_record.publication_state))
            {
                if (best == nullptr || best->registry_descriptor.version < record.registry_descriptor.version)
                {
                    best = &record;
                }
            }
        }
        return best;
    }

    [[nodiscard]] std::vector<TPolicyRegistryVersionIndexRecord> RollbackCandidatesForFamily(
        policy_type_system::TPolicyFamilyId family_id) const
    {
        std::vector<TPolicyRegistryVersionIndexRecord> result{};
        for (const auto& record : records)
        {
            if (record.registry_descriptor.family_id == family_id &&
                (record.rollback_candidate ||
                 record.publication_record.publication_state == policy_type_system::TPolicyPublicationState::rollback_candidate ||
                 record.lineage.IsRollbackRelated()))
            {
                result.push_back(record);
            }
        }
        return result;
    }
};

} // namespace assembler::ecosystem_governance::policy_registry
