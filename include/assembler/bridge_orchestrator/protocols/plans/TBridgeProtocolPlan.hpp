#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/steps/TBridgeProtocolStep.hpp"

/**
 * @file TBridgeProtocolPlan.hpp
 * @brief Fixed-capacity bridge protocol plan.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - deterministic endpoint-neutral protocol plan composed of declared
 *   protocol steps;
 * - future support for protocol catalogs, bridge setup validation, diagnostic
 *   plans, and session-to-protocol bootstrap;
 * - strict separation from concrete execution and endpoint invocation.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - fixed-capacity step array;
 * - add/validate/count helpers;
 * - standard envelope-placement plan factory.
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
 * - dynamic protocol registry or executable runtime pipeline.
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
    template <std::size_t Capacity>
    struct TBridgeProtocolPlan final
    {
        TBridgeProtocolKind kind{TBridgeProtocolKind::unknown};
        std::array<TBridgeProtocolStep, Capacity> steps{};
        std::size_t step_count{0u};
        std::string_view plan_name{};

        [[nodiscard]] constexpr bool has_valid_kind() const noexcept
        {
            return kind != TBridgeProtocolKind::unknown;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return step_count == 0u;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return step_count >= Capacity;
        }

        constexpr bool add(TBridgeProtocolStep step) noexcept
        {
            if (full() || !step.is_valid())
            {
                return false;
            }

            steps[step_count] = step;
            ++step_count;
            return true;
        }

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            if (!has_valid_kind() || empty())
            {
                return false;
            }

            for (std::size_t index = 0u; index < step_count; ++index)
            {
                if (!steps[index].is_valid())
                {
                    return false;
                }

                if (index > 0u && steps[index - 1u].to != steps[index].from)
                {
                    return false;
                }
            }

            return true;
        }

        [[nodiscard]] constexpr const TBridgeProtocolStep& step_at(
            std::size_t index) const noexcept
        {
            return steps[index];
        }

        [[nodiscard]] constexpr const TBridgeProtocolStep& first_step() const noexcept
        {
            return steps[0u];
        }

        [[nodiscard]] constexpr const TBridgeProtocolStep& last_step() const noexcept
        {
            return steps[step_count - 1u];
        }

        [[nodiscard]] constexpr bool ends_terminally() const noexcept
        {
            return is_valid() && last_step().is_terminal_step();
        }

        [[nodiscard]] static constexpr TBridgeProtocolPlan<12> envelope_placement_plan() noexcept
        {
            TBridgeProtocolPlan<12> plan{
                TBridgeProtocolKind::envelope_placement,
                {},
                0u,
                "envelope_placement_protocol_plan"
            };

            plan.add(TBridgeProtocolStep::make(
                1u,
                TBridgeStage::session_opening,
                TBridgeStage::channel_resolution,
                "resolve_channel"));

            plan.add(TBridgeProtocolStep::make(
                2u,
                TBridgeStage::channel_resolution,
                TBridgeStage::binding_resolution,
                "resolve_binding"));

            plan.add(TBridgeProtocolStep::make(
                3u,
                TBridgeStage::binding_resolution,
                TBridgeStage::compatibility_check,
                "check_compatibility"));

            plan.add(TBridgeProtocolStep::make(
                4u,
                TBridgeStage::compatibility_check,
                TBridgeStage::adapter_readiness,
                "check_adapter_readiness"));

            plan.add(TBridgeProtocolStep::make(
                5u,
                TBridgeStage::adapter_readiness,
                TBridgeStage::request_preparation,
                "prepare_request"));

            plan.add(TBridgeProtocolStep::make(
                6u,
                TBridgeStage::request_preparation,
                TBridgeStage::port_readiness,
                "check_port_readiness"));

            plan.add(TBridgeProtocolStep::make(
                7u,
                TBridgeStage::port_readiness,
                TBridgeStage::admission_request,
                "request_admission"));

            plan.add(TBridgeProtocolStep::make(
                8u,
                TBridgeStage::admission_request,
                TBridgeStage::admission_result,
                "receive_admission"));

            plan.add(TBridgeProtocolStep::make(
                9u,
                TBridgeStage::admission_result,
                TBridgeStage::handle_exchange,
                "exchange_handle"));

            plan.add(TBridgeProtocolStep::make(
                10u,
                TBridgeStage::handle_exchange,
                TBridgeStage::adapter_handle_acceptance,
                "adapter_accepts_handle"));

            plan.add(TBridgeProtocolStep::make(
                11u,
                TBridgeStage::adapter_handle_acceptance,
                TBridgeStage::load_or_delivery_signal,
                "load_or_delivery_signal"));

            plan.add(TBridgeProtocolStep::make(
                12u,
                TBridgeStage::load_or_delivery_signal,
                TBridgeStage::result_consolidation,
                "consolidate_result"));

            return plan;
        }
    };
}
