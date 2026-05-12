#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/protocol_state/transitions/TBridgeTransition.hpp"
#include "assembler/communication_context/protocols/frames/TBridgeProtocolFrame.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/plans/TBridgeProtocolPlan.hpp"
#include "assembler/communication_context/protocols/results/TBridgeProtocolResult.hpp"
#include "assembler/communication_context/protocols/status/TBridgeProtocolStatus.hpp"
#include "assembler/communication_context/protocols/traces/TBridgeProtocolTrace.hpp"
#include "assembler/communication_context/protocols/views/TBridgeProtocolView.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"

/**
 * @file TBridgeProtocol.hpp
 * @brief Bridge-visible protocol declaration and state-advancement value.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - authoritative protocol model binding a protocol id, kind, session,
 *   endpoint-neutral plan, current step index, status, and result;
 * - future input to `TBridge` orchestration without becoming `TBridge`;
 * - bridge-visible state advancement over W02 protocol state while preserving
 *   the rule that endpoint invocation remains outside the protocol model.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - declaration factory from an open/compatible session and plan;
 * - view/frame/trace helpers;
 * - endpoint-neutral `advance_model_step` that applies W02 state transition
 *   only;
 * - completion/rejection/failure helpers;
 * - no adapter calls, no port calls, no bridge loop, and no async behavior.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - complete bridge executor or endpoint call runner.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Protocol Model headers may depend on W01 carriers/results/errors,
 * W02 protocol-state foundations, W06 binding model through sessions, W07
 * compatibility through sessions, and W08 session model. They must not include
 * endpoint-domain headers such as log_level_api, write_side, read_side,
 * persistence implementations, telemetry SDKs, or thin C ABI implementation
 * internals.
 */

namespace assembler::communication_context
{
    template <std::size_t PlanCapacity>
    struct TBridgeProtocol final
    {
        TBridgeProtocolId protocol_id{TBridgeProtocolId::invalid()};
        TBridgeProtocolKind kind{TBridgeProtocolKind::unknown};
        TSession session{};
        TBridgeProtocolPlan<PlanCapacity> plan{};
        std::size_t current_step_index{0u};
        TBridgeProtocolStatus status{TBridgeProtocolStatus::unknown};
        TBridgeProtocolResult last_result{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view protocol_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return protocol_id.is_valid()
                && kind != TBridgeProtocolKind::unknown
                && session.is_valid()
                && plan.is_valid()
                && status != TBridgeProtocolStatus::unknown;
        }

        [[nodiscard]] constexpr bool is_ready() const noexcept
        {
            return is_valid()
                && status == TBridgeProtocolStatus::ready
                && session.is_open()
                && current_step_index < plan.step_count;
        }

        [[nodiscard]] constexpr bool is_active() const noexcept
        {
            return is_valid()
                && status == TBridgeProtocolStatus::active
                && current_step_index < plan.step_count;
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_bridge_protocol_status(status)
                || session.protocol_state.is_terminal();
        }

        [[nodiscard]] constexpr bool has_next_step() const noexcept
        {
            return is_valid()
                && !is_terminal()
                && current_step_index < plan.step_count;
        }

        [[nodiscard]] constexpr const TBridgeProtocolStep& current_step() const noexcept
        {
            return plan.step_at(current_step_index);
        }

        [[nodiscard]] constexpr TBridgeProtocolView view() const noexcept
        {
            if (!is_valid())
            {
                return TBridgeProtocolView::invalid();
            }

            return TBridgeProtocolView{
                protocol_id,
                kind,
                session.session_id,
                status,
                current_step_index,
                plan.step_count,
                protocol_name
            };
        }

        [[nodiscard]] constexpr TBridgeProtocolFrame frame() const noexcept
        {
            return TBridgeProtocolFrame{
                protocol_id,
                kind,
                status,
                session.view(),
                session.protocol_state.snapshot(to_string(kind)),
                has_next_step() ? current_step() : TBridgeProtocolStep{},
                current_step_index,
                plan.step_count,
                correlation
            };
        }

        [[nodiscard]] constexpr TBridgeProtocolTrace trace_current_step(
            std::string_view note = {}) const noexcept
        {
            if (!has_next_step())
            {
                return TBridgeProtocolTrace{};
            }

            const auto step = current_step();

            return TBridgeProtocolTrace::make(
                protocol_id,
                session.session_id,
                step.from,
                step.to,
                step.step_name,
                correlation,
                note);
        }

