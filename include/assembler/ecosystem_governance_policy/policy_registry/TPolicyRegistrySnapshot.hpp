#pragma once

#include <cstddef>

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistrySnapshot.hpp
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
 *   TPolicyRegistrySnapshot is a copy-safe summary of bounded registry state.
 *   It reports capacity, occupied entry count, visible entry count, and rejected
 *   entry count without exposing registry storage.
 */
struct TPolicyRegistrySnapshot final
{
    std::size_t capacity{0};
    std::size_t occupied_entries{0};
    std::size_t visible_entries{0};
    std::size_t rejected_entries{0};

    [[nodiscard]] constexpr bool Empty() const noexcept { return occupied_entries == 0; }
    [[nodiscard]] constexpr bool Full() const noexcept { return capacity != 0 && occupied_entries >= capacity; }
};

} // namespace assembler::ecosystem_governance::policy_registry
