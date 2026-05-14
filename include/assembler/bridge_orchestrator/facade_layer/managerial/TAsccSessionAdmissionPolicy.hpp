#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/managerial/TAsccSessionReadinessView.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/sessions/requests/TSessionOpenRequest.hpp"

/**
 * @file TAsccSessionAdmissionPolicy.hpp
 * @brief Managerial facade policy for admitting ASCC session lifecycle state.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccSessionAdmissionPolicy` is part of the ASCC Managerial Facade. It
 * admits or rejects a facade-prepared `TSessionOpenRequest` by opening the
 * canonical `TSession` lifecycle model and projecting the result into
 * `TAsccSessionReadinessView`.
 *
 * This policy is a component-readiness policy. It is not protocol stepping,
 * bridge execution, endpoint invocation, or transport session creation.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/managerial/
 * ```
 *
 * It is called after administrative session policy selection and request
 * adaptation, before protocol declaration and consuming operation.
 *
 * @section relationship_to_sessions Relationship To Session Model Entities
 * The policy uses:
 *
 * ```text
 * TSessionOpenRequest
 * TSession::open(...)
 * TSessionView
 * TSessionSnapshot
 * TSessionResult
 * ```
 *
 * It preserves the session model as the authoritative lifecycle runtime and
 * only wraps its outcome into facade-level readiness evidence.
 *
 * @section relationship_to_protocols Relationship To Protocols
 * The output readiness view may feed `TSessionProtocolBootstrapPolicy`, which
 * decides whether an open session may be used to declare a `TBridgeProtocol`.
 * This policy itself does not declare or advance protocols.
 *
 * @section relationship_to_facade_siblings Relationship To Other Facade Headers
 * Expected flow:
 *
 * ```text
 * TAsccSessionOpenRequestAdapter
 *     -> TAsccSessionAdmissionPolicy
 *     -> TAsccSessionReadinessView
 *     -> TAsccManagerialReadinessView
 * ```
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may select the session profile. This policy only
 * checks whether the selected local session profile can be admitted in ASCC.
 * It does not own governance semantics.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - protocol execution;
 * - bridge run-loop execution;
 * - adapter/port invocation;
 * - endpoint resource lifecycle;
 * - global policy assignment;
 * - registry mutation;
 * - persistence, telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section current_shape Current Shape
 * The current policy opens the canonical session and then derives readiness
 * from its view, snapshot, result, compatibility, and a supplied bootstrap flag.
 * Later versions may consume richer binding readiness and lifecycle transition
 * reports.
 */

namespace assembler::communication_context
{
    struct TAsccSessionAdmissionPolicy final
    {
        [[nodiscard]] static constexpr TAsccSessionReadinessView admit(
            TSessionOpenRequest request,
            bool protocol_bootstrap_allowed,
            std::string_view note = {}) noexcept
        {
            const auto session = TSession::open(request);

            return TAsccSessionReadinessView::from_session_evidence(
                session.view(),
                session.snapshot(),
                session.result(),
                request.compatibility,
                protocol_bootstrap_allowed,
                note);
        }
    };
}
