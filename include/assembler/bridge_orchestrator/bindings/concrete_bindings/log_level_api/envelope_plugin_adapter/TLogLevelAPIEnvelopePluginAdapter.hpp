#pragma once

#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/contracts/TPluginAdapter.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/carriers/TLogLevelEnvelopeDescriptor.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/config/TLogLevelAPIEnvelopePluginAdapterConfig.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/policies/TLogLevelAPIEnvelopePluginAdapterReadinessPolicy.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/state/TLogLevelAPIEnvelopePluginAdapterState.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/views/TLogLevelAPIEnvelopePluginAdapterViewBuilder.hpp"

/**
 * @file TLogLevelAPIEnvelopePluginAdapter.hpp
 * @brief Concrete content-side plugin adapter for Log Level API envelope placement.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - concrete adapter that satisfies W05 `TPluginAdapter` obligations for a
 *   prepared Log Level Envelope descriptor;
 * - future bridge between Log Level API envelope assembly and Write Side
 *   placement ports;
 * - strict boundary that adapts only a descriptor and does not own envelope
 *   assembly, validation, metadata, timestamp, or write-side placement.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - CRTP inheritance from `TPluginAdapter<TLogLevelAPIEnvelopePluginAdapter>`;
 * - readiness, placement-request preparation, placement-handle acceptance,
 *   load-signal emission, and next-destination request production;
 * - local descriptor/config/state only.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - Log Level API facade implementation;
 * - Envelope Assembler internals;
 * - content validation internals;
 * - metadata injection or timestamp stabilization internals;
 * - Write Side placement port implementation;
 * - Write Side slot/container/round internals;
 * - bridge orchestration beyond W10 model stepping;
 * - registry, database, persistence, telemetry, scheduler, thread, or ABI behavior;
 * - dynamic plugin loading or runtime dependency injection.
 * - concrete host port, binding execution, or actual envelope memory movement.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14A concrete adapter headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPluginAdapter` obligations, and W10 aggregate bridge
 * surfaces for smoke-test compatibility. They must not include concrete
 * `assembler/log_level_api/...` or `assembler/write_side/...` endpoint-domain
 * internals until those domains are separately realized and explicitly bridged.
 */

namespace assembler::communication_context
{
    class TLogLevelAPIEnvelopePluginAdapter final
        : public TPluginAdapter<TLogLevelAPIEnvelopePluginAdapter>
    {
    public:
        constexpr TLogLevelAPIEnvelopePluginAdapter(
            TLogLevelEnvelopeDescriptor descriptor,
            TLogLevelAPIEnvelopePluginAdapterConfig config =
                TLogLevelAPIEnvelopePluginAdapterConfig::defaults()) noexcept
            : descriptor_(descriptor),
              config_(config),
              state_()
        {
        }

        [[nodiscard]] constexpr const TLogLevelEnvelopeDescriptor& descriptor() const noexcept
        {
            return descriptor_;
        }

        [[nodiscard]] constexpr const TLogLevelAPIEnvelopePluginAdapterConfig& config() const noexcept
        {
            return config_;
        }

        [[nodiscard]] constexpr const TLogLevelAPIEnvelopePluginAdapterState& state() const noexcept
        {
            return state_;
        }

        [[nodiscard]] constexpr TPluginAdapterView view() const noexcept
        {
            return TLogLevelAPIEnvelopePluginAdapterViewBuilder::view(
                config_,
                descriptor_.correlation);
        }

        [[nodiscard]] constexpr TReadinessView readiness() noexcept
        {
            if (!config_.is_valid())
            {
                return TReadinessView::not_ready(
                    "log_level_api_envelope_plugin_adapter_config_invalid",
                    descriptor_.correlation);
            }

            if (!TLogLevelAPIEnvelopePluginAdapterReadinessPolicy::descriptor_is_ready(descriptor_))
            {
                return TReadinessView::not_ready(
                    "log_level_envelope_descriptor_invalid",
                    descriptor_.correlation);
            }

            return TReadinessView::ready(
                descriptor_.correlation,
                TLogLevelAPIEnvelopePluginAdapterReadinessPolicy::readiness_capacity_hint(descriptor_));
        }

        [[nodiscard]] constexpr TPlacementRequest prepare_placement_request() noexcept
        {
            if (!descriptor_.is_valid())
            {
                return TPlacementRequest{};
            }

            return TPlacementRequest::make(
                descriptor_.correlation,
                descriptor_.envelope_kind,
                descriptor_.payload_size_hint,
                descriptor_.requires_ordered_placement,
                descriptor_.requested_destination_family.empty()
                    ? config_.requested_destination_family
                    : descriptor_.requested_destination_family);
        }

        [[nodiscard]] constexpr TBridgeResult accept_placement_handle(
            const TPlacementHandle& handle) noexcept
        {
            if (!handle.is_valid())
            {
                return TBridgeResult::fail(
                    TBridgeError::make(
                        TBridgeErrorCode::handle_unavailable,
                        "placement handle is invalid"),
                    descriptor_.correlation);
            }

            if (handle.correlation != descriptor_.correlation)
            {
                return TBridgeResult::reject(
                    TBridgeError::make(
                        TBridgeErrorCode::invalid_correlation,
                        "placement handle correlation does not match descriptor correlation"),
                    descriptor_.correlation);
            }

            state_.accept_handle(handle);
            return TBridgeResult::success(descriptor_.correlation);
        }

        [[nodiscard]] constexpr TLoadSignal emit_load_signal() noexcept
        {
            if (!state_.has_accepted_handle())
            {
                return TLoadSignal::failed(
                    descriptor_.correlation,
                    TPlacementHandle::invalid(),
                    "placement handle has not been accepted");
            }

            auto signal = TLoadSignal::completed(
                descriptor_.correlation,
                state_.accepted_handle,
                descriptor_.payload_size_hint);

            state_.mark_load_signal_emitted();
            return signal;
        }

        [[nodiscard]] constexpr TNextDestinationRequest next_destination_request() noexcept
        {
            return TNextDestinationRequest::make(
                descriptor_.correlation,
                state_.accepted_handle,
                state_.has_accepted_handle()
                    ? TNextDestinationReason::continuous_flow_requested
                    : TNextDestinationReason::retry_requested,
                state_.has_accepted_handle()
                    ? "continue_after_log_level_envelope_load"
                    : "retry_after_missing_placement_handle");
        }

        constexpr void reset_state() noexcept
        {
            state_.reset();
        }

    private:
        TLogLevelEnvelopeDescriptor descriptor_{};
        TLogLevelAPIEnvelopePluginAdapterConfig config_{};
        TLogLevelAPIEnvelopePluginAdapterState state_{};
    };
}
