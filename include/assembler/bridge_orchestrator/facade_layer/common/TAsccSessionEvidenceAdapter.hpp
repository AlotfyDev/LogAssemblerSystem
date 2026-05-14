#pragma once

#include "assembler/communication_context/facade_layer/managerial/TAsccSessionReadinessView.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"

/**
 * @file TAsccSessionEvidenceAdapter.hpp
 * @brief Cross-facade adapter for projecting session evidence into ASCC facade readiness.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccSessionEvidenceAdapter` is a cross-facade helper that converts the
 * canonical session model evidence (`TSessionView`, `TSessionSnapshot`,
 * `TSessionResult`, and compatibility view) into `TAsccSessionReadinessView`.
 *
 * The adapter makes session evidence facade-consumable without allowing
 * Pipeline Composer, administrative surfaces, or consuming surfaces to mutate
 * `TSession` internals directly.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/common/
 * ```
 *
 * It is common because session evidence may be used by managerial readiness,
 * diagnostics, consuming operation reports, and later audit/export surfaces.
 *
 * @section relationship_to_sessions Relationship To Session Model Entities
 * The adapter consumes an already produced `TSession`. It does not create the
 * session and does not decide whether opening was valid. It simply projects
 * existing session evidence into a facade-level readiness view.
 *
 * @section relationship_to_facade_siblings Relationship To Other Facade Headers
 * Expected usage:
 *
 * ```text
 * TSession
 *     -> TAsccSessionEvidenceAdapter
 *     -> TAsccSessionReadinessView
 *     -> TAsccManagerialReadinessView / future facade reports
 * ```
 *
 * @section policy_relationship Policy Relationship
 * This adapter is policy-neutral. If a composition-level policy requires
 * session evidence, this adapter supplies a normalized ASCC view. It does not
 * evaluate policy semantics.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - session opening;
 * - lifecycle mutation;
 * - protocol declaration;
 * - protocol stepping;
 * - bridge operation;
 * - endpoint invocation;
 * - registry mutation;
 * - persistence/export backends;
 * - telemetry, IO, threading, async, or scheduler behavior.
 */

namespace assembler::communication_context
{
    struct TAsccSessionEvidenceAdapter final
    {
        [[nodiscard]] static constexpr TAsccSessionReadinessView to_readiness_view(
            const TSession& session,
            bool protocol_bootstrap_allowed,
            std::string_view note = {}) noexcept
        {
            return TAsccSessionReadinessView::from_session_evidence(
                session.view(),
                session.snapshot(),
                session.result(),
                session.compatibility,
                protocol_bootstrap_allowed,
                note);
        }
    };
}
