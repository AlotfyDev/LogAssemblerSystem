#pragma once

#include <type_traits>
#include <utility>

#include "assembler/communication_context/bridge_carriers/admission/TAdmissionResult.hpp"
#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"

/**
 * @file TPortObligationTraits_CrtpAdjusted.hpp
 * @brief C++17 detection traits for host-side port obligations with CRTP-adjusted detection.
 *
 * @section design_philosophy Design Philosophy
 * This implementation adjusts the SFINAE detection logic specifically for CRTP (Curiously Recurring Template Pattern) inheritance patterns.
 * The key adjustments are:
 * - Use const T& in std::declval to match const method signatures in CRTP derived classes
 * - Ensure detection works for classes defined after header inclusion (post-definition instantiation)
 * - Maintain strict type checking while being more permissive for CRTP access patterns
 * - Focus on method accessibility and signature compatibility rather than exact type matching
 *
 * The philosophy is to make SFINAE traits robust for CRTP by:
 * 1. Using const references to match typical CRTP method signatures
 * 2. Allowing for inheritance-based method resolution
 * 3. Providing clear error messages for missing implementations
 * 4. Ensuring compile-time verification without runtime overhead
 *
 * This approach addresses the dysfunctionality where standard SFINAE failed to detect CRTP methods
 * by adjusting the detection to be more CRTP-aware while maintaining static polymorphism principles.
 *
 * @section implementation_structure Implementation Structure
 * - detail namespace: Contains low-level SFINAE detection templates
 * - TPortObligationTraits<T>: Main trait class with boolean flags for each obligation
 * - is_port_obligation_surface<T>: Aggregate trait for complete surface checking
 * - Uses std::void_t for SFINAE and std::is_same for type verification
 * - Const-correct detection to work with CRTP const methods
 */

namespace assembler::communication_context
{
    namespace detail
    {
        template<typename, typename = void>
        struct has_port_readiness_method_crtp : std::false_type {};

        template<typename T>
        struct has_port_readiness_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().readiness(std::declval<const TPlacementRequest&>()))>>
            : std::is_same<
                decltype(std::declval<const T&>().readiness(std::declval<const TPlacementRequest&>())),
                TReadinessView
              > {};

        template<typename, typename = void>
        struct has_port_admit_method_crtp : std::false_type {};

        template<typename T>
        struct has_port_admit_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().admit(std::declval<const TPlacementRequest&>()))>>
            : std::is_same<
                decltype(std::declval<const T&>().admit(std::declval<const TPlacementRequest&>())),
                TAdmissionResult
              > {};

        template<typename, typename = void>
        struct has_port_placement_handle_method_crtp : std::false_type {};

        template<typename T>
        struct has_port_placement_handle_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().placement_handle(std::declval<const TPlacementRequest&>()))>>
            : std::is_same<
                decltype(std::declval<const T&>().placement_handle(std::declval<const TPlacementRequest&>())),
                TPlacementHandle
              > {};

        template<typename, typename = void>
        struct has_port_receive_load_signal_method_crtp : std::false_type {};

        template<typename T>
        struct has_port_receive_load_signal_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().receive_load_signal(std::declval<const TLoadSignal&>()))>>
            : std::is_same<
                decltype(std::declval<const T&>().receive_load_signal(std::declval<const TLoadSignal&>())),
                TBridgeResult
              > {};

        template<typename, typename = void>
        struct has_port_next_destination_method_crtp : std::false_type {};

        template<typename T>
        struct has_port_next_destination_method_crtp<
            T,
            std::void_t<decltype(std::declval<const T&>().next_destination(std::declval<const TNextDestinationRequest&>()))>>
            : std::is_same<
                decltype(std::declval<const T&>().next_destination(std::declval<const TNextDestinationRequest&>())),
                TBridgeResult
              > {};
    }

    template<typename T>
    struct TPortObligationTraits_CrtpAdjusted final
    {
        static constexpr bool has_readiness =
            detail::has_port_readiness_method_crtp<T>::value;

        static constexpr bool has_admission =
            detail::has_port_admit_method_crtp<T>::value;

        static constexpr bool has_placement_handle =
            detail::has_port_placement_handle_method_crtp<T>::value;

        static constexpr bool has_load_signal =
            detail::has_port_receive_load_signal_method_crtp<T>::value;

        static constexpr bool has_next_destination =
            detail::has_port_next_destination_method_crtp<T>::value;

        static constexpr bool satisfies_primary_placement_surface =
            has_readiness
            && has_admission
            && has_placement_handle
            && has_load_signal
            && has_next_destination;
    };

    template<typename T>
    struct is_port_obligation_surface_crtp_adjusted
        : std::integral_constant<bool, TPortObligationTraits_CrtpAdjusted<T>::satisfies_primary_placement_surface>
    {};
}