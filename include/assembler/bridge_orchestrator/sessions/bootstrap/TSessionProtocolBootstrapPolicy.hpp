#pragma once

#include "assembler/communication_context/protocols/plans/TBridgeProtocolPlan.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"

/**
 * @file TSessionProtocolBootstrapPolicy.hpp
 * @brief Policy for deciding whether an ASCC session may bootstrap a protocol.
 *
 * @section ascc_purpose Purpose
 * `TSessionProtocolBootstrapPolicy` is the session-to-protocol boundary rule.
 * It answers whether an already opened ASCC session is suitable to declare a
 * `TBridgeProtocol` with a selected `TBridgeProtocolPlan`.
 *
 * This is not protocol execution. It is not bridge execution. It is the
 * readiness bridge between the session lifecycle model and the protocol model.
 *
 * @section relationship_to_sessions Relationship To Sessions
 * `TSession` owns lifecycle state and bridge-visible protocol state at the
 * session boundary. This policy checks whether that session is open and whether
 * its current protocol stage aligns with the selected plan's first step.
 *
 * @section relationship_to_protocols Relationship To Protocols
 * `TBridgeProtocol::declare(...)` expects an open session and a valid plan. This
 * policy can be used before declaration to keep protocol bootstrap decisions
 * explicit and facade-readable.
 *
 * Expected relationship:
 *
 * ```text
 * TSession
 *     + TBridgeProtocolPlan
 *     -> TSessionProtocolBootstrapPolicy
 *     -> TBridgeProtocol::declare(...)
 * ```
 *
 * @section relationship_to_facade Relationship To Facade Layer
 * The Managerial Facade may use this policy while building session and protocol
 * readiness views. It helps answer whether the session layer has produced a
 * lifecycle state ready for the selected protocol.
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may select a protocol profile. This local policy
 * only checks whether the selected protocol can bootstrap from the current ASCC
 * session model state. It does not own governance policy semantics.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - session opening;
 * - protocol state advancement;
 * - bridge run loop;
 * - adapter/port invocation;
 * - endpoint resource lifecycle;
 * - carrier movement;
 * - registry mutation;
 * - persistence, telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section current_shape Current Shape
 * The current policy is a constexpr helper over session and plan validity. A
 * mature version may produce a structured bootstrap report and integrate with
 * ASCC managerial readiness evidence.
 */

namespace assembler::communication_context
{
    struct TSessionProtocolBootstrapPolicy final
    {
        template <std::size_t PlanCapacity>
        [[nodiscard]] static constexpr bool can_bootstrap(
            const TSession& session,
            const TBridgeProtocolPlan<PlanCapacity>& plan) noexcept
        {
            return session.is_open()
                && plan.is_valid()
                && plan.first_step().from == session.protocol_state.current_stage;
        }
    };
}
