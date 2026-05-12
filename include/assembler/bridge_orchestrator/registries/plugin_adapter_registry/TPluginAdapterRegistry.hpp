#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/obligations/plugin_adapters/descriptors/TPluginAdapterDescriptor.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/ids/TPluginAdapterId.hpp"
#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"

/**
 * @file TPluginAdapterRegistry.hpp
 * @brief Core bounded registry for ASCC plugin-adapter descriptors.
 *
 * @section ascc_comp_w01_reg05 REG-05 Identity Normalization
 * This registry now uses `TPluginAdapterId` and `TBoundedRegistry`, preserving
 * a single registry primitive across ASCC. It catalogs bridge-visible
 * plugin-adapter descriptors; views remain projections derived from those
 * descriptors.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry must not store or own concrete endpoint adapter instances. It
 * must not become a service locator, broker, scheduler, dependency-injection
 * container, endpoint invoker, pipeline composer, or owner of endpoint
 * lifecycle.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TPluginAdapterRegistry final
    {
        TBoundedRegistry<TPluginAdapterId, TPluginAdapterDescriptor, Capacity> registry{
            TBoundedRegistry<TPluginAdapterId, TPluginAdapterDescriptor, Capacity>::make(
                "plugin_adapter_registry")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return registry.is_valid();
        }

        constexpr bool register_adapter(TPluginAdapterDescriptor adapter) noexcept
        {
            return registry.register_value(
                adapter.adapter_id,
                adapter,
                adapter.descriptor_name);
        }

        [[nodiscard]] constexpr const TRegistryEntry<TPluginAdapterId, TPluginAdapterDescriptor>* find(
            TPluginAdapterId id) const noexcept
        {
            return registry.find(id);
        }

        [[nodiscard]] constexpr bool contains(TPluginAdapterId id) const noexcept
        {
            return registry.contains(id);
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return registry.snapshot();
        }

        [[nodiscard]] static constexpr TPluginAdapterRegistry make(
            std::string_view name = "plugin_adapter_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TPluginAdapterRegistry{
                TBoundedRegistry<TPluginAdapterId, TPluginAdapterDescriptor, Capacity>::make(
                    name,
                    token)
            };
        }
    };
}
