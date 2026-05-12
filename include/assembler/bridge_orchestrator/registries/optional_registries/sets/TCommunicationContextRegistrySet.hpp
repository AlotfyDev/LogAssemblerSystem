#pragma once

#include "assembler/communication_context/registries/optional_registries/typed/TBindingRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBridgeProtocolRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TBridgeRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TChannelRegistry.hpp"
#include "assembler/communication_context/registries/optional_registries/typed/TSessionRegistry.hpp"

/**
 * @file TCommunicationContextRegistrySet.hpp
 * @brief Optional grouped registry set for Communication Context model declarations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - grouped optional registries for channels, bindings, sessions, protocols,
 *   and bridges;
 * - diagnostic registry snapshots without mandating registry use;
 * - no global singleton or service-locator behavior.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - five typed registries as public fields;
 * - validity helper;
 * - total count helper;
 * - default factory.
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
