#pragma once

#include "TPolicyRegistrySnapshot.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistryView.hpp
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
 *   TPolicyRegistryView is the public read-only projection over registry state.
 *   It intentionally exposes summary information only. It does not provide
 *   mutation, persistence, service-location, or target access.
 */
struct TPolicyRegistryView final
{
    TPolicyRegistrySnapshot snapshot{};

    [[nodiscard]] constexpr bool Empty() const noexcept { return snapshot.Empty(); }
    [[nodiscard]] constexpr bool Full() const noexcept { return snapshot.Full(); }
    [[nodiscard]] constexpr std::size_t Capacity() const noexcept { return snapshot.capacity; }
    [[nodiscard]] constexpr std::size_t Size() const noexcept { return snapshot.occupied_entries; }
};

} // namespace assembler::ecosystem_governance::policy_registry
