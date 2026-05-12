#pragma once

#include "TPolicyRegistryEntry.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyStatus.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryLookupResult.hpp
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
 *   TPolicyRegistryLookupResult reports the outcome of a registry lookup. It
 *   carries only a descriptor copy and primitive issue/status information; it
 *   does not expose registry storage or mutate the registry.
 */
struct TPolicyRegistryLookupResult final
{
    policy_type_system::TPolicyStatus status{policy_type_system::TPolicyStatus::unknown};
    policy_type_system::TPolicyIssue issue{};
    TPolicyRegistryEntryDescriptor descriptor{};

    [[nodiscard]] static constexpr TPolicyRegistryLookupResult Found(const TPolicyRegistryEntry& entry) noexcept
    {
        TPolicyRegistryLookupResult result{};
        result.status = policy_type_system::TPolicyStatus::valid;
        result.issue = policy_type_system::TPolicyIssue{result.status, 0u};
        result.descriptor = entry.descriptor;
        return result;
    }

    [[nodiscard]] static constexpr TPolicyRegistryLookupResult NotFound() noexcept
    {
        TPolicyRegistryLookupResult result{};
        result.status = policy_type_system::TPolicyStatus::incomplete;
        result.issue = policy_type_system::TPolicyIssue{result.status, 1u};
        return result;
    }

    [[nodiscard]] constexpr bool IsFound() const noexcept { return status == policy_type_system::TPolicyStatus::valid; }
};

} // namespace assembler::ecosystem_governance::policy_registry
