#pragma once

#include <type_traits>
#include <utility>

#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"

/**
 * @file TPluginAdapterObligationTraits.hpp
 * @brief C++17 detection traits for content-side plugin-adapter obligations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - static obligation detection for concrete content-side plugin-adapter
 *   implementations;
 * - future support for richer compile-time diagnostics, compatibility
 *   matrices, and binding preflight checks;
 * - C++17-compatible trait layer that preserves the architectural obligation
 *   model without requiring C++20 concepts.
 *
 * @section ascc_current_wave Current W05 Implementation Scope
 * This W05 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It defines bridge-visible host-side port
 * obligations and content-side plugin-adapter obligations without binding
 * execution, session execution, protocol execution, bridge orchestration, or
 * endpoint-domain dependency.
 *
 * - SFINAE detection for required content-side methods;
 * - `is_plugin_adapter_obligation_surface<T>` aggregate trait;
 * - required method shape:
 *   readiness() -> TReadinessView;
 *   prepare_placement_request() -> TPlacementRequest;
 *   accept_placement_handle(TPlacementHandle) -> TBridgeResult;
 *   emit_load_signal() -> TLoadSignal;
 *   next_destination_request() -> TNextDestinationRequest.
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
 * - runtime validation, envelope assembly, or endpoint-specific behavior.
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
    namespace detail
    {
        template<typename, typename = void>
        struct has_adapter_readiness_method : std::false_type {};

        template<typename T>
        struct has_adapter_readiness_method<
            T,
            std::void_t<decltype(std::declval<T&>().readiness())>>
            : std::is_same<
                decltype(std::declval<T&>().readiness()),
                TReadinessView
              > {};

        template<typename, typename = void>
        struct has_prepare_placement_request_method : std::false_type {};

        template<typename T>
        struct has_prepare_placement_request_method<
            T,
            std::void_t<decltype(std::declval<T&>().prepare_placement_request())>>
            : std::is_same<
                decltype(std::declval<T&>().prepare_placement_request()),
                TPlacementRequest
              > {};

        template<typename, typename = void>
        struct has_accept_placement_handle_method : std::false_type {};

        template<typename T>
        struct has_accept_placement_handle_method<
            T,
            std::void_t<decltype(std::declval<T&>().accept_placement_handle(std::declval<const TPlacementHandle&>()))>>
            : std::is_same<
                decltype(std::declval<T&>().accept_placement_handle(std::declval<const TPlacementHandle&>())),
                TBridgeResult
              > {};

        template<typename, typename = void>
        struct has_emit_load_signal_method : std::false_type {};

        template<typename T>
        struct has_emit_load_signal_method<
            T,
            std::void_t<decltype(std::declval<T&>().emit_load_signal())>>
            : std::is_same<
                decltype(std::declval<T&>().emit_load_signal()),
                TLoadSignal
              > {};

        template<typename, typename = void>
        struct has_next_destination_request_method : std::false_type {};

        template<typename T>
        struct has_next_destination_request_method<
            T,
            std::void_t<decltype(std::declval<T&>().next_destination_request())>>
            : std::is_same<
                decltype(std::declval<T&>().next_destination_request()),
                TNextDestinationRequest
              > {};
    }

    template<typename T>
    struct TPluginAdapterObligationTraits final
    {
        static constexpr bool has_readiness =
            detail::has_adapter_readiness_method<T>::value;

        static constexpr bool has_prepare_placement_request =
            detail::has_prepare_placement_request_method<T>::value;

        static constexpr bool has_accept_placement_handle =
            detail::has_accept_placement_handle_method<T>::value;

        static constexpr bool has_emit_load_signal =
            detail::has_emit_load_signal_method<T>::value;

        static constexpr bool has_next_destination_request =
            detail::has_next_destination_request_method<T>::value;

        static constexpr bool satisfies_primary_placement_surface =
            has_readiness
            && has_prepare_placement_request
            && has_accept_placement_handle
            && has_emit_load_signal
            && has_next_destination_request;
    };

    template<typename T>
    struct is_plugin_adapter_obligation_surface
        : std::integral_constant<bool, TPluginAdapterObligationTraits<T>::satisfies_primary_placement_surface>
    {};
}