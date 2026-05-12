#pragma once

#include "assembler/communication_context/bridge_core/TBridge.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/registries/optional_registries/base/TBoundedRegistry.hpp"

/**
 * @file TBridgeRegistry.hpp
 * @brief Optional bounded registry for bridge declarations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional registry layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - typed registry over `TBridgeId` and `TBridge`;
 * - bridge declaration visibility without executing registered bridges;
 * - no scheduler, orchestrator replacement, or lifecycle authority.
 *
 * @section ascc_current_wave Current W11 Implementation Scope
 * This W11 version intentionally implements only lightweight, header-only,
 * bounded registries for model objects already defined by W04-W10.
 *
 * - capacity-templated bridge registry;
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
