#pragma once

#include <array>
#include <cstddef>
#include "TPolicyRegistryEntry.hpp"
#include "TPolicyRegistryLookupResult.hpp"
#include "TPolicyRegistryView.hpp"

namespace assembler::ecosystem_governance::policy_registry
{

/*
 * File: TPolicyRegistry.hpp
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
 *   TPolicyRegistry is a small bounded in-memory catalog for policy registry
 *   entries. It can admit descriptors, produce snapshots/views, and perform
 *   basic lookup by policy id or family/version/scope. It deliberately avoids
 *   persistence, source ingestion, DI, service-location, execution, target
 *   invocation, communication binding, and material circulation.
 */
template <std::size_t Capacity>
class TPolicyRegistry final
{
public:
    using entry_type = TPolicyRegistryEntry;

    [[nodiscard]] constexpr std::size_t CapacityValue() const noexcept { return Capacity; }
    [[nodiscard]] constexpr std::size_t Size() const noexcept { return size_; }
    [[nodiscard]] constexpr bool Empty() const noexcept { return size_ == 0; }
    [[nodiscard]] constexpr bool Full() const noexcept { return size_ >= Capacity; }

    [[nodiscard]] constexpr bool Add(const TPolicyRegistryEntry& entry) noexcept
    {
        if (!entry.descriptor.IsStructurallyUsable() || Full() || ContainsEntry(entry.descriptor.entry_id)) {
            return false;
        }
        entries_[size_] = entry;
        ++size_;
        return true;
    }

    [[nodiscard]] constexpr bool AddDescriptor(const TPolicyRegistryEntryDescriptor& descriptor) noexcept
    {
        return Add(TPolicyRegistryEntry{descriptor});
    }

    [[nodiscard]] constexpr TPolicyRegistryLookupResult Lookup(const TPolicyRegistryLookupKey& key) const noexcept
    {
        for (std::size_t i = 0; i < size_; ++i) {
            if (entries_[i].Matches(key)) { return TPolicyRegistryLookupResult::Found(entries_[i]); }
        }
        return TPolicyRegistryLookupResult::NotFound();
    }

    [[nodiscard]] constexpr TPolicyRegistrySnapshot Snapshot() const noexcept
    {
        TPolicyRegistrySnapshot snap{};
        snap.capacity = Capacity;
        snap.occupied_entries = size_;
        for (std::size_t i = 0; i < size_; ++i) {
            if (entries_[i].IsLookupVisible()) { ++snap.visible_entries; }
            if (entries_[i].descriptor.registry_status == TPolicyRegistryEntryStatus::rejected) { ++snap.rejected_entries; }
        }
        return snap;
    }

    [[nodiscard]] constexpr TPolicyRegistryView View() const noexcept
    {
        return TPolicyRegistryView{Snapshot()};
    }

private:
    std::array<entry_type, Capacity> entries_{};
    std::size_t size_{0};

    [[nodiscard]] constexpr bool ContainsEntry(TPolicyRegistryEntryId id) const noexcept
    {
        for (std::size_t i = 0; i < size_; ++i) {
            if (entries_[i].descriptor.entry_id == id) { return true; }
        }
        return false;
    }
};

} // namespace assembler::ecosystem_governance::policy_registry
