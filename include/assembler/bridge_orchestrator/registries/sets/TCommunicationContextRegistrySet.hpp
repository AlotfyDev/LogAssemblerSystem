#pragma once

#include "assembler/communication_context/registries/binding_registry/TBindingRegistry.hpp"
#include "assembler/communication_context/registries/bridge_protocol_registry/TBridgeProtocolRegistry.hpp"
#include "assembler/communication_context/registries/bridge_registry/TBridgeRegistry.hpp"
#include "assembler/communication_context/registries/channel_registry/TChannelRegistry.hpp"
#include "assembler/communication_context/registries/session_registry/TSessionRegistry.hpp"

/**
 * @file TCommunicationContextRegistrySet.hpp
 * @brief Core grouped registry set for ASCC model declarations.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This is the canonical grouped registry-set path.  The previous
 * implementation lived under `registries/optional_registries/sets`; that path
 * is now compatibility-only.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry set groups catalog/evidence registries only.  It must not be a
 * global singleton, service locator, scheduler, broker, endpoint invoker, or
 * pipeline composer.
 */

namespace assembler::communication_context
{
    template <
        std::size_t ChannelCapacity,
        std::size_t BindingCapacity,
        std::size_t SessionCapacity,
        std::size_t ProtocolCapacity,
        std::size_t BridgeCapacity,
        std::size_t PlanCapacity>
    struct TCommunicationContextRegistrySet final
    {
        TChannelRegistry<ChannelCapacity> channels{};
        TBindingRegistry<BindingCapacity> bindings{};
        TSessionRegistry<SessionCapacity> sessions{};
        TBridgeProtocolRegistry<ProtocolCapacity, PlanCapacity> protocols{};
        TBridgeRegistry<BridgeCapacity, PlanCapacity> bridges{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return channels.is_valid()
                && bindings.is_valid()
                && sessions.is_valid()
                && protocols.is_valid()
                && bridges.is_valid();
        }

        [[nodiscard]] constexpr std::size_t total_count() const noexcept
        {
            return channels.count
                + bindings.registry.count
                + sessions.registry.count
                + protocols.registry.count
                + bridges.registry.count;
        }

        [[nodiscard]] static constexpr TCommunicationContextRegistrySet make(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TCommunicationContextRegistrySet{
                TChannelRegistry<ChannelCapacity>::make("channel_registry", token),
                TBindingRegistry<BindingCapacity>::make("binding_registry", token),
                TSessionRegistry<SessionCapacity>::make("session_registry", token),
                TBridgeProtocolRegistry<ProtocolCapacity, PlanCapacity>::make(
                    "bridge_protocol_registry",
                    token),
                TBridgeRegistry<BridgeCapacity, PlanCapacity>::make(
                    "bridge_registry",
                    token)
            };
        }
    };
}
