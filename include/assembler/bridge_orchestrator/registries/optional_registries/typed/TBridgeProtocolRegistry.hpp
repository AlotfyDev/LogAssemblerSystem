#pragma once

#include "assembler/communication_context/registries/optional_registries/base/TBoundedRegistry.hpp"
#include "assembler/communication_context/protocols/common/TBridgeProtocol.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"

/**
 * @file TBridgeProtocolRegistry.hpp
 * @brief Optional bounded registry for bridge protocol declarations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - typed registry over `TBridgeProtocolId` and `TBridgeProtocol`;
 * - protocol declaration visibility for diagnostics and later registry sets;
 * - no protocol stepping or bridge loop execution.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - capacity-templated protocol registry;
 * - register/find/contains/snapshot helpers.
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
