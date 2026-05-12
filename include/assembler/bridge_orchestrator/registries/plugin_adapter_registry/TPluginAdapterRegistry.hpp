#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"
#include "assembler/communication_context/registries/snapshots/TRegistrySnapshot.hpp"

/**
 * @file TPluginAdapterRegistry.hpp
 * @brief Core bounded registry for ASCC plugin-adapter views.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This registry stores bridge-visible `TPluginAdapterView` values.  It does
 * not store or own concrete plugin adapter endpoint objects.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry must not become a service locator, broker, scheduler,
 * dependency-injection container, endpoint invoker, pipeline composer, or owner
 * of endpoint lifecycle.  It only catalogs adapter views for ASCC
 * composition/evidence/diagnostic surfaces.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TPluginAdapterRegistry final
    {
        std::array<TPluginAdapterView, Capacity> adapters{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view registry_name{"plugin_adapter_registry"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !registry_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr const TPluginAdapterView* find(
            std::uint64_t adapter_id) const noexcept
        {
            if (adapter_id == 0u)
            {
                return nullptr;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (adapters[index].adapter_id == adapter_id)
                {
                    return &adapters[index];
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr bool contains(std::uint64_t adapter_id) const noexcept
        {
            return find(adapter_id) != nullptr;
        }

        constexpr bool register_adapter(TPluginAdapterView adapter) noexcept
        {
            if (!is_valid()
                || full()
                || !adapter.is_valid()
                || contains(adapter.adapter_id))
            {
                ++rejected_insertions;
                return false;
            }

            adapters[count] = adapter;
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

        [[nodiscard]] static constexpr TPluginAdapterRegistry make(
            std::string_view name = "plugin_adapter_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TPluginAdapterRegistry{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
