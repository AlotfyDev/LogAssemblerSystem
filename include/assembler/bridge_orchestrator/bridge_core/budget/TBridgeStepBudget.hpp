#pragma once

#include <cstdint>

/**
 * @file TBridgeStepBudget.hpp
 * @brief Bridge Core step-budget value.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - deterministic bound for endpoint-neutral bridge model advancement;
 * - future protection against accidental unbounded loops;
 * - independent from timeouts, threads, schedulers, and runtime clocks.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - maximum step count and consumed step count;
 * - consume/remain/exhausted helpers;
 * - static finite and single-step factories.
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
 * - clock timeout, scheduling quantum, or async cancellation token.
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
    struct TBridgeStepBudget final
    {
        std::uint32_t max_steps{0u};
        std::uint32_t consumed_steps{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return max_steps > 0u;
        }

        [[nodiscard]] constexpr bool exhausted() const noexcept
        {
            return !is_valid() || consumed_steps >= max_steps;
        }

        [[nodiscard]] constexpr std::uint32_t remaining() const noexcept
        {
            return consumed_steps >= max_steps
                ? 0u
                : max_steps - consumed_steps;
        }

        constexpr bool consume_one() noexcept
        {
            if (exhausted())
            {
                return false;
            }

            ++consumed_steps;
            return true;
        }

        [[nodiscard]] static constexpr TBridgeStepBudget finite(
            std::uint32_t maximum_steps) noexcept
        {
            return TBridgeStepBudget{maximum_steps, 0u};
        }

        [[nodiscard]] static constexpr TBridgeStepBudget single_step() noexcept
        {
            return TBridgeStepBudget{1u, 0u};
        }
    };
}
