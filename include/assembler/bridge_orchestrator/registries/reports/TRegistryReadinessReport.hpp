#pragma once

#include <string_view>

#include "assembler/communication_context/registries/snapshots/TRegistrySnapshot.hpp"

/**
 * @file TRegistryReadinessReport.hpp
 * @brief Readiness report for one ASCC bounded registry.
 *
 * @section purpose Purpose
 * Converts registry snapshot evidence into a bounded readiness report usable by
 * managerial facade and component admission.
 *
 * This report is not a registry, not a service locator, and not a persistence
 * engine.
 */

namespace assembler::communication_context
{
    struct TRegistryReadinessReport final
    {
        TRegistrySnapshot snapshot{};
        bool registry_valid{false};
        bool has_required_entries{false};
        bool capacity_available{false};
        std::string_view report_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return snapshot.is_valid();
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && registry_valid
                && has_required_entries;
        }

        [[nodiscard]] static constexpr TRegistryReadinessReport from_snapshot(
            TRegistrySnapshot registry_snapshot,
            bool valid_registry,
            bool required_entries_present,
            std::string_view note = {}) noexcept
        {
            return TRegistryReadinessReport{
                registry_snapshot,
                valid_registry,
                required_entries_present,
                registry_snapshot.count < registry_snapshot.capacity,
                note
            };
        }
    };
}
