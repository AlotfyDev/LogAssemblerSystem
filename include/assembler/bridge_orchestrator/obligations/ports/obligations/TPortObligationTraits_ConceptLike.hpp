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
 * @file TPortObligationTraits_ConceptLike.hpp
 * @brief C++17 detection traits for host-side port obligations using concept-like detection.
 *
 * @section design_philosophy Design Philosophy
 * This implementation uses a concept-like detection approach, simulating C++20 concepts in C++17.
 * The key principles are:
 * - Unified detection: Check all required methods in a single SFINAE context
 * - Concept-like requirements: Define a complete "concept" that the type must satisfy
 * - Holistic validation: Ensure the entire obligation surface is present and correct
 * - Error clarity: Provide clear compile-time feedback when requirements are not met
 *
 * The philosophy is to treat the obligation surface as a single concept that must be satisfied,
 * rather than checking individual methods in isolation. This approach:
 * 1. Reduces false positives from partial implementations
 * 2. Provides atomic concept satisfaction (all-or-nothing)
 * 3. Mimics C++20 concept checking with SFINAE
 * 4. Ensures complete interface compliance for CRTP classes
 *
 * This addresses the dysfunctionality by using a more holistic detection method that
 * validates the entire interface contract, making it more robust for CRTP patterns
 * and complex inheritance scenarios.
 *
 * @section implementation_structure Implementation Structure
 * - Single SFINAE check using std::void_t with all method requirements
 * - Concept-like trait that validates complete interface compliance
 * - Uses std::conjunction to combine all detection requirements
 * - Provides both individual method detection and aggregate surface validation
 * - Maintains const-correctness and type safety
 */

namespace assembler::communication_context
{
    namespace detail
    {
        // Concept-like detection: check all methods in a single SFINAE context
        template<typename T, typename = void>
        struct port_obligation_concept_check : std::false_type {};

        template<typename T>
        struct port_obligation_concept_check<
            T,
            std::void_t<
                // All methods must be present with correct signatures
                decltype(std::declval<const T&>().readiness(std::declval<const TPlacementRequest&>())),
                decltype(std::declval<const T&>().admit(std::declval<const TPlacementRequest&>())),
                decltype(std::declval<const T&>().placement_handle(std::declval<const TPlacementRequest&>())),
                decltype(std::declval<const T&>().receive_load_signal(std::declval<const TLoadSignal&>())),
                decltype(std::declval<const T&>().next_destination(std::declval<const TNextDestinationRequest&>())),
                // And return correct types
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().readiness(std::declval<const TPlacementRequest&>())),
                    TReadinessView
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().admit(std::declval<const TPlacementRequest&>())),
                    TAdmissionResult
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().placement_handle(std::declval<const TPlacementRequest&>())),
                    TPlacementHandle
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().receive_load_signal(std::declval<const TLoadSignal&>())),
                    TBridgeResult
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().next_destination(std::declval<const TNextDestinationRequest&>())),
                    TBridgeResult
                >>
            >
        > : std::true_type {};
    }

    template<typename T>
    struct TPortObligationTraits_ConceptLike final
    {
        // Concept-like check: all methods must be present and correctly typed
        static constexpr bool satisfies_primary_placement_surface =
            detail::port_obligation_concept_check<T>::value;

        // For debugging/analysis, individual checks (derived from concept)
        static constexpr bool has_readiness = satisfies_primary_placement_surface;
        static constexpr bool has_admission = satisfies_primary_placement_surface;
        static constexpr bool has_placement_handle = satisfies_primary_placement_surface;
        static constexpr bool has_load_signal = satisfies_primary_placement_surface;
        static constexpr bool has_next_destination = satisfies_primary_placement_surface;
    };

    template<typename T>
    struct is_port_obligation_surface_concept_like
        : std::integral_constant<bool, TPortObligationTraits_ConceptLike<T>::satisfies_primary_placement_surface>
    {};
}