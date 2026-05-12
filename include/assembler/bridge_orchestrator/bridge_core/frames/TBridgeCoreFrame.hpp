#pragma once

#include <cstdint>

#include "assembler/communication_context/bridge_core/budget/TBridgeStepBudget.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"
#include "assembler/communication_context/protocols/frames/TBridgeProtocolFrame.hpp"

/**
 * @file TBridgeCoreFrame.hpp
 * @brief Read-only current Bridge Core frame.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - compact bridge-level current-frame projection over a W09 protocol frame;
 * - future source for bridge diagnostics, registries, reports, and orchestration
 *   review;
 * - no endpoint handles or runtime scheduler state.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - bridge id, status, step budget, sequence index, and protocol frame;
 * - validity and terminal helpers.
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
 * - mutable orchestration context or endpoint call frame.
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
    struct TBridgeCoreFrame final
    {
        TBridgeId bridge_id{TBridgeId::invalid()};
        TBridgeStatus status{TBridgeStatus::unknown};
        TBridgeStepBudget budget{};
        std::uint32_t frame_index{0u};
        TBridgeProtocolFrame protocol_frame{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return bridge_id.is_valid()
                && status != TBridgeStatus::unknown
                && budget.is_valid()
                && protocol_frame.is_valid();
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_bridge_status(status)
                || protocol_frame.is_terminal();
        }
    };
}
