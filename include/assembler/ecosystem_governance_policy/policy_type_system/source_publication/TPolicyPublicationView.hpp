#pragma once

#include <cstddef>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/source_publication/TPolicyPublicationRecord.hpp"
#include "assembler/ecosystem_governance/policy_type_system/source_publication/TPolicyVersionLineage.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyPublicationView.hpp
 * Wave: EG-POL-W16_Policy_Source_And_Publication
 * Domain: ecosystem_governance / policy_type_system / source_publication
 *
 * Architectural boundary:
 *   W16 implements the first policy source and publication vocabulary derived
 *   from EG-POL-ARCH-006_Policy_Source_Publication_And_Registry_Versioning.
 *   It follows W12 Policy Family And Scope, W13 Target Capability Contracts,
 *   W14 Family Target Compatibility Matrix, and W15 Assignment Lifecycle And
 *   Conflict. The wave is descriptive and non-executing: it classifies policy
 *   source descriptors, publication states, publication records, version
 *   lineage, and publication views without publishing to a real registry,
 *   assigning policies, realizing policies, or invoking targets.
 *
 * Relationship to prior waves:
 *   - W01 supplies TPolicyId, TPolicyVersion, and primitive source vocabulary.
 *   - W09 supplies TPolicy as semantic aggregate, not executor.
 *   - W10 supplies non-executing assignment basics; W16 does not activate
 *     assignments.
 *   - W11 supplies registry basics; W16 prepares publication/registry-version
 *     semantics but does not become registry persistence.
 *   - W12, W13, W14, and W15 supply family/scope, target capability,
 *     compatibility, and assignment lifecycle foundations that later workflows
 *     will consume.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-006 states that source is not validity, ingestion is not
 *   publication, publication is not assignment, assignment is not realization,
 *   registry is not a storage engine, and rollback readiness is not rollback
 *   execution. This file preserves those non-collapse rules.
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
 *   TPolicyPublicationView is a read-only aggregate view over publication records and version lineage records. It supports governance review and smoke tests without owning registry persistence or executing policy behavior.
 */

struct TPolicyPublicationView final
{
    std::vector<TPolicyPublicationRecord> publication_records{};
    std::vector<TPolicyVersionLineage> version_lineages{};

    [[nodiscard]] std::size_t PublicationRecordCount() const noexcept
    {
        return publication_records.size();
    }

    [[nodiscard]] std::size_t LineageCount() const noexcept
    {
        return version_lineages.size();
    }

    [[nodiscard]] bool HasAnyPublishedRecord() const noexcept
    {
        for (const auto& record : publication_records)
        {
            if (record.IsPublishedRecord())
            {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool HasAnyRollbackLineage() const noexcept
    {
        for (const auto& lineage : version_lineages)
        {
            if (lineage.IsRollbackRelated())
            {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool AllRecordsValid() const noexcept
    {
        for (const auto& record : publication_records)
        {
            if (!record.IsValidRecord())
            {
                return false;
            }
        }
        for (const auto& lineage : version_lineages)
        {
            if (!lineage.IsValidLineage())
            {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr bool IsViewOnly() const noexcept { return true; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
