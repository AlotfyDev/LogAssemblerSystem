#pragma once

#include <type_traits>
#include <utility>

#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffHandle.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"
#include "assembler/communication_context/integration_boundaries/descriptors/TIntegrationBoundaryDescriptor.hpp"
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"
#include "assembler/communication_context/integration_boundaries/views/TIntegrationBoundaryPortView.hpp"

/**
 * @file TIntegrationBoundaryPortTraits.hpp
 * @brief Compile-time obligation detection for abstract integration boundary ports.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - trait detection for future boundary port concrete implementations;
 * - static checks for view, descriptor, readiness, accept_handoff,
 *   complete_handoff, and reject_handoff surfaces;
 * - no concrete implementation behavior.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - SFINAE-based detection helpers;
 * - aggregate booleans for required boundary obligations;
 * - no concepts dependency, preserving C++17 compatibility.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete persistence, telemetry, ABI, read-side, or external receiver
 *   integration;
 * - endpoint-domain internals;
 * - adapter/port call wiring for concrete endpoints;
 * - storage, database, file IO, network IO, telemetry export, or logging sinks;
 * - runtime scheduling, service location, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - bridge execution replacement;
 * - ownership over downstream lifecycle or endpoint resources.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W13 may depend on W01-W12 public Communication Context surfaces.
 * It must remain future-facing and abstract. Concrete implementations belong
 * to later dedicated binding waves.
 */

namespace assembler::communication_context
{
    namespace detail
    {
        template<typename T, typename = void>
        struct has_boundary_view_impl : std::false_type {};

        template<typename T>
        struct has_boundary_view_impl<
            T,
            std::void_t<decltype(std::declval<const T&>().boundary_view())>>
            : std::is_same<
                  decltype(std::declval<const T&>().boundary_view()),
                  TIntegrationBoundaryPortView>
        {};

        template<typename T, typename = void>
        struct has_boundary_descriptor_impl : std::false_type {};

        template<typename T>
        struct has_boundary_descriptor_impl<
            T,
            std::void_t<decltype(std::declval<const T&>().boundary_descriptor())>>
            : std::is_same<
                  decltype(std::declval<const T&>().boundary_descriptor()),
                  TIntegrationBoundaryDescriptor>
        {};

        template<typename T, typename = void>
        struct has_boundary_readiness_impl : std::false_type {};

        template<typename T>
        struct has_boundary_readiness_impl<
            T,
            std::void_t<decltype(std::declval<T&>().boundary_readiness(
                std::declval<const TBoundaryHandoffRequest&>()))>>
            : std::is_same<
                  decltype(std::declval<T&>().boundary_readiness(
                      std::declval<const TBoundaryHandoffRequest&>())),
                  TReadinessView>
        {};

        template<typename T, typename = void>
        struct has_accept_boundary_handoff_impl : std::false_type {};

        template<typename T>
        struct has_accept_boundary_handoff_impl<
            T,
            std::void_t<decltype(std::declval<T&>().accept_boundary_handoff(
                std::declval<const TBoundaryHandoffRequest&>()))>>
            : std::is_same<
                  decltype(std::declval<T&>().accept_boundary_handoff(
                      std::declval<const TBoundaryHandoffRequest&>())),
                  TBoundaryHandoffResult>
        {};

        template<typename T, typename = void>
        struct has_complete_boundary_handoff_impl : std::false_type {};

        template<typename T>
        struct has_complete_boundary_handoff_impl<
            T,
            std::void_t<decltype(std::declval<T&>().complete_boundary_handoff(
                std::declval<const TBoundaryHandoffHandle&>()))>>
            : std::is_same<
                  decltype(std::declval<T&>().complete_boundary_handoff(
                      std::declval<const TBoundaryHandoffHandle&>())),
                  TBoundaryHandoffResult>
        {};

        template<typename T, typename = void>
        struct has_reject_boundary_handoff_impl : std::false_type {};

        template<typename T>
        struct has_reject_boundary_handoff_impl<
            T,
            std::void_t<decltype(std::declval<T&>().reject_boundary_handoff(
                std::declval<const TBoundaryHandoffRequest&>()))>>
            : std::is_same<
                  decltype(std::declval<T&>().reject_boundary_handoff(
                      std::declval<const TBoundaryHandoffRequest&>())),
                  TBoundaryHandoffResult>
        {};
    }

    template<typename T>
    struct TIntegrationBoundaryPortTraits final
    {
        static constexpr bool has_view =
            detail::has_boundary_view_impl<T>::value;

        static constexpr bool has_descriptor =
            detail::has_boundary_descriptor_impl<T>::value;

        static constexpr bool has_readiness =
            detail::has_boundary_readiness_impl<T>::value;

        static constexpr bool has_accept_handoff =
            detail::has_accept_boundary_handoff_impl<T>::value;

        static constexpr bool has_complete_handoff =
            detail::has_complete_boundary_handoff_impl<T>::value;

        static constexpr bool has_reject_handoff =
            detail::has_reject_boundary_handoff_impl<T>::value;

        static constexpr bool satisfies_required_surface =
            has_view
            && has_descriptor
            && has_readiness
            && has_accept_handoff
            && has_complete_handoff
            && has_reject_handoff;
    };
}