        constexpr bool activate() noexcept
        {
            if (!is_ready())
            {
                return false;
            }

            status = TBridgeProtocolStatus::active;
            last_result = TBridgeProtocolResult::active(protocol_id, correlation);
            return true;
        }

        constexpr TBridgeProtocolResult advance_model_step() noexcept
        {
            if (status == TBridgeProtocolStatus::ready)
            {
                if (!activate())
                {
                    last_result = TBridgeProtocolResult::fail(
                        protocol_id,
                        TBridgeError::make(
                            TBridgeErrorCode::protocol_violation,
                            "protocol is not ready"),
                        correlation);
                    return last_result;
                }
            }

            if (!is_active() || !has_next_step())
            {
                last_result = TBridgeProtocolResult::fail(
                    protocol_id,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "protocol cannot advance"),
                    correlation);
                status = TBridgeProtocolStatus::failed;
                return last_result;
            }

            const auto step = current_step();

            if (session.protocol_state.current_stage != step.from)
            {
                last_result = TBridgeProtocolResult::fail(
                    protocol_id,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "protocol state does not match the current step"),
                    correlation);
                status = TBridgeProtocolStatus::failed;
                session.protocol_state.complete(last_result.bridge_result);
                return last_result;
            }

            const bool transitioned = session.protocol_state.apply_transition(
                TBridgeTransition::make(step.from, step.to, step.step_name));

            if (!transitioned)
            {
                last_result = TBridgeProtocolResult::fail(
                    protocol_id,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "protocol transition was rejected by protocol state"),
                    correlation);
                status = TBridgeProtocolStatus::failed;
                session.protocol_state.complete(last_result.bridge_result);
                return last_result;
            }

            ++current_step_index;

            if (current_step_index >= plan.step_count)
            {
                status = TBridgeProtocolStatus::completed;
                session.status = TSessionStatus::completed;
                session.protocol_state.complete(TBridgeResult::success(correlation));
                last_result = TBridgeProtocolResult::completed(protocol_id, correlation);
                return last_result;
            }

            last_result = TBridgeProtocolResult::active(protocol_id, correlation);
            return last_result;
        }

        constexpr bool reject(TBridgeError reason) noexcept
        {
            if (!is_valid() || is_terminal())
            {
                return false;
            }

            status = TBridgeProtocolStatus::rejected;
            session.reject(reason);
            last_result = TBridgeProtocolResult::reject(protocol_id, reason, correlation);
            return true;
        }

        constexpr bool fail(TBridgeError reason) noexcept
        {
            if (!is_valid() || is_terminal())
            {
                return false;
            }

            status = TBridgeProtocolStatus::failed;
            session.status = TSessionStatus::failed;
            session.protocol_state.complete(TBridgeResult::fail(reason, correlation));
            last_result = TBridgeProtocolResult::fail(protocol_id, reason, correlation);
            return true;
        }

        [[nodiscard]] static constexpr TBridgeProtocol declare(
            TBridgeProtocolId id,
            TSession open_session,
            TBridgeProtocolPlan<PlanCapacity> protocol_plan,
            std::string_view name = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            const bool declaration_valid =
                id.is_valid()
                && open_session.is_open()
                && protocol_plan.is_valid()
                && protocol_plan.first_step().from == open_session.protocol_state.current_stage;

            if (!declaration_valid)
            {
                TBridgeProtocol protocol{
                    id,
                    protocol_plan.kind,
                    open_session,
                    protocol_plan,
                    0u,
                    TBridgeProtocolStatus::rejected,
                    TBridgeProtocolResult::reject(
                        id,
                        TBridgeError::make(
                            TBridgeErrorCode::protocol_violation,
                            "protocol declaration is invalid"),
                        token),
                    token,
                    name
                };

                return protocol;
            }

            return TBridgeProtocol{
                id,
                protocol_plan.kind,
                open_session,
                protocol_plan,
                0u,
                TBridgeProtocolStatus::ready,
                TBridgeProtocolResult::ready(id, token),
                token,
                name
            };
        }
    };
}
