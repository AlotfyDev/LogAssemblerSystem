#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/protocol_state/lifecycle/TBridgeProtocolState.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocol_state/transitions/TBridgeTransition.hpp"
#include "assembler/communication_context/sessions/requests/TSessionOpenRequest.hpp"
#include "assembler/communication_context/sessions/results/TSessionResult.hpp"
#include "assembler/communication_context/sessions/snapshots/TSessionSnapshot.hpp"
#include "assembler/communication_context/sessions/views/TSessionView.hpp"

/**
 * @file TSession.hpp
 * @brief Bridge-visible session declaration and lifecycle value.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Session Model for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - authoritative session value joining session identity, binding,
 *   compatibility snapshot, policy, bridge-visible protocol state, status,
 *   and correlation;
 * - future source for session registries, protocol bootstrap gates, bridge
 *   orchestration planning, diagnostics, and channel-session indexes;
 * - strict separation between session declaration/lifecycle metadata and
 *   actual protocol or endpoint execution.
 *
 * @section ascc_current_wave Current W08 Implementation Scope
 * This W08 version intentionally implements only session identity, opening
 * request, lifecycle status, snapshot/view/result, and declaration-level
 * session state around a compatible binding. It may hold protocol state as
 * bridge-visible lifecycle metadata, but it does not execute protocol steps,
 * orchestrate bridges, invoke endpoints, allocate endpoint resources, or own
 * endpoint lifecycle.
 *
 * - open-from-request factory;
 * - read-only view and snapshot helpers;
 * - bridge-visible lifecycle helpers for activation and terminal closure;
 * - no protocol stepping, no endpoint invocation, and no bridge loop.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - protocol execution or protocol stepping;
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, or thread ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - real transport session, network session, web session, or endpoint resource.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Session model headers may depend on W01 carriers/results/errors, W02
 * protocol-state foundations, W06 binding model, and W07 compatibility model.
 * They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TSession final
    {
        TSessionId session_id{TSessionId::invalid()};
        TBinding binding{};
        TSessionPolicy policy{};
        TCompatibilityView compatibility{};
        TBridgeProtocolState protocol_state{};
        TSessionStatus status{TSessionStatus::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view session_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            const bool base_valid = session_id.is_valid()
                && policy.is_valid()
                && status != TSessionStatus::unknown;

            if (!base_valid)
            {
                return false;
            }

            if (status == TSessionStatus::rejected
                || status == TSessionStatus::failed
                || status == TSessionStatus::deferred)
            {
                return protocol_state.snapshot("session_model").is_valid();
            }

            return binding.is_valid()
                && compatibility.binding.is_valid();
        }

        [[nodiscard]] constexpr bool is_open() const noexcept
        {
            return is_valid()
                && is_open_session_status(status)
                && !protocol_state.has_error();
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_session_status(status)
                || protocol_state.is_terminal();
        }

        [[nodiscard]] constexpr bool can_activate() const noexcept
        {
            return is_valid()
                && status == TSessionStatus::open
                && !protocol_state.is_terminal();
        }

        [[nodiscard]] constexpr TSessionView view() const noexcept
        {
            if (!is_valid())
            {
                return TSessionView::invalid();
            }

            return TSessionView{
                session_id,
                binding.binding_id,
                status,
                correlation,
                session_name
            };
        }

        [[nodiscard]] constexpr TSessionSnapshot snapshot() const noexcept
        {
            return TSessionSnapshot{
                session_id,
                status,
                binding.view(),
                compatibility,
                protocol_state.snapshot("session_model"),
                correlation,
                session_name
            };
        }

        [[nodiscard]] constexpr TSessionResult result() const noexcept
        {
            if (!is_valid())
            {
                return TSessionResult::fail(
                    session_id,
                    TBridgeError::make(
                        TBridgeErrorCode::internal_error,
                        "session is invalid"),
                    correlation);
            }

            if (status == TSessionStatus::open
                || status == TSessionStatus::active
                || status == TSessionStatus::completed)
            {
                return TSessionResult{
                    session_id,
                    status,
                    TBridgeResult::success(correlation)
                };
            }

            if (status == TSessionStatus::rejected)
            {
                return TSessionResult::reject(
                    session_id,
                    TBridgeError::make(
                        TBridgeErrorCode::incompatible_binding,
                        "session was rejected"),
                    correlation);
            }

            if (status == TSessionStatus::deferred)
            {
                return TSessionResult::defer(
                    session_id,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "session was deferred"),
                    correlation);
            }

            return TSessionResult::fail(
                session_id,
                TBridgeError::make(
                    TBridgeErrorCode::internal_error,
                    "session failed or is not open"),
                correlation);
        }

        constexpr bool activate() noexcept
        {
            if (!can_activate())
            {
                return false;
            }

            const auto transitioned = protocol_state.apply_transition(
                TBridgeTransition::make(
                    protocol_state.current_stage,
                    TBridgeStage::session_opening,
                    "session activated"));

            if (!transitioned)
            {
                return false;
            }

            status = TSessionStatus::active;
            return true;
        }

        constexpr bool complete() noexcept
        {
            if (!is_valid() || is_terminal())
            {
                return false;
            }

            status = TSessionStatus::completed;
            protocol_state.complete(TBridgeResult::success(correlation));
            return true;
        }

        constexpr bool reject(TBridgeError reason) noexcept
        {
            if (!is_valid() || is_terminal())
            {
                return false;
            }

            status = TSessionStatus::rejected;
            protocol_state.complete(TBridgeResult::reject(reason, correlation));
            return true;
        }

        [[nodiscard]] static constexpr TSession open(
            TSessionOpenRequest request) noexcept
        {
            if (!request.is_openable())
            {
                auto rejected_state = TBridgeProtocolState::start(request.correlation);
                rejected_state.complete(
                    TBridgeResult::reject(
                        TBridgeError::make(
                            TBridgeErrorCode::incompatible_binding,
                            "session open request is not compatible"),
                        request.correlation));

                return TSession{
                    request.session_id,
                    request.binding,
                    request.policy,
                    request.compatibility,
                    rejected_state,
                    TSessionStatus::rejected,
                    request.correlation,
                    request.session_name
                };
            }

            auto state = TBridgeProtocolState::start(request.correlation);
            state.apply_transition(
                TBridgeTransition::make(
                    TBridgeStage::idle,
                    TBridgeStage::session_opening,
                    "session opened from compatible binding"));

            return TSession{
                request.session_id,
                request.binding,
                request.policy,
                request.compatibility,
                state,
                TSessionStatus::open,
                request.correlation,
                request.session_name
            };
        }
    };
}