#pragma once

#include <cstddef>
#include "TPolicyRegistryEntryId.hpp"
#include "TPolicyRegistryEntryStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyScope.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicySnapshot.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicyView.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryEntryDescriptor.hpp
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
 *   TPolicyRegistryEntryDescriptor is the registry-facing summary of a policy.
 *   It records entry identity, policy identity, family, version, scope, status,
 *   and compact structural metrics. It is intentionally smaller than TPolicy
 *   and does not expose mutable policy internals.
 */
struct TPolicyRegistryEntryDescriptor final
{
    TPolicyRegistryEntryId entry_id{};
    policy_type_system::TPolicyId policy_id{};
    policy_type_system::TPolicyFamilyId family_id{};
    policy_type_system::TPolicyVersion version{};
    policy_type_system::TPolicyScope scope{policy_type_system::TPolicyScope::unspecified};
    TPolicyRegistryEntryStatus registry_status{TPolicyRegistryEntryStatus::unknown};
    std::size_t clause_count{0};
    std::size_t graph_node_count{0};
    std::size_t graph_edge_count{0};
    bool structurally_complete{false};

    constexpr TPolicyRegistryEntryDescriptor() noexcept = default;

    [[nodiscard]] static constexpr TPolicyRegistryEntryDescriptor FromSnapshot(
        TPolicyRegistryEntryId entry,
        const policy_type_system::TPolicySnapshot& snapshot,
        TPolicyRegistryEntryStatus status = TPolicyRegistryEntryStatus::registered) noexcept
    {
        TPolicyRegistryEntryDescriptor descriptor{};
        descriptor.entry_id = entry;
        descriptor.policy_id = snapshot.policy_id;
        descriptor.family_id = snapshot.family_id;
        descriptor.version = snapshot.version;
        descriptor.scope = snapshot.scope;
        descriptor.registry_status = status;
        descriptor.clause_count = snapshot.clause_count;
        descriptor.graph_node_count = snapshot.graph_node_count;
        descriptor.graph_edge_count = snapshot.graph_edge_count;
        descriptor.structurally_complete = snapshot.structurally_complete;
        return descriptor;
    }

    [[nodiscard]] static constexpr TPolicyRegistryEntryDescriptor FromView(
        TPolicyRegistryEntryId entry,
        const policy_type_system::TPolicyView& view,
        TPolicyRegistryEntryStatus status = TPolicyRegistryEntryStatus::registered) noexcept
    {
        return FromSnapshot(entry, view.snapshot, status);
    }

    [[nodiscard]] constexpr bool HasEntryIdentity() const noexcept { return entry_id.IsValid(); }
    [[nodiscard]] constexpr bool HasPolicyIdentity() const noexcept { return policy_id.IsValid() && family_id.IsValid() && !version.IsZero(); }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept
    {
        return HasEntryIdentity() && HasPolicyIdentity() && IsRegistered(registry_status);
    }
};

} // namespace assembler::ecosystem_governance::policy_registry
