#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryEntryId.hpp
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
 *   TPolicyRegistryEntryId is the primitive identity token for a registry entry.
 *   It identifies the catalog record, not the policy object itself. The policy
 *   object remains identified by TPolicyId from the policy type system.
 */
struct TPolicyRegistryEntryId final
{
    using value_type = std::uint64_t;
    value_type value{0};

    constexpr TPolicyRegistryEntryId() noexcept = default;
    explicit constexpr TPolicyRegistryEntryId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyRegistryEntryId Invalid() noexcept { return TPolicyRegistryEntryId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyRegistryEntryId lhs, TPolicyRegistryEntryId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyRegistryEntryId lhs, TPolicyRegistryEntryId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyRegistryEntryId lhs, TPolicyRegistryEntryId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_registry
