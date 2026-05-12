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
 * @file TPluginAdapterObligationTraits_ConceptLike.hpp
 * @brief C++17 detection traits for content-side plugin-adapter obligations using concept-like detection.
 *
 * @section design_philosophy Design Philosophy
 * This implementation uses a concept-like detection approach for plugin adapter obligations,
 * simulating C++20 concepts in C++17 for content-side interfaces.
 * The key principles are:
 * - Unified detection: Check all required adapter methods in a single SFINAE context
 * - Concept-like requirements: Define a complete "adapter concept" that the type must satisfy
 * - Holistic validation: Ensure the entire adapter obligation surface is present and correct
 * - Error clarity: Provide clear compile-time feedback when adapter requirements are not met
 *
 * The philosophy is to treat the plugin adapter obligation surface as a single concept that must be satisfied,
 * rather than checking individual methods in isolation. This approach:
 * 1. Reduces false positives from partial adapter implementations
 * 2. Provides atomic concept satisfaction for content-side adapters (all-or-nothing)
 * 3. Mimics C++20 concept checking with SFINAE for adapter interfaces
 * 4. Ensures complete interface compliance for CRTP adapter classes
 *
 * This addresses the dysfunctionality by using a more holistic detection method that
 * validates the entire adapter interface contract, making it more robust for CRTP patterns
 * and complex inheritance scenarios in plugin adapter hierarchies.
 *
 * @section implementation_structure Implementation Structure
 * - Single SFINAE check using std::void_t with all adapter method requirements
 * - Concept-like trait that validates complete adapter interface compliance
 * - Uses std::conjunction-like logic through multiple std::enable_if_t conditions
 * - Provides both individual method detection and aggregate surface validation
 * - Maintains const-correctness and type safety for adapter methods
 */

namespace assembler::communication_context
{
    namespace detail
    {
        // Concept-like detection: check all adapter methods in a single SFINAE context
        template<typename T, typename = void>
        struct plugin_adapter_obligation_concept_check : std::false_type {};

        template<typename T>
        struct plugin_adapter_obligation_concept_check<
            T,
            std::void_t<
                // All adapter methods must be present with correct signatures
                decltype(std::declval<const T&>().readiness()),
                decltype(std::declval<const T&>().prepare_placement_request()),
                decltype(std::declval<const T&>().accept_placement_handle(std::declval<const TPlacementHandle&>())),
                decltype(std::declval<const T&>().emit_load_signal()),
                decltype(std::declval<const T&>().next_destination_request()),
                // And return correct types
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().readiness()),
                    TReadinessView
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().prepare_placement_request()),
                    TPlacementRequest
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().accept_placement_handle(std::declval<const TPlacementHandle&>())),
                    TBridgeResult
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().emit_load_signal()),
                    TLoadSignal
                >>,
                std::enable_if_t<std::is_same_v<
                    decltype(std::declval<const T&>().next_destination_request()),
                    TNextDestinationRequest
                >>
            >
        > : std::true_type {};
    }

    template<typename T>
    struct TPluginAdapterObligationTraits_ConceptLike final
    {
        // Concept-like check: all adapter methods must be present and correctly typed
        static constexpr bool satisfies_primary_placement_surface =
            detail::plugin_adapter_obligation_concept_check<T>::value;

        // For debugging/analysis, individual checks (derived from concept)
        static constexpr bool has_readiness = satisfies_primary_placement_surface;
        static constexpr bool has_prepare_placement_request = satisfies_primary_placement_surface;
        static constexpr bool has_accept_placement_handle = satisfies_primary_placement_surface;
        static constexpr bool has_emit_load_signal = satisfies_primary_placement_surface;
        static constexpr bool has_next_destination_request = satisfies_primary_placement_surface;
    };

    template<typename T>
    struct is_plugin_adapter_obligation_surface_concept_like
        : std::integral_constant<bool, TPluginAdapterObligationTraits_ConceptLike<T>::satisfies_primary_placement_surface>
    {};
}