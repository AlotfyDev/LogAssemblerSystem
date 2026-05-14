#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"

/**
 * @file TAsccSessionPolicyCatalogView.hpp
 * @brief Administrative facade view for ASCC-supported session policy families.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccSessionPolicyCatalogView` is part of the ASCC Administrative Facade.
 * It exposes, in a bounded and read-only form, the session-opening policy
 * profiles that the Communication Context component declares as selectable by a
 * higher-level Pipeline Composer.
 *
 * This catalog is not a session opener. It does not create `TSession`, evaluate
 * bindings, advance protocol state, invoke endpoints, allocate resources, or
 * manage a session registry. It is an administrative declaration surface that
 * says which session policies are available for composition-time selection.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/administrative/
 * ```
 *
 * Administrative surface answers:
 *
 * ```text
 * Which session policy families can this ASCC component offer to a Pipeline
 * Composer profile?
 * ```
 *
 * The Managerial Facade later decides whether a selected policy can open a
 * session for a specific binding and compatibility snapshot.
 *
 * @section relationship_to_sessions Relationship To Session Model Entities
 * This catalog stores `TSessionPolicy` descriptors. `TSessionPolicy` already
 * describes strict declaration sessions, materialized-binding sessions, strict
 * compatibility requirements, and future lifecycle gates.
 *
 * The catalog deliberately does not expose mutable `TSession` state or build a
 * `TSessionOpenRequest`. Those are Managerial Facade responsibilities.
 *
 * Expected mature relationship:
 *
 * ```text
 * TAsccSessionPolicyCatalogView
 *     -> selected TSessionPolicy
 *     -> TAsccSessionOpenRequestAdapter
 *     -> TAsccSessionAdmissionPolicy
 *     -> TAsccSessionReadinessView
 * ```
 *
 * @section relationship_to_facade_siblings Relationship To Other Facade Headers
 * This administrative catalog feeds the session admission path. It is a
 * discovery and declaration object. It must not become the manager or consumer.
 *
 * ```text
 * TAsccAdministrativeFacade
 *     -> TAsccSessionPolicyCatalogView
 *     -> TAsccSessionAdmissionPolicy
 *     -> TAsccManagerialReadinessView
 * ```
 *
 * Consuming facade surfaces must never modify this catalog.
 *
 * @section policy_relationship Policy Relationship
 * Policy belongs primarily to the composition layer. This catalog supplies the
 * session-policy capabilities that a composition-level policy may select. ASCC
 * does not own global policy semantics; it declares what local session profile
 * capabilities it can realize when admitted.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - session opening;
 * - compatibility evaluation;
 * - protocol bootstrap;
 * - bridge execution;
 * - endpoint invocation;
 * - adapter or port calls;
 * - policy governance;
 * - registry mutation;
 * - persistence, telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section current_shape Current Shape
 * The current shape is a bounded catalog of concrete `TSessionPolicy` values.
 * Later waves may introduce profile identifiers, names, versions, and richer
 * policy descriptors without changing the administrative responsibility.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccSessionPolicyCatalogView final
    {
        std::array<TSessionPolicy, Capacity> policies{};
        std::size_t count{0u};
        std::string_view catalog_name{"ascc_session_policy_catalog"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return count <= Capacity && !catalog_name.empty();
        }

        constexpr bool add(TSessionPolicy policy) noexcept
        {
            if (count >= Capacity || !policy.is_valid())
            {
                return false;
            }

            policies[count++] = policy;
            return true;
        }

        [[nodiscard]] constexpr const TSessionPolicy& first_policy() const noexcept
        {
            return policies[0u];
        }

        [[nodiscard]] constexpr bool has_policy() const noexcept
        {
            return count > 0u;
        }

        [[nodiscard]] static constexpr TAsccSessionPolicyCatalogView default_session_policies(
            std::string_view name = "ascc_default_session_policy_catalog") noexcept
        {
            TAsccSessionPolicyCatalogView<Capacity> view{{}, 0u, name};
            view.add(TSessionPolicy::strict_declaration_session());
            return view;
        }
    };
}
