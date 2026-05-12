#pragma once

#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyScope.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryLookupKey.hpp
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
 *   TPolicyRegistryLookupKey describes how a caller asks the registry to find a
 *   policy. It may identify an exact policy id, or a family/version/scope. The
 *   key is descriptive and query-facing; it is not a policy object and not a
 *   registry entry.
 */
struct TPolicyRegistryLookupKey final
{
    policy_type_system::TPolicyId policy_id{};
    policy_type_system::TPolicyFamilyId family_id{};
    policy_type_system::TPolicyVersion version{};
    policy_type_system::TPolicyScope scope{policy_type_system::TPolicyScope::unspecified};

    constexpr TPolicyRegistryLookupKey() noexcept = default;

    [[nodiscard]] static constexpr TPolicyRegistryLookupKey ByPolicyId(policy_type_system::TPolicyId id) noexcept
    {
        TPolicyRegistryLookupKey key{};
        key.policy_id = id;
        return key;
    }

    [[nodiscard]] static constexpr TPolicyRegistryLookupKey ByFamilyVersion(
        policy_type_system::TPolicyFamilyId family,
        policy_type_system::TPolicyVersion ver,
        policy_type_system::TPolicyScope sc = policy_type_system::TPolicyScope::unspecified) noexcept
    {
        TPolicyRegistryLookupKey key{};
        key.family_id = family;
        key.version = ver;
        key.scope = sc;
        return key;
    }

    [[nodiscard]] constexpr bool HasPolicyId() const noexcept { return policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasFamilyVersion() const noexcept { return family_id.IsValid() && !version.IsZero(); }
    [[nodiscard]] constexpr bool IsSpecified() const noexcept { return HasPolicyId() || HasFamilyVersion(); }
};

} // namespace assembler::ecosystem_governance::policy_registry
