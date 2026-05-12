#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/registries/entries/TRegistryEntry.hpp"
#include "assembler/communication_context/registries/lookups/TRegistryLookupResult.hpp"
#include "assembler/communication_context/registries/snapshots/TRegistrySnapshot.hpp"

/**
 * @file TBoundedRegistry.hpp
 * @brief Core bounded registry container for ASCC model entries.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This file is the canonical core-registry home for the bounded registry
 * primitive that originally lived under `optional_registries/base`.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry is a bounded catalog/evidence container.  It must not become a
 * service locator, broker, scheduler, dependency injection container, endpoint
 * invoker, persistence engine, telemetry exporter, or pipeline composer.
 */

namespace assembler::communication_context
{
    template <typename TId, typename TValue, std::size_t Capacity>
    struct TBoundedRegistry final
    {
        using Entry = TRegistryEntry<TId, TValue>;

        std::array<Entry, Capacity> entries{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view registry_name{"bounded_registry"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !registry_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return count == 0u;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr const Entry* find(TId id) const noexcept
        {
            if (!id.is_valid())
            {
                return nullptr;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (entries[index].id == id)
                {
                    return &entries[index];
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr Entry* find_mutable(TId id) noexcept
        {
            if (!id.is_valid())
            {
                return nullptr;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (entries[index].id == id)
                {
                    return &entries[index];
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr bool contains(TId id) const noexcept
        {
            return find(id) != nullptr;
        }

        [[nodiscard]] constexpr TRegistryLookupResult lookup_result(TId id) const noexcept
        {
            if (!id.is_valid())
            {
                return TRegistryLookupResult::reject(
                    registry_name,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "registry lookup id is invalid"),
                    correlation);
            }

            if (contains(id))
            {
                return TRegistryLookupResult::found_result(registry_name, correlation);
            }

            return TRegistryLookupResult::missing(registry_name, correlation);
        }

        constexpr bool register_value(
            TId id,
            TValue value,
            std::string_view label = {}) noexcept
        {
            if (!is_valid()
                || full()
                || !id.is_valid()
                || !value.is_valid()
                || contains(id))
            {
                ++rejected_insertions;
                return false;
            }

            entries[count] = Entry::make(
                id,
                value,
                count + 1u,
                label,
                correlation);
            ++count;
            return true;
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return TRegistrySnapshot::make(
                registry_name,
                count,
                Capacity,
                rejected_insertions,
                correlation);
        }

        [[nodiscard]] static constexpr TBoundedRegistry make(
            std::string_view name,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBoundedRegistry{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
