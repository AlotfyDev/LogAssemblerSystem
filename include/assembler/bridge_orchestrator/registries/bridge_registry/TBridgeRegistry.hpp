#pragma once

#include "assembler/communication_context/bridge_core/TBridge.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"

/**
 * @file TBridgeRegistry.hpp
 * @brief Core bounded registry for ASCC bridge model declarations.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This is the canonical registry path for `TBridgeRegistry`.  The previous
 * implementation lived under `registries/optional_registries/typed`; that path
 * is now compatibility-only.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry catalogs bridge model declarations for evidence and lookup. It
 * must not execute registered bridges, schedule runtime work, invoke endpoints,
 * act as a broker, or become a service locator.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity, std::size_t PlanCapacity>
    struct TBridgeRegistry final
    {
        using Bridge = TBridge<PlanCapacity>;

        TBoundedRegistry<TBridgeId, Bridge, Capacity> registry{
            TBoundedRegistry<TBridgeId, Bridge, Capacity>::make("bridge_registry")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return registry.is_valid();
        }

        constexpr bool register_bridge(Bridge bridge) noexcept
        {
            return registry.register_value(
                bridge.bridge_id,
                bridge,
                bridge.bridge_name);
        }

        [[nodiscard]] constexpr const TRegistryEntry<TBridgeId, Bridge>* find(
            TBridgeId id) const noexcept
        {
            return registry.find(id);
        }

        [[nodiscard]] constexpr bool contains(TBridgeId id) const noexcept
        {
            return registry.contains(id);
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return registry.snapshot();
        }

        [[nodiscard]] static constexpr TBridgeRegistry make(
            std::string_view name = "bridge_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeRegistry{
                TBoundedRegistry<TBridgeId, Bridge, Capacity>::make(name, token)
            };
        }
    };
}
