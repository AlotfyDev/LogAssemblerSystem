#pragma once

#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapterBinding.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/TWriteSideEnvelopePlacementPortBinding.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/config/TFirstIntegrationSkeletonConfig.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/plans/TFirstIntegrationSkeletonModelPlan.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/reports/TFirstIntegrationSkeletonReport.hpp"

/**
 * @file TFirstIntegrationSkeleton.hpp
 * @brief First end-to-end ASCC integration skeleton.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the first ASCC integration skeleton.
 * The final version should preserve:
 *
 * - primary W15 integration skeleton joining W14A and W14B;
 * - dependency-ordered model setup from channel to bridge;
 * - endpoint-neutral carrier-flow smoke path using adapter and port public
 *   surfaces only;
 * - structured report suitable for later integration waves.
 *
 * @section ascc_current_wave Current W15 Implementation Scope
 * This W15 version validates that W14A and W14B can be placed into the
 * existing W01-W10 Communication Context model as a coherent integration
 * skeleton. It intentionally remains a skeleton, not a production runtime.
 *
 * - constructs W14A adapter and W14B port;
 * - declares channel, binding, session, protocol, and bridge model;
 * - runs W10 model bridge to terminal;
 * - performs concrete carrier exchange through public adapter/port APIs.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete endpoint-domain internals;
 * - Write Side slot/container/round implementation;
 * - Log Level API envelope assembly, validation, metadata, or timestamp internals;
 * - runtime scheduling, threading, async execution, persistence, telemetry, ABI, or database behavior;
 * - replacing W09 protocol model or W10 bridge model-step orchestration;
 * - hiding bridge-visible failure/report states.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W15 may depend on W01-W10, W14A, and W14B public include surfaces.
 * It must not include concrete endpoint-domain headers such as
 * `assembler/log_level_api/...` or `assembler/write_side/...` internals.
 */

namespace assembler::communication_context
{
    class TFirstIntegrationSkeleton final
    {
    public:
        constexpr explicit TFirstIntegrationSkeleton(
            TFirstIntegrationSkeletonConfig config =
                TFirstIntegrationSkeletonConfig::defaults(),
            TCorrelationToken token =
                TCorrelationToken::from_parts(15u, 1u)) noexcept
            : config_(config),
              correlation_(token)
        {
        }

        [[nodiscard]] constexpr const TFirstIntegrationSkeletonConfig& config() const noexcept
        {
            return config_;
        }

        [[nodiscard]] constexpr TCorrelationToken correlation() const noexcept
        {
            return correlation_;
        }

