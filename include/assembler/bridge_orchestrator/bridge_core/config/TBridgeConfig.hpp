#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/budget/TBridgeStepBudget.hpp"
#include "assembler/communication_context/bridge_core/config/TBridgeRunMode.hpp"

/**
 * @file TBridgeConfig.hpp
 * @brief Bridge Core endpoint-neutral configuration.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - stable configuration surface for bridge model execution policy;
 * - future extension point for diagnostics, trace capture, strict checks,
 *   run-mode control, and step budget;
 * - no runtime scheduler, persistence, telemetry, or endpoint policy ownership.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - run mode, budget, diagnostic/trace flags, strict mode, and name;
 * - validity and diagnostic helpers;
 * - manual, bounded, and single-pass factories.
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
 * - concrete runtime executor configuration.
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
    struct TBridgeConfig final
    {
        TBridgeRunMode run_mode{TBridgeRunMode::unknown};
        TBridgeStepBudget budget{};
        bool require_ready_protocol{true};
        bool collect_diagnostic_snapshot{true};
        bool collect_trace_frame{true};
        bool strict_terminal_consistency{true};
        std::string_view config_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return run_mode != TBridgeRunMode::unknown
                && budget.is_valid();
        }

        [[nodiscard]] constexpr bool should_collect_diagnostics() const noexcept
        {
            return collect_diagnostic_snapshot || collect_trace_frame;
        }

        [[nodiscard]] static constexpr TBridgeConfig manual_step(
            std::string_view name = "manual_step_bridge_config") noexcept
        {
            return TBridgeConfig{
                TBridgeRunMode::manual_step,
                TBridgeStepBudget::single_step(),
                true,
                true,
                true,
                true,
                name
            };
        }

        [[nodiscard]] static constexpr TBridgeConfig bounded_model_run(
            std::uint32_t max_steps,
            std::string_view name = "bounded_model_run_bridge_config") noexcept
        {
            return TBridgeConfig{
                TBridgeRunMode::bounded_model_run,
                TBridgeStepBudget::finite(max_steps),
                true,
                true,
                true,
                true,
                name
            };
        }

        [[nodiscard]] static constexpr TBridgeConfig single_pass_model_run(
            std::string_view name = "single_pass_model_run_bridge_config") noexcept
        {
            return TBridgeConfig{
                TBridgeRunMode::single_pass_model_run,
                TBridgeStepBudget::finite(1u),
                true,
                true,
                true,
                true,
                name
            };
        }

        [[nodiscard]] static constexpr TBridgeConfig diagnostic_dry_run(
            std::uint32_t max_steps,
            std::string_view name = "diagnostic_dry_run_bridge_config") noexcept
        {
            return TBridgeConfig{
                TBridgeRunMode::diagnostic_dry_run,
                TBridgeStepBudget::finite(max_steps),
                true,
                true,
                true,
                true,
                name
            };
        }
    };
}
