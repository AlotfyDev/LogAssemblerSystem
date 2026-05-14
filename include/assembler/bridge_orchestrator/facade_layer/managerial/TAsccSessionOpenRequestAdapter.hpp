#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"
#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"
#include "assembler/communication_context/sessions/requests/TSessionOpenRequest.hpp"

/**
 * @file TAsccSessionOpenRequestAdapter.hpp
 * @brief Managerial facade adapter that builds session-open requests.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccSessionOpenRequestAdapter` is part of the ASCC Managerial Facade. It
 * adapts facade-selected component/session configuration into a
 * `TSessionOpenRequest`, which is the session model's canonical opening
 * request carrier.
 *
 * This adapter exists to prevent the Pipeline Composer or consuming surfaces
 * from constructing raw session-open requests by depending on session internals.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/managerial/
 * ```
 *
 * It sits between administrative profile selection and actual session
 * admission:
 *
 * ```text
 * TAsccSessionPolicyCatalogView
 *     -> selected TSessionPolicy
 *     -> TAsccSessionOpenRequestAdapter
 *     -> TSessionOpenRequest
 *     -> TAsccSessionAdmissionPolicy
 * ```
 *
 * @section relationship_to_sessions Relationship To Session Model Entities
 * The adapter produces `TSessionOpenRequest` using:
 *
 * ```text
 * TSessionId
 * TBinding
 * TSessionPolicy
 * TCorrelationToken
 * ```
 *
 * The produced request still uses the canonical `TSessionOpenRequest::make`
 * path, which captures strict compatibility through `TCompatibilityEvaluator`.
 * Therefore this adapter does not duplicate compatibility logic. It preserves
 * the session model's existing request semantics while making it facade-safe.
 *
 * @section relationship_to_facade_siblings Relationship To Other Facade Headers
 * This adapter feeds `TAsccSessionAdmissionPolicy`. It is not a readiness view
 * and not a consuming operation entry point.
 *
 * @section policy_relationship Policy Relationship
 * A composition-level policy may select strict declaration session or
 * materialized-binding session behavior. This adapter materializes that
 * selected local session policy as an ASCC session-open request. It does not
 * own policy semantics.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - session lifecycle mutation;
 * - protocol declaration;
 * - bridge execution;
 * - adapter/port invocation;
 * - endpoint resource acquisition;
 * - policy governance;
 * - registry insertion;
 * - persistence, telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section mature_shape Final Intended Shape
 * A mature adapter may consume component profile ids, binding readiness reports,
 * session profile ids, policy-derived configuration references, and evidence
 * correlation data. The current version keeps the adapter focused on canonical
 * request construction.
 */

namespace assembler::communication_context
{
    struct TAsccSessionOpenRequestAdapter final
    {
        [[nodiscard]] static constexpr TSessionOpenRequest from_binding_and_policy(
            TSessionId id,
            TBinding binding,
            TSessionPolicy policy,
            std::string_view session_name = {},
            TCorrelationToken correlation = TCorrelationToken::invalid()) noexcept
        {
            return TSessionOpenRequest::make(
                id,
                binding,
                policy,
                session_name,
                correlation);
        }
    };
}
