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
 * @file TPluginAdapterObligationTraits_CrtpAdjusted.hpp
 * @brief C++17 detection traits for content-side plugin-adapter obligations with CRTP-adjusted detection.
 *
 * @section design_philosophy Design Philosophy
 * This implementation adjusts the SFINAE detection logic specifically for CRTP (Curiously Recurring Template Pattern) inheritance patterns in plugin adapter contexts.
 * The key adjustments are:
 * - Use const T& in std::declval to match const method signatures in CRTP derived classes
 * - Ensure detection works for classes defined after header inclusion (post-definition instantiation)
 * - Maintain strict type checking while being more permissive for CRTP access patterns
 * - Focus on method accessibility and signature compatibility for adapter interfaces
 *
 * The philosophy is to make SFINAE traits robust for CRTP plugin adapters by:
 * 1. Using const references to match typical CRTP method signatures
 * 2. Allowing for inheritance-based method resolution in adapter hierarchies
 * 3. Providing clear error messages for missing adapter implementations
 * 4. Ensuring compile-time verification without runtime overhead for content-side obligations
 *
 * This approach addresses the dysfunctionality where standard SFINAE failed to detect CRTP methods
 * in plugin adapter classes by adjusting the detection to be more CRTP-aware while maintaining
 * static polymorphism principles for content-side interfaces.
 *
 * @section implementation_structure Implementation Structure
 * - detail namespace: Contains low-level SFINAE detection templates for adapter methods
 * - TPluginAdapterObligationTraits_CrtpAdjusted<T>: Main trait class with boolean flags for each adapter obligation
 * - is_plugin_adapter_obligation_surface_crtp_adjusted<T>: Aggregate trait for complete surface checking
 * - Uses std::void_t for SFINAE and std::is_same for type verification
 * - Const-correct detection to work with CRTP const methods in adapters
 */

namespace assembler::communication_context
{
    namespace detail
    {
        template<typename, typename = void>
        struct has_adapter_readiness_method_crtp : std::false_type {};

        template<typename T>
        struct has_adapter_readiness_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().readiness())>>
            : std::is_same<
                decltype(std::declval<const T&>().readiness()),
                TReadinessView
              > {};

        template<typename, typename = void>
        struct has_prepare_placement_request_method_crtp : std::false_type {};

        template<typename T>
        struct has_prepare_placement_request_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().prepare_placement_request())>>
            : std::is_same<
                decltype(std::declval<const T&>().prepare_placement_request()),
                TPlacementRequest
              > {};

        template<typename, typename = void>
        struct has_accept_placement_handle_method_crtp : std::false_type {};

        template<typename T>
        struct has_accept_placement_handle_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().accept_placement_handle(std::declval<const TPlacementHandle&>()))>>
            : std::is_same<
                decltype(std::declval<const T&>().accept_placement_handle(std::declval<const TPlacementHandle&>())),
                TBridgeResult
              > {};

        template<typename, typename = void>
        struct has_emit_load_signal_method_crtp : std::false_type {};

        template<typename T>
        struct has_emit_load_signal_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().emit_load_signal())>>
            : std::is_same<
                decltype(std::declval<const T&>().emit_load_signal()),
                TLoadSignal
              > {};

        template<typename, typename = void>
        struct has_next_destination_request_method_crtp : std::false_type {};

        template<typename T>
        struct has_next_destination_request_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().next_destination_request())>>
            : std::is_same<
                decltype(std::declval<const T&>().next_destination_request()),
                TNextDestinationRequest
              > {};
    }

    template<typename T>
    struct TPluginAdapterObligationTraits_CrtpAdjusted final
    {
        static constexpr bool has_readiness =
            detail::has_adapter_readiness_method_crtp<T>::value;

        static constexpr bool has_prepare_placement_request =
            detail::has_prepare_placement_request_method_crtp<T>::value;

        static constexpr bool has_accept_placement_handle =
            detail::has_accept_placement_handle_method_crtp<T>::value;

        static constexpr bool has_emit_load_signal =
            detail::has_emit_load_signal_method_crtp<T>::value;

        static constexpr bool has_next_destination_request =
            detail::has_next_destination_request_method_crtp<T>::value;

        static constexpr bool satisfies_primary_placement_surface =
            has_readiness
            && has_prepare_placement_request
            && has_accept_placement_handle
            && has_emit_load_signal
            && has_next_destination_request;
    };

    template<typename T>
    struct is_plugin_adapter_obligation_surface_crtp_adjusted
        : std::integral_constant<bool, TPluginAdapterObligationTraits_CrtpAdjusted<T>::satisfies_primary_placement_surface>
    {};
}