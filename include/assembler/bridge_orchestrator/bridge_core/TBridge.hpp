#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_core/config/TBridgeConfig.hpp"
#include "assembler/communication_context/bridge_core/frames/TBridgeCoreFrame.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/bridge_core/issues/TBridgeCoreIssue.hpp"
#include "assembler/communication_context/bridge_core/policies/TBridgeCorePolicy.hpp"
#include "assembler/communication_context/bridge_core/reports/TBridgeCoreStepReport.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"
#include "assembler/communication_context/bridge_core/snapshots/TBridgeCoreSnapshot.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"
#include "assembler/communication_context/bridge_core/traces/TBridgeCoreTrace.hpp"
#include "assembler/communication_context/bridge_core/views/TBridgeCoreView.hpp"
#include "assembler/communication_context/protocols/common/TBridgeProtocol.hpp"

/**
 * @file TBridge.hpp
 * @brief Endpoint-neutral Bridge Core value and model-step orchestrator.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - authoritative Bridge Core value that owns bridge identity, configuration,
 *   bridge status, step budget, a W09 protocol value, last result, and last
 *   issue;
 * - future parent for concrete bridge wiring while preserving endpoint-neutral
 *   model execution boundaries;
 * - deterministic model-step orchestration over W09 `TBridgeProtocol` without
 *   invoking concrete ports, plugin adapters, endpoints, schedulers, or IO.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - declaration factory from a ready W09 protocol and W10 config;
 * - view, frame, snapshot, trace, single-step report, and bounded-run helpers;
 * - endpoint-neutral `step_model_once` that delegates to W09 protocol model
 *   advancement only;
 * - no endpoint invocation and no runtime scheduling.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings;
 * - dynamic plugin loading or runtime dependency injection.
 * - concrete bridge executor or endpoint call wiring.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Core headers may depend on W01 carriers/results/errors, W02 protocol
 * state foundations, W08 session model through W09, and W09 bridge protocol
 * model. They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    template <std::size_t PlanCapacity>
    struct TBridge final
    {
        TBridgeId bridge_id{TBridgeId::invalid()};
        TBridgeConfig config{};
        TBridgeProtocol<PlanCapacity> protocol{};
        TBridgeStatus status{TBridgeStatus::unknown};
        TBridgeCoreResult last_result{};
        TBridgeCoreIssue last_issue{TBridgeCoreIssue::none()};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view bridge_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return bridge_id.is_valid()
                && config.is_valid()
                && protocol.is_valid()
                && status != TBridgeStatus::unknown;
        }

        [[nodiscard]] constexpr bool is_ready() const noexcept
        {
            return is_valid()
                && status == TBridgeStatus::ready
                && protocol.is_ready()
                && !config.budget.exhausted();
        }

        [[nodiscard]] constexpr bool is_running() const noexcept
        {
            return is_valid()
                && status == TBridgeStatus::running
                && !config.budget.exhausted();
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_bridge_status(status)
                || protocol.is_terminal();
        }

        [[nodiscard]] constexpr TBridgeCoreView view() const noexcept
        {
            if (!is_valid())
            {
                return TBridgeCoreView::invalid();
            }

            return TBridgeCoreView{
                bridge_id,
                protocol.protocol_id,
                status,
                config.budget.consumed_steps,
                config.budget.max_steps,
                correlation,
                bridge_name
            };
        }

        [[nodiscard]] constexpr TBridgeCoreFrame frame() const noexcept
        {
            return TBridgeCoreFrame{
                bridge_id,
                status,
                config.budget,
                config.budget.consumed_steps,
                protocol.frame()
            };
        }

        [[nodiscard]] constexpr TBridgeCoreSnapshot snapshot() const noexcept
        {
            return TBridgeCoreSnapshot{
                bridge_id,
                status,
                config,
                protocol.view(),
                frame(),
                last_issue,
                correlation,
                bridge_name
            };
        }

        [[nodiscard]] constexpr TBridgeCoreTrace trace_current_step(
            std::string_view note = {}) const noexcept
        {
            return TBridgeCoreTrace::make(
                bridge_id,
                status,
                protocol.trace_current_step(note),
                correlation,
                note);
        }

        constexpr TBridgeCoreResult step_model_once() noexcept
        {
            if (!is_valid())
            {
                last_issue = TBridgeCoreIssue::fatal(
                    TBridgeStatus::failed,
                    "bridge.invalid",
                    "bridge is invalid",
                    correlation);
                status = TBridgeStatus::failed;
                last_result = TBridgeCoreResult::failed(
                    bridge_id,
                    TBridgeError::make(
                        TBridgeErrorCode::internal_error,
                        "bridge is invalid"),
                    config.budget.consumed_steps,
                    correlation);
                return last_result;
            }

            if (is_terminal())
            {
                last_result = status == TBridgeStatus::completed
                    ? TBridgeCoreResult::completed(
                        bridge_id,
                        config.budget.consumed_steps,
                        correlation,
                        "bridge already completed")
                    : TBridgeCoreResult::failed(
                        bridge_id,
                        TBridgeError::make(
                            TBridgeErrorCode::protocol_violation,
                            "bridge is terminal"),
                        config.budget.consumed_steps,
                        correlation);
                return last_result;
            }

            if (config.budget.exhausted())
            {
                status = TBridgeStatus::exhausted;
                last_issue = TBridgeCoreIssue::block(
                    status,
                    "bridge.budget.exhausted",
                    "bridge step budget exhausted",
                    correlation);
                last_result = TBridgeCoreResult::exhausted_budget(
                    bridge_id,
                    config.budget.consumed_steps,
                    correlation);
                return last_result;
            }

            if (status == TBridgeStatus::ready)
            {
                status = TBridgeStatus::running;
            }

            if (status != TBridgeStatus::running)
            {
                last_issue = TBridgeCoreIssue::block(
                    status,
                    "bridge.status.not_runnable",
                    "bridge status is not runnable",
                    correlation);
                last_result = TBridgeCoreResult::failed(
                    bridge_id,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "bridge status is not runnable"),
                    config.budget.consumed_steps,
                    correlation);
                status = TBridgeStatus::failed;
                return last_result;
            }

            const bool consumed = config.budget.consume_one();

            if (!consumed)
            {
                status = TBridgeStatus::exhausted;
                last_issue = TBridgeCoreIssue::block(
                    status,
                    "bridge.budget.exhausted",
                    "bridge step budget exhausted",
                    correlation);
                last_result = TBridgeCoreResult::exhausted_budget(
                    bridge_id,
                    config.budget.consumed_steps,
                    correlation);
                return last_result;
            }

            const auto protocol_result = protocol.advance_model_step();

            if (protocol_result.failed())
            {
                status = TBridgeStatus::failed;
                last_issue = TBridgeCoreIssue::block(
                    status,
                    "bridge.protocol.step_failed",
                    protocol_result.note,
                    correlation);
                last_result = TBridgeCoreResult::failed(
                    bridge_id,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        protocol_result.note),
                    config.budget.consumed_steps,
                    correlation);
                return last_result;
            }

            if (protocol_result.rejected())
            {
                status = TBridgeStatus::rejected;
                last_issue = TBridgeCoreIssue::block(
                    status,
                    "bridge.protocol.step_rejected",
                    protocol_result.note,
                    correlation);
                last_result = TBridgeCoreResult::rejected(
                    bridge_id,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        protocol_result.note),
                    correlation);
                return last_result;
            }

            if (protocol.status == TBridgeProtocolStatus::completed)
            {
                status = TBridgeStatus::completed;
                last_result = TBridgeCoreResult::completed(
                    bridge_id,
                    config.budget.consumed_steps,
                    correlation);
                return last_result;
            }

            last_result = TBridgeCoreResult::running(
                bridge_id,
                config.budget.consumed_steps,
                correlation);
            return last_result;
        }

        constexpr TBridgeCoreStepReport step_model_report() noexcept
        {
            const auto before = frame();
            const auto trace = trace_current_step("before_model_step");
            const auto result = step_model_once();
            const auto after = frame();

            return TBridgeCoreStepReport{
                before,
                after,
                result,
                trace
            };
        }

        constexpr TBridgeCoreResult run_model_to_terminal() noexcept
        {
            if (!is_valid())
            {
                return step_model_once();
            }

            while (!is_terminal() && !config.budget.exhausted())
            {
                const auto result = step_model_once();

                if (result.failed() || result.rejected() || result.exhausted())
                {
                    return result;
                }

                if (result.completed())
                {
                    return result;
                }
            }

            if (status == TBridgeStatus::completed)
            {
                return last_result;
            }

            status = TBridgeStatus::exhausted;
            last_issue = TBridgeCoreIssue::block(
                status,
                "bridge.budget.exhausted",
                "bridge model run exhausted before terminal completion",
                correlation);
            last_result = TBridgeCoreResult::exhausted_budget(
                bridge_id,
                config.budget.consumed_steps,
                correlation);
            return last_result;
        }

        [[nodiscard]] static constexpr TBridge declare(
            TBridgeId id,
            TBridgeProtocol<PlanCapacity> ready_protocol,
            TBridgeConfig bridge_config,
            std::string_view name = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            const auto issue = TBridgeCorePolicy::check_declaration(
                id,
                bridge_config,
                ready_protocol,
                token);

            if (issue.is_present())
            {
                return TBridge{
                    id,
                    bridge_config,
                    ready_protocol,
                    issue.bridge_status == TBridgeStatus::unknown
                        ? TBridgeStatus::rejected
                        : issue.bridge_status,
                    TBridgeCoreResult::rejected(
                        id,
                        TBridgeError::make(
                            TBridgeErrorCode::protocol_violation,
                            issue.message),
                        token),
                    issue,
                    token,
                    name
                };
            }

            return TBridge{
                id,
                bridge_config,
                ready_protocol,
                TBridgeStatus::ready,
                TBridgeCoreResult::ready(id, token),
                TBridgeCoreIssue::none(),
                token,
                name
            };
        }
    };
}
