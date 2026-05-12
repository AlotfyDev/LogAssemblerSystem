#pragma once

#include "assembler/communication_context/bridge_core/frames/TBridgeCoreFrame.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"
#include "assembler/communication_context/bridge_core/traces/TBridgeCoreTrace.hpp"

/**
 * @file TBridgeCoreStepReport.hpp
 * @brief Bridge Core single-step report.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - deterministic report for one endpoint-neutral bridge step;
 * - future use in diagnostics, bounded runs, validation reports, and trace
 *   review;
 * - no persistence, telemetry, or endpoint execution ownership.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - before/after frames, bridge result, and optional trace;
 * - success/completion helpers.
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
 * - runtime event bus or durable execution report.
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
    struct TBridgeCoreStepReport final
    {
        TBridgeCoreFrame before{};
        TBridgeCoreFrame after{};
        TBridgeCoreResult result{};
        TBridgeCoreTrace trace{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return before.is_valid()
                && after.is_valid()
                && result.bridge_id == before.bridge_id
                && result.bridge_id == after.bridge_id;
        }

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return result.succeeded();
        }

        [[nodiscard]] constexpr bool completed() const noexcept
        {
            return result.completed();
        }
    };
}
