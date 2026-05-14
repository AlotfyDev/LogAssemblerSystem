#pragma once

#include "assembler/communication_context/sessions/status/TSessionStatus.hpp"

/**
 * @file TSessionLifecycleTransitionMatrix.hpp
 * @brief Declarative transition matrix for ASCC session lifecycle status.
 *
 * @section ascc_purpose Purpose
 * `TSessionLifecycleTransitionMatrix` formalizes the legal session lifecycle
 * transitions currently implied by `TSession` methods such as `open`,
 * `activate`, `complete`, and `reject`.
 *
 * It is a state-policy helper, not a session executor. It describes whether a
 * lifecycle transition is allowed; it does not mutate `TSession` itself.
 *
 * @section relationship_to_session_runtime Relationship To Session Runtime
 * `TSession` remains the authoritative lifecycle value that actually mutates
 * session status and bridge-visible protocol state. This matrix should be used
 * by facade readiness, tests, diagnostics, and future compliance checks to
 * validate or explain allowed lifecycle movement.
 *
 * Expected relationship:
 *
 * ```text
 * TSessionStatus
 *     -> TSessionLifecycleTransitionMatrix
 *     -> TSession / TAsccSessionAdmissionPolicy / diagnostics
 * ```
 *
 * @section relationship_to_facade Relationship To Facade Layer
 * The Managerial Facade may use this matrix to explain why a selected session
 * state can or cannot proceed to protocol bootstrap or consuming operation.
 *
 * @section policy_relationship Policy Relationship
 * This matrix may support policy-realizable session behavior, but it does not
 * own governance policy semantics. It only defines ASCC-local lifecycle legality.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - session mutation;
 * - protocol stepping;
 * - bridge execution;
 * - endpoint invocation;
 * - timeout scheduling;
 * - persistence, telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section current_shape Current Shape
 * The current matrix is intentionally compact and constexpr-friendly. Later
 * waves may add reports, transition reasons, transition owners, and facade-safe
 * evidence references.
 */

namespace assembler::communication_context
{
    struct TSessionLifecycleTransitionMatrix final
    {
        [[nodiscard]] static constexpr bool can_transition(
            TSessionStatus from,
            TSessionStatus to) noexcept
        {
            if (from == to)
            {
                return true;
            }

            switch (from)
            {
                case TSessionStatus::unknown:
                    return to == TSessionStatus::pending_open
                        || to == TSessionStatus::open
                        || to == TSessionStatus::rejected;

                case TSessionStatus::pending_open:
                    return to == TSessionStatus::open
                        || to == TSessionStatus::rejected
                        || to == TSessionStatus::failed
                        || to == TSessionStatus::deferred;

                case TSessionStatus::open:
                    return to == TSessionStatus::active
                        || to == TSessionStatus::closing
                        || to == TSessionStatus::completed
                        || to == TSessionStatus::rejected
                        || to == TSessionStatus::failed
                        || to == TSessionStatus::suspended;

                case TSessionStatus::active:
                    return to == TSessionStatus::closing
                        || to == TSessionStatus::completed
                        || to == TSessionStatus::failed
                        || to == TSessionStatus::suspended;

                case TSessionStatus::closing:
                    return to == TSessionStatus::completed
                        || to == TSessionStatus::failed;

                case TSessionStatus::suspended:
                    return to == TSessionStatus::active
                        || to == TSessionStatus::closing
                        || to == TSessionStatus::expired
                        || to == TSessionStatus::failed;

                case TSessionStatus::completed:
                case TSessionStatus::rejected:
                case TSessionStatus::failed:
                case TSessionStatus::deferred:
                case TSessionStatus::expired:
                    return false;
            }

            return false;
        }
    };
}
