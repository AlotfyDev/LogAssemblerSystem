#pragma once

#include <cstdint>

#include "assembler/ecosystem_governance/policy_registry/TPolicyRegistryLookupResult.hpp"
#include "assembler/ecosystem_governance/policy_registry/versioning/TPolicyRegistryVersionIndex.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryVersionedLookup.hpp
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
 *   TPolicyRegistryVersionedLookup defines version-aware registry lookup helpers and lookup result vocabulary. It can report exact-version and latest-published discovery without becoming a registry storage engine, service locator, assignment activator, or realizer.
 */

enum class TPolicyRegistryVersionedLookupStatus : std::uint8_t
{
    unknown = 0,
    found_exact = 1,
    found_latest_published = 2,
    found_rollback_candidate = 3,
    not_found = 4,
    not_visible = 5,
    invalid_query = 6
};

struct TPolicyRegistryVersionedLookupResult final
{
    TPolicyRegistryVersionedLookupStatus status{TPolicyRegistryVersionedLookupStatus::unknown};
    TPolicyRegistryEntryDescriptor descriptor{};
    policy_type_system::TPolicyPublicationState publication_state{policy_type_system::TPolicyPublicationState::unknown};
    bool rollback_candidate{false};

    [[nodiscard]] constexpr bool Found() const noexcept
    {
        return status == TPolicyRegistryVersionedLookupStatus::found_exact ||
               status == TPolicyRegistryVersionedLookupStatus::found_latest_published ||
               status == TPolicyRegistryVersionedLookupStatus::found_rollback_candidate;
    }

    [[nodiscard]] constexpr bool AssignmentEligible() const noexcept
    {
        return Found() && policy_type_system::IsAssignmentVisible(publication_state);
    }
};

struct TPolicyRegistryVersionedLookup final
{
    [[nodiscard]] static TPolicyRegistryVersionedLookupResult Exact(
        const TPolicyRegistryVersionIndex& index,
        policy_type_system::TPolicyId policy_id,
        policy_type_system::TPolicyVersion version) noexcept
    {
        TPolicyRegistryVersionedLookupResult result{};
        if (!policy_id.IsValid() || version.IsZero())
        {
            result.status = TPolicyRegistryVersionedLookupStatus::invalid_query;
            return result;
        }
        const auto* record = index.FindExact(policy_id, version);
        if (record == nullptr)
        {
            result.status = TPolicyRegistryVersionedLookupStatus::not_found;
            return result;
        }
        result.status = record->IsAssignmentVisible()
            ? TPolicyRegistryVersionedLookupStatus::found_exact
            : TPolicyRegistryVersionedLookupStatus::not_visible;
        result.descriptor = record->registry_descriptor;
        result.publication_state = record->publication_record.publication_state;
        result.rollback_candidate = record->rollback_candidate || record->lineage.IsRollbackRelated();
        return result;
    }

    [[nodiscard]] static TPolicyRegistryVersionedLookupResult LatestPublished(
        const TPolicyRegistryVersionIndex& index,
        policy_type_system::TPolicyFamilyId family_id,
        policy_type_system::TPolicyScope scope = policy_type_system::TPolicyScope::unspecified) noexcept
    {
        TPolicyRegistryVersionedLookupResult result{};
        if (!family_id.IsValid())
        {
            result.status = TPolicyRegistryVersionedLookupStatus::invalid_query;
            return result;
        }
        const auto* record = index.FindLatestPublishedForFamily(family_id, scope);
        if (record == nullptr)
        {
            result.status = TPolicyRegistryVersionedLookupStatus::not_found;
            return result;
        }
        result.status = TPolicyRegistryVersionedLookupStatus::found_latest_published;
        result.descriptor = record->registry_descriptor;
        result.publication_state = record->publication_record.publication_state;
        result.rollback_candidate = record->rollback_candidate || record->lineage.IsRollbackRelated();
        return result;
    }
};

} // namespace assembler::ecosystem_governance::policy_registry
