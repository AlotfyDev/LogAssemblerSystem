#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/registries/status/TRegistryEntryStatus.hpp"

/**
 * @file TRegistryEntry.hpp
 * @brief Core registry entry wrapper for ASCC model values.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This file is the canonical core-registry home for the entry wrapper that
 * originally lived under `optional_registries/entries`.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * Registry entries are catalog/evidence wrappers.  They must not own endpoint
 * resources, invoke endpoints, schedule work, implement service-location, or
 * replace Channel, Binding, Session, Protocol, or Bridge semantics.
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
