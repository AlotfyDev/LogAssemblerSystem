#pragma once

#include "TPolicyRegistryEntryDescriptor.hpp"
#include "TPolicyRegistryLookupKey.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment/TPolicyAssignmentId.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryEntry.hpp
 * Wave: EG-POL-W11_Policy_Registry_Basics
 * Domain: ecosystem_governance / policy_registry
 *
 * Architectural boundary:
 *   This file belongs to the Policy Registry Basics wave. W11 introduces the
 *   smallest in-memory/catalog-facing registry vocabulary needed after W09
 *   TPolicy aggregate and W10 assignment basics. The registry layer indexes and
 *   describes policy objects; it does not execute policies, does not realize
 *   policies, does not own target components, does not persist to a database,
 *   does not become a service locator, and does not communicate with other
 *   domains.
 *
 * Relationship to prior waves:
 *   - W01 provides policy identity, family, version, source, scope, status,
 *     issue, and primitive result vocabulary.
 *   - W09 provides TPolicy, TPolicyView, and TPolicySnapshot that may be used
 *     to create registry descriptors.
 *   - W10 provides assignment identity and assignment view; W11 may reference
 *     assignments as descriptors, but it does not execute assignment workflows.
 *
 * Relationship to future waves:
 *   A future ecosystem governance registry may add persistence, versioned
 *   catalogs, policy-source ingestion, policy bundle loading, or governance
 *   review workflows. Those are intentionally outside this W11 foundation.
 *
 * Current implementation posture:
 *   W11 remains header-only-first and C++17-compatible. Types are compact value
 *   carriers or bounded in-memory containers suitable for smoke tests and later
 *   implementation derivation. The opening documentation describes the complete
 *   intended responsibility even when the code is only a foundational block.

 *
 * File responsibility:
 *   TPolicyRegistryEntry is a bounded in-memory catalog record for a policy.
 *   It stores the descriptor and optional assignment identity reference. It does
 *   not store the full policy aggregate, does not persist anything, and does not
 *   own the assigned target.
 */
struct TPolicyRegistryEntry final
{
    TPolicyRegistryEntryDescriptor descriptor{};
    policy_type_system::TPolicyAssignmentId assignment_id{};

    constexpr TPolicyRegistryEntry() noexcept = default;
    constexpr explicit TPolicyRegistryEntry(TPolicyRegistryEntryDescriptor d) noexcept : descriptor(d) {}

    [[nodiscard]] constexpr bool IsOccupied() const noexcept { return descriptor.entry_id.IsValid(); }
    [[nodiscard]] constexpr bool IsLookupVisible() const noexcept { return policy_registry::IsLookupVisible(descriptor.registry_status); }

    [[nodiscard]] constexpr bool Matches(const TPolicyRegistryLookupKey& key) const noexcept
    {
        if (!IsLookupVisible() || !key.IsSpecified()) { return false; }
        if (key.HasPolicyId()) { return descriptor.policy_id == key.policy_id; }
        const bool family_match = descriptor.family_id == key.family_id;
        const bool version_match = descriptor.version == key.version;
        const bool scope_match = key.scope == policy_type_system::TPolicyScope::unspecified || descriptor.scope == key.scope;
        return family_match && version_match && scope_match;
    }
};

} // namespace assembler::ecosystem_governance::policy_registry