        [[nodiscard]] constexpr TFirstIntegrationSkeletonReport run() const noexcept
        {
            TFirstIntegrationSkeletonReport report{};
            report.config_valid = config_.is_valid();

            if (!report.config_valid)
            {
                report.mark_failure("w15_config_invalid");
                return report;
            }

            auto adapter = TLogLevelAPIEnvelopePluginAdapterFactory::from_fields(
                correlation_,
                config_.envelope_id,
                config_.payload_size_hint);

            auto port = TWriteSideEnvelopePlacementPortFactory::make_default();

            report.adapter_view_valid = adapter.view().is_valid();
            report.port_view_valid = port.view().is_valid();

            if (!report.adapter_view_valid)
            {
                report.mark_failure("adapter_view_invalid");
                return report;
            }

            if (!report.port_view_valid)
            {
                report.mark_failure("port_view_invalid");
                return report;
            }

            const auto channel =
                TFirstIntegrationSkeletonModelPlan::declare_channel(
                    config_,
                    adapter,
                    port,
                    correlation_);
            report.channel_valid = channel.is_valid();

            if (!report.channel_valid)
            {
                report.mark_failure("channel_invalid");
                return report;
            }

            const auto surface_pair =
                TFirstIntegrationSkeletonModelPlan::make_surface_pair(adapter, port);
            report.surface_pair_valid = surface_pair.is_valid()
                && surface_pair.supports_primary_placement_flow();

            if (!report.surface_pair_valid)
            {
                report.mark_failure("surface_pair_invalid");
                return report;
            }

            const auto binding =
                TFirstIntegrationSkeletonModelPlan::declare_binding(
                    config_,
                    channel,
                    surface_pair,
                    correlation_);
            report.binding_compatible = binding.is_compatible();

            if (!report.binding_compatible)
            {
                report.mark_failure("binding_incompatible");
                return report;
            }

            const auto session =
                TFirstIntegrationSkeletonModelPlan::open_session(
                    config_,
                    binding,
                    correlation_);
            report.session_open = session.is_open();

            if (!report.session_open)
            {
                report.mark_failure("session_not_open");
                return report;
            }

            const auto protocol =
                TFirstIntegrationSkeletonModelPlan::declare_protocol(
                    config_,
                    session,
                    correlation_);
            report.protocol_ready = protocol.is_ready();

            if (!report.protocol_ready)
            {
                report.mark_failure("protocol_not_ready");
                return report;
            }

            auto bridge =
                TFirstIntegrationSkeletonModelPlan::declare_bridge(
                    config_,
                    protocol,
                    correlation_);
            report.bridge_declared = bridge.is_valid() && bridge.is_ready();

            if (!report.bridge_declared)
            {
                report.mark_failure("bridge_not_declared_ready");
                return report;
            }

            report.bridge_model_result = bridge.run_model_to_terminal();
            report.bridge_model_completed = report.bridge_model_result.completed();

            if (!report.bridge_model_completed)
            {
                report.mark_failure("bridge_model_not_completed");
                return report;
            }

            const auto adapter_readiness = adapter.readiness();
            report.adapter_ready = adapter_readiness.is_ready();

            if (!report.adapter_ready)
            {
                report.mark_failure("adapter_not_ready");
                return report;
            }

            const auto placement_request = adapter.prepare_placement_request();
            report.placement_request_valid = placement_request.is_valid();

            if (!report.placement_request_valid)
            {
                report.mark_failure("placement_request_invalid");
                return report;
            }

            const auto port_readiness = port.readiness(placement_request);
            report.port_ready = port_readiness.is_ready();

            if (!report.port_ready)
            {
                report.mark_failure("port_not_ready");
                return report;
            }

            report.admission = port.admit(placement_request);
            report.admission_accepted = report.admission.accepted();

            if (!report.admission_accepted)
            {
                report.mark_failure("admission_not_accepted");
                return report;
            }

            report.placement_handle = port.placement_handle(placement_request);
            report.placement_handle_valid = report.placement_handle.is_valid();

            if (!report.placement_handle_valid)
            {
                report.mark_failure("placement_handle_invalid");
                return report;
            }

            report.adapter_handle_result =
                adapter.accept_placement_handle(report.placement_handle);
            report.adapter_accepted_handle = report.adapter_handle_result.succeeded();

            if (!report.adapter_accepted_handle)
            {
                report.mark_failure("adapter_handle_not_accepted");
                return report;
            }

            const auto load_signal = adapter.emit_load_signal();
            report.load_signal_completed = load_signal.completed();

            if (!report.load_signal_completed)
            {
                report.mark_failure("load_signal_not_completed");
                return report;
            }

            report.load_signal_result = port.receive_load_signal(load_signal);
            report.port_received_load_signal = report.load_signal_result.succeeded();

            if (!report.port_received_load_signal)
            {
                report.mark_failure("port_did_not_receive_load_signal");
                return report;
            }

            const auto next_destination_request = adapter.next_destination_request();
            report.next_destination_result = port.next_destination(next_destination_request);
            report.next_destination_acknowledged = report.next_destination_result.succeeded();

            if (!report.next_destination_acknowledged)
            {
                report.mark_failure("next_destination_not_acknowledged");
                return report;
            }

            return report;
        }

    private:
        TFirstIntegrationSkeletonConfig config_{};
        TCorrelationToken correlation_{TCorrelationToken::invalid()};
    };
}
