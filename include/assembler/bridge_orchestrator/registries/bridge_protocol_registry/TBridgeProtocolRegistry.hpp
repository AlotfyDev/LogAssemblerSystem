#pragma once

#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"
#include "assembler/communication_context/protocols/common/TBridgeProtocol.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"

/**
 * @file TBridgeProtocolRegistry.hpp
 * @brief Core bounded registry for ASCC bridge protocol declarations.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This is the canonical registry path for `TBridgeProtocolRegistry`.  The
 * previous implementation lived under `registries/optional_registries/typed`;
 * that path is now compatibility-only.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry catalogs protocol model declarations for evidence and lookup.
 * It must not step protocols, run bridge loops, invoke endpoints, schedule
 * runtime work, or act as a service locator.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity, std::size_t PlanCapacity>
    struct TBridgeProtocolRegistry final
    {
        using Protocol = TBridgeProtocol<PlanCapacity>;

        TBoundedRegistry<TBridgeProtocolId, Protocol, Capacity> registry{
            TBoundedRegistry<TBridgeProtocolId, Protocol, Capacity>::make(
                "bridge_protocol_registry")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return registry.is_valid();
        }

        constexpr bool register_protocol(Protocol protocol) noexcept
        {
            return registry.register_value(
                protocol.protocol_id,
                protocol,
                protocol.protocol_name);
        }

        [[nodiscard]] constexpr const TRegistryEntry<TBridgeProtocolId, Protocol>* find(
            TBridgeProtocolId id) const noexcept
        {
            return registry.find(id);
        }

        [[nodiscard]] constexpr bool contains(TBridgeProtocolId id) const noexcept
        {
            return registry.contains(id);
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return registry.snapshot();
        }

        [[nodiscard]] static constexpr TBridgeProtocolRegistry make(
            std::string_view name = "bridge_protocol_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeProtocolRegistry{
                TBoundedRegistry<TBridgeProtocolId, Protocol, Capacity>::make(name, token)
            };
        }
    };
}
