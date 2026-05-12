#pragma once

#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationTraits.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"

/**
 * @file TPluginAdapter.hpp
 * @brief CRTP content-side plugin-adapter obligation facade.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical static abstraction for a content-side plugin-adapter obligation
 *   surface;
 * - future extension point for concrete envelope producers, read-side
 *   producers, telemetry producers, persistence-facing producers, and ABI
 *   producers;
 * - CRTP facade that lets the bridge call content-provider obligations without
 *   depending on endpoint implementation classes directly.
 *
 * @section ascc_current_wave Current W05 Implementation Scope
 * This W05 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It defines bridge-visible host-side port
 * obligations and content-side plugin-adapter obligations without binding
 * execution, session execution, protocol execution, bridge orchestration, or
 * endpoint-domain dependency.
 *
 * - CRTP wrapper over Derived;
 * - primary content-side placement obligation methods;
 * - no binding/session/protocol/bridge orchestration;
 * - no endpoint-domain include or endpoint object ownership.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - session lifecycle or session execution;
 * - concrete adapter-port binding execution;
 * - channel registry or binding registry ownership;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - dynamic polymorphic plugin registry or binding engine.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This obligation foundation header may depend on W01 primitive carriers,
 * W02 protocol-state concepts where needed, W03 participant descriptors, and
 * W04 channel topology where needed. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    template<typename Derived>
    class TPluginAdapter
    {
    public:
        using derived_type = Derived;

        [[nodiscard]] constexpr TPluginAdapterView view() const noexcept
        {
            return derived().view();
        }

        [[nodiscard]] TReadinessView readiness() noexcept
        {
            static_assert(
                TPluginAdapterObligationTraits<Derived>::has_readiness,
                "Derived TPluginAdapter must implement readiness() -> TReadinessView");

            return derived().readiness();
        }

        [[nodiscard]] TPlacementRequest prepare_placement_request() noexcept
        {
            static_assert(
                TPluginAdapterObligationTraits<Derived>::has_prepare_placement_request,
                "Derived TPluginAdapter must implement prepare_placement_request() -> TPlacementRequest");

            return derived().prepare_placement_request();
        }

        [[nodiscard]] TBridgeResult accept_placement_handle(
            const TPlacementHandle& handle) noexcept
        {
            static_assert(
                TPluginAdapterObligationTraits<Derived>::has_accept_placement_handle,
                "Derived TPluginAdapter must implement accept_placement_handle(const TPlacementHandle&) -> TBridgeResult");

            return derived().accept_placement_handle(handle);
        }

        [[nodiscard]] TLoadSignal emit_load_signal() noexcept
        {
            static_assert(
                TPluginAdapterObligationTraits<Derived>::has_emit_load_signal,
                "Derived TPluginAdapter must implement emit_load_signal() -> TLoadSignal");

            return derived().emit_load_signal();
        }

        [[nodiscard]] TNextDestinationRequest next_destination_request() noexcept
        {
            static_assert(
                TPluginAdapterObligationTraits<Derived>::has_next_destination_request,
                "Derived TPluginAdapter must implement next_destination_request() -> TNextDestinationRequest");

            return derived().next_destination_request();
        }

    protected:
        constexpr TPluginAdapter() noexcept = default;

        [[nodiscard]] constexpr Derived& derived() noexcept
        {
            return static_cast<Derived&>(*this);
        }

        [[nodiscard]] constexpr const Derived& derived() const noexcept
        {
            return static_cast<const Derived&>(*this);
        }
    };
}