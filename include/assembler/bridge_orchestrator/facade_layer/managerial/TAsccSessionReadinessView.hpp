#pragma once

#include <string_view>

#include "assembler/communication_context/compatibility/views/TCompatibilityView.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/sessions/results/TSessionResult.hpp"
#include "assembler/communication_context/sessions/snapshots/TSessionSnapshot.hpp"
#include "assembler/communication_context/sessions/views/TSessionView.hpp"

/**
 * @file TAsccSessionReadinessView.hpp
 * @brief Managerial facade readiness projection for ASCC session lifecycle.
 *
 * @section ascc_facade_purpose Purpose
 * `TAsccSessionReadinessView` is part of the ASCC Managerial Facade. It
 * projects whether a selected binding and session policy have produced, or can
 * produce, a session lifecycle state suitable for protocol declaration and
 * later bridge operation.
 *
 * This view is a readiness/evidence object. It is not a session opener, not a
 * protocol executor, not a bridge executor, and not an endpoint resource owner.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/managerial/
 * ```
 *
 * Managerial surface answers:
 *
 * ```text
 * Is the selected session configuration ready enough to support protocol
 * declaration for this ASCC component profile?
 * ```
 *
 * @section relationship_to_sessions Relationship To Session Model Entities
 * This readiness view consumes session model evidence:
 *
 * ```text
 * TSessionView
 * TSessionSnapshot
 * TSessionResult
 * TCompatibilityView
 * ```
 *
 * It does not mutate `TSession`. It does not call `TSession::open()` itself.
 * It only projects the outcome of a session-admission/opening path into a
 * facade-level readiness result.
 *
 * @section relationship_to_protocols Relationship To Protocols
 * A protocol may be declared only after an open/admissible session exists.
 * Therefore, this view is an upstream input to protocol readiness/admission:
 *
 * ```text
 * TAsccSessionReadinessView
 *     -> TSessionProtocolBootstrapPolicy
 *     -> TBridgeProtocol::declare(...)
 *     -> TAsccProtocolReadinessView
 * ```
 *
 * @section relationship_to_facade_siblings Relationship To Other Facade Headers
 * This view contributes to `TAsccManagerialReadinessView` and must be produced
 * before the consuming facade exposes a session-dependent bridge/protocol
 * operation.
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may require strict compatibility, materialized
 * binding, or declaration-only sessions. ASCC does not own those global policy
 * semantics. ASCC reports whether its session layer can realize the selected
 * session profile.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - session mutation;
 * - protocol stepping;
 * - bridge loop execution;
 * - endpoint resource acquisition;
 * - adapter/port invocation;
 * - binding construction;
 * - compatibility evaluation from scratch;
 * - registry mutation;
 * - persistence, telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section mature_shape Final Intended Shape
 * A mature version may include references to selected session profile id,
 * binding readiness report, lifecycle transition report, protocol bootstrap
 * readiness, safe-point evidence, and diagnostic evidence references. The
 * current version captures the core readiness projection in a bounded
 * header-only shape.
 */

namespace assembler::communication_context
{
    struct TAsccSessionReadinessView final
    {
        TSessionView session_view{};
        TSessionSnapshot session_snapshot{};
        TSessionResult session_result{};
        TCompatibilityView compatibility{};
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        bool session_open{false};
        bool compatibility_passed{false};
        bool protocol_bootstrap_allowed{false};
        std::string_view readiness_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return session_view.is_valid()
                && session_snapshot.is_valid()
                && status != TAsccComponentReadinessStatus::unknown;
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && status == TAsccComponentReadinessStatus::ready
                && session_open
                && compatibility_passed
                && protocol_bootstrap_allowed
                && session_result.succeeded();
        }

        [[nodiscard]] static constexpr TAsccSessionReadinessView from_session_evidence(
            TSessionView view,
            TSessionSnapshot snapshot,
            TSessionResult result,
            TCompatibilityView compatibility_view,
            bool bootstrap_allowed,
            std::string_view note = {}) noexcept
        {
            const bool open = is_open_session_status(view.status);
            const bool compatibility_ok = compatibility_view.passed();
            const bool overall_ready = open
                && compatibility_ok
                && bootstrap_allowed
                && result.succeeded();

            return TAsccSessionReadinessView{
                view,
                snapshot,
                result,
                compatibility_view,
                overall_ready
                    ? TAsccComponentReadinessStatus::ready
                    : TAsccComponentReadinessStatus::blocked,
                open,
                compatibility_ok,
                bootstrap_allowed,
                note
            };
        }
    };
}
