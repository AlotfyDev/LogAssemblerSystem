#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/obligations/ports/descriptors/TPortDescriptor.hpp"
#include "assembler/communication_context/obligations/ports/ids/TPortId.hpp"
#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"

/**
 * @file TPortRegistry.hpp
 * @brief Core bounded registry for ASCC port descriptors.
 *
 * @section ascc_comp_w01_reg05 REG-05 Identity Normalization
 * This registry now uses `TPortId` and `TBoundedRegistry`, preserving a single
 * registry primitive across ASCC. It catalogs bridge-visible port descriptors;
 * views remain projections derived from those descriptors.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry must not store or own concrete endpoint port instances. It
 * must not become a service locator, broker, scheduler, dependency-injection
 * container, endpoint invoker, pipeline composer, or owner of endpoint
 * lifecycle.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TPortRegistry final
    {
        TBoundedRegistry<TPortId, TPortDescriptor, Capacity> registry{
            TBoundedRegistry<TPortId, TPortDescriptor, Capacity>::make("port_registry")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return registry.is_valid();
        }

        constexpr bool register_port(TPortDescriptor port) noexcept
        {
            return registry.register_value(
                port.port_id,
                port,
                port.descriptor_name);
        }

        [[nodiscard]] constexpr const TRegistryEntry<TPortId, TPortDescriptor>* find(
            TPortId id) const noexcept
        {
            return registry.find(id);
        }

        [[nodiscard]] constexpr bool contains(TPortId id) const noexcept
        {
            return registry.contains(id);
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return registry.snapshot();
        }

        [[nodiscard]] static constexpr TPortRegistry make(
            std::string_view name = "port_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TPortRegistry{
                TBoundedRegistry<TPortId, TPortDescriptor, Capacity>::make(
                    name,
                    token)
            };
        }
    };
}
