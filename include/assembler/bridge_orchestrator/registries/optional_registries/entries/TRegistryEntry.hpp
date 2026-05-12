#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/registries/optional_registries/status/TRegistryEntryStatus.hpp"

/**
 * @file TRegistryEntry.hpp
 * @brief Optional registry entry wrapper for ASCC model values.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - generic value wrapper for registry-owned references to model objects;
 * - registry-local entry metadata without taking lifecycle authority over the value;
 * - stable entry status and label fields for diagnostics.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - templated entry wrapper;
 * - validity, usability, activation, suspension, retirement helpers;
 * - factory helpers for accepted and rejected entries.
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
    template <typename TId, typename TValue>
    struct TRegistryEntry final
    {
        TId id{};
        TValue value{};
        TRegistryEntryStatus status{TRegistryEntryStatus::unknown};
        std::uint64_t ordinal{0u};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view label{};

        [[nodiscard]] constexpr bool has_valid_id() const noexcept
        {
            return id.is_valid();
        }

        [[nodiscard]] constexpr bool has_valid_value() const noexcept
        {
            return value.is_valid();
        }

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return has_valid_id()
                && has_valid_value()
                && status != TRegistryEntryStatus::unknown;
        }

        [[nodiscard]] constexpr bool is_usable() const noexcept
        {
            return is_valid() && is_usable_registry_entry_status(status);
        }

        constexpr bool activate() noexcept
        {
            if (!is_valid() || is_terminal_registry_entry_status(status))
            {
                return false;
            }

            status = TRegistryEntryStatus::active;
            return true;
        }

        constexpr bool suspend() noexcept
        {
            if (!is_valid() || is_terminal_registry_entry_status(status))
            {
                return false;
            }

            status = TRegistryEntryStatus::suspended;
            return true;
        }

        constexpr bool retire() noexcept
        {
            if (!is_valid())
            {
                return false;
            }

            status = TRegistryEntryStatus::retired;
            return true;
        }

        [[nodiscard]] static constexpr TRegistryEntry make(
            TId entry_id,
            TValue entry_value,
            std::uint64_t entry_ordinal,
            std::string_view entry_label = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            if (!entry_id.is_valid() || !entry_value.is_valid())
            {
                return TRegistryEntry{
                    entry_id,
                    entry_value,
                    TRegistryEntryStatus::rejected,
                    entry_ordinal,
                    token,
                    entry_label
                };
            }

            return TRegistryEntry{
                entry_id,
                entry_value,
                TRegistryEntryStatus::registered,
                entry_ordinal,
                token,
                entry_label
            };
        }
    };
}
