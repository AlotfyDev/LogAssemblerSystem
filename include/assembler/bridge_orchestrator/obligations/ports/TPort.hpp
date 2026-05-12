#pragma once

#include <type_traits>

#include "assembler/communication_context/bridge_carriers/admission/TAdmissionResult.hpp"
#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/obligations/ports/obligations/TPortObligationTraits.hpp"
#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"

/**
 * @file TPort.hpp
 * @brief CRTP host-side port obligation facade.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - canonical static abstraction for a host-side port obligation surface;
 * - future extension point for concrete placement, delivery, persistence,
 *   telemetry, receiver, and ABI-facing ports;
 * - CRTP facade that lets the bridge call obligations without depending on
 *   endpoint implementation classes directly.
 *
 * @section ascc_current_wave Current W05 Implementation Scope
 * This W05 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It defines bridge-visible host-side port
 * obligations and content-side plugin-adapter obligations without binding
 * execution, session execution, protocol execution, bridge orchestration, or
 * endpoint-domain dependency.
 *
 * - CRTP wrapper over Derived;
 * - primary host-side placement obligation methods;
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
 * - dynamic polymorphic port registry or binding engine.
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
    class TPort
    {
    public:
        using derived_type = Derived;

        [[nodiscard]] constexpr TPortView view() const noexcept
        {
            return derived().view();
        }

        [[nodiscard]] TReadinessView readiness(
            const TPlacementRequest& request) noexcept
        {
            static_assert(
                TPortObligationTraits<Derived>::has_readiness,
                "Derived TPort must implement readiness(const TPlacementRequest&) -> TReadinessView");

            return derived().readiness(request);
        }

        [[nodiscard]] TAdmissionResult admit(
            const TPlacementRequest& request) noexcept
        {
            static_assert(
                TPortObligationTraits<Derived>::has_admission,
                "Derived TPort must implement admit(const TPlacementRequest&) -> TAdmissionResult");

            return derived().admit(request);
        }

        [[nodiscard]] TPlacementHandle placement_handle(
            const TPlacementRequest& request) noexcept
        {
            static_assert(
                TPortObligationTraits<Derived>::has_placement_handle,
                "Derived TPort must implement placement_handle(const TPlacementRequest&) -> TPlacementHandle");

            return derived().placement_handle(request);
        }

        [[nodiscard]] TBridgeResult receive_load_signal(
            const TLoadSignal& signal) noexcept
        {
            static_assert(
                TPortObligationTraits<Derived>::has_load_signal,
                "Derived TPort must implement receive_load_signal(const TLoadSignal&) -> TBridgeResult");

            return derived().receive_load_signal(signal);
        }

        [[nodiscard]] TBridgeResult next_destination(
            const TNextDestinationRequest& request) noexcept
        {
            static_assert(
                TPortObligationTraits<Derived>::has_next_destination,
                "Derived TPort must implement next_destination(const TNextDestinationRequest&) -> TBridgeResult");

            return derived().next_destination(request);
        }

    protected:
        constexpr TPort() noexcept = default;

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