#pragma once

#include <string_view>

/**
 * @file TRegistryEntryStatus.hpp
 * @brief Optional registry entry lifecycle status.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - small status vocabulary for optional registry entries;
 * - diagnostic lifecycle state without owning registered object lifecycle;
 * - stable string conversion for reports and snapshots.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - enum class `TRegistryEntryStatus`;
 * - terminal/visibility helpers;
 * - string conversion.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - mandatory runtime ownership;
 * - service locator behavior;
 * - dependency injection container behavior;
 * - scheduler, broker, queue, worker, thread, async, or event-loop behavior;
 * - endpoint-domain internals;
 * - concrete adapter/port invocation;
 * - persistence, database, telemetry, ABI, or downstream registry behavior;
 * - mutation of endpoint-owned resources;
 * - replacement of Channel, Binding, Session, Protocol, or Bridge semantics.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W11 may depend on W01-W10 public Communication Context surfaces.
 * It must remain optional and must not be required by W14 concrete bindings
 * or W15 first integration skeleton.
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
