#pragma once

#include <string_view>

/**
 * @file TBridgeRunMode.hpp
 * @brief Bridge Core run-mode taxonomy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - stable run-mode vocabulary for manual stepping, bounded model run,
 *   single-pass run, and future orchestrated modes;
 * - explicit distinction between endpoint-neutral bridge model advancement and
 *   real runtime scheduling;
 * - textual conversion for diagnostics and configuration views.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - enum class `TBridgeRunMode`;
 * - bounded/manual helper classifications;
 * - textual conversion helper.
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
 * - runtime scheduler configuration or async executor policy.
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
    enum class TBridgeRunMode
    {
        unknown,
        manual_step,
        bounded_model_run,
        single_pass_model_run,
        diagnostic_dry_run
    };

    [[nodiscard]] constexpr bool is_bounded_run_mode(
        TBridgeRunMode mode) noexcept
    {
        return mode == TBridgeRunMode::bounded_model_run
            || mode == TBridgeRunMode::single_pass_model_run
            || mode == TBridgeRunMode::diagnostic_dry_run;
    }

    [[nodiscard]] constexpr bool is_manual_run_mode(
        TBridgeRunMode mode) noexcept
    {
        return mode == TBridgeRunMode::manual_step;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBridgeRunMode mode) noexcept
    {
        switch (mode)
        {
            case TBridgeRunMode::unknown: return "unknown";
            case TBridgeRunMode::manual_step: return "manual_step";
            case TBridgeRunMode::bounded_model_run: return "bounded_model_run";
            case TBridgeRunMode::single_pass_model_run: return "single_pass_model_run";
            case TBridgeRunMode::diagnostic_dry_run: return "diagnostic_dry_run";
        }

        return "unknown";
    }
}
