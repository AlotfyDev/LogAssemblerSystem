#pragma once

#include <string_view>

/**
 * @file TRegistryEntryStatus.hpp
 * @brief Core registry entry lifecycle status for ASCC registries.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This file is the canonical core-registry home for the entry-status
 * vocabulary that originally lived under `optional_registries/status`.
 * Registries are now treated as core ASCC composability/evidence surfaces,
 * not as permanently optional side structures.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement service-location, broker behavior, endpoint
 * invocation, scheduling, pipeline composition, or runtime ownership of
 * endpoint resources.
 */

namespace assembler::communication_context
{
    enum class TRegistryEntryStatus
    {
        unknown,
        registered,
        active,
        suspended,
        retired,
        rejected
    };

    [[nodiscard]] constexpr bool is_usable_registry_entry_status(
        TRegistryEntryStatus status) noexcept
    {
        return status == TRegistryEntryStatus::registered
            || status == TRegistryEntryStatus::active;
    }

    [[nodiscard]] constexpr bool is_terminal_registry_entry_status(
        TRegistryEntryStatus status) noexcept
    {
        return status == TRegistryEntryStatus::retired
            || status == TRegistryEntryStatus::rejected;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TRegistryEntryStatus status) noexcept
    {
        switch (status)
        {
            case TRegistryEntryStatus::unknown: return "unknown";
            case TRegistryEntryStatus::registered: return "registered";
            case TRegistryEntryStatus::active: return "active";
            case TRegistryEntryStatus::suspended: return "suspended";
            case TRegistryEntryStatus::retired: return "retired";
            case TRegistryEntryStatus::rejected: return "rejected";
        }

        return "unknown";
    }
}
