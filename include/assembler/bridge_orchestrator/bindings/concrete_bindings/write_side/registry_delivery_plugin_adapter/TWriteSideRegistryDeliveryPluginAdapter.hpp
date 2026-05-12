#pragma once

#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/carriers/TWriteSideRegistryDeliveryMaterialDescriptor.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/config/TWriteSideRegistryDeliveryPluginAdapterConfig.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/policies/TWriteSideRegistryDeliveryReadinessPolicy.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/state/TWriteSideRegistryDeliveryPluginAdapterState.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/views/TWriteSideRegistryDeliveryPluginAdapterViewBuilder.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/contracts/TPluginAdapter.hpp"

/**
 * @file TWriteSideRegistryDeliveryPluginAdapter.hpp
 * @brief Concrete Write Side PluginAdapter for registry-delivery material.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - W05 `TPluginAdapter` concrete surface for Write Side content-provider
 *   delivery material;
 * - W13-compatible boundary handoff request helper;
 * - state transitions for placement handle, load signal, and optional boundary
 *   handoff result tracking;
 * - no downstream registry implementation.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - implements view/readiness/prepare_placement_request/
 *   accept_placement_handle/emit_load_signal/next_destination_request;
 * - exposes prepare_boundary_handoff_request and boundary result acceptance
 *   helpers;
 * - no endpoint include dependencies.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - the downstream Log Level Records Registry;
 * - persistence, database, file IO, network IO, telemetry export, or logging
 *   sinks;
 * - Write Side slot, slots container, round manager, dispatcher, or reference
 *   precalculator internals;
 * - registry delivery port implementation;
 * - bridge runtime scheduling or endpoint invocation wiring;
 * - downstream lifecycle ownership after handoff.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14C may depend on W01-W13 public Communication Context surfaces.
 * It must not include concrete `assembler/write_side/...` or downstream
 * registry internals.
 */

namespace assembler::communication_context
{
    class TWriteSideRegistryDeliveryPluginAdapter final
        : public TPluginAdapter<TWriteSideRegistryDeliveryPluginAdapter>
    {
    public:
        constexpr TWriteSideRegistryDeliveryPluginAdapter(
            TWriteSideRegistryDeliveryMaterialDescriptor descriptor,
            TWriteSideRegistryDeliveryPluginAdapterConfig config =
                TWriteSideRegistryDeliveryPluginAdapterConfig::defaults()) noexcept
            : descriptor_(descriptor),
              config_(config),
              state_()
        {
        }

        [[nodiscard]] constexpr const TWriteSideRegistryDeliveryMaterialDescriptor& descriptor() const noexcept
        {
            return descriptor_;
        }

        [[nodiscard]] constexpr const TWriteSideRegistryDeliveryPluginAdapterConfig& config() const noexcept
        {
            return config_;
        }

        [[nodiscard]] constexpr const TWriteSideRegistryDeliveryPluginAdapterState& state() const noexcept
        {
            return state_;
        }

        [[nodiscard]] constexpr TPluginAdapterView view() const noexcept
        {
            return TWriteSideRegistryDeliveryPluginAdapterViewBuilder::view(
                config_,
                descriptor_.correlation);
        }

        [[nodiscard]] constexpr TReadinessView readiness() noexcept
        {
            return TWriteSideRegistryDeliveryReadinessPolicy::readiness(
                descriptor_,
                config_);
        }

        [[nodiscard]] constexpr TPlacementRequest prepare_placement_request() noexcept
        {
            if (!descriptor_.is_valid())
            {
                return TPlacementRequest{};
            }

            return TPlacementRequest::make(
                descriptor_.correlation,
                descriptor_.material_kind,
                descriptor_.material_size_hint,
                descriptor_.requires_ordered_delivery,
                descriptor_.destination_family());
        }

        [[nodiscard]] constexpr TBoundaryHandoffRequest prepare_boundary_handoff_request() noexcept
        {
            if (!descriptor_.is_valid())
            {
                return TBoundaryHandoffRequest{};
            }

            return TBoundaryHandoffRequest::make(
                descriptor_.correlation,
                descriptor_.registry_boundary,
                descriptor_.material_kind,
                descriptor_.material_size_hint,
                descriptor_.requires_ordered_delivery);
        }

        [[nodiscard]] constexpr TBridgeResult accept_placement_handle(
            const TPlacementHandle& handle) noexcept
        {
            if (!handle.is_valid())
            {
                return TBridgeResult::fail(
                    TBridgeError::make(
                        TBridgeErrorCode::handle_unavailable,
                        "registry delivery placement handle is invalid"),
                    descriptor_.correlation);
            }

            if (handle.correlation != descriptor_.correlation)
            {
                return TBridgeResult::reject(
                    TBridgeError::make(
                        TBridgeErrorCode::invalid_correlation,
                        "registry delivery placement handle correlation mismatch"),
                    descriptor_.correlation);
            }

            state_.accept_placement_handle(handle);
            return TBridgeResult::success(descriptor_.correlation);
        }

        [[nodiscard]] constexpr TLoadSignal emit_load_signal() noexcept
        {
            if (!state_.has_accepted_placement_handle())
            {
                return TLoadSignal::failed(
                    descriptor_.correlation,
                    TPlacementHandle::invalid(),
                    "registry delivery placement handle has not been accepted");
            }

            auto signal = TLoadSignal::completed(
                descriptor_.correlation,
                state_.accepted_placement_handle,
                descriptor_.material_size_hint);

            state_.mark_load_signal_emitted();
            return signal;
        }

        [[nodiscard]] constexpr TNextDestinationRequest next_destination_request() noexcept
        {
            return TNextDestinationRequest::make(
                descriptor_.correlation,
                state_.accepted_placement_handle,
                state_.has_accepted_placement_handle()
                    ? TNextDestinationReason::current_destination_completed
                    : TNextDestinationReason::retry_requested,
                state_.has_accepted_placement_handle()
                    ? "continue_after_write_side_registry_delivery_material_load"
                    : "retry_after_missing_registry_delivery_placement_handle");
        }

        [[nodiscard]] constexpr TBridgeResult accept_boundary_handoff_result(
            TBoundaryHandoffResult result) noexcept
        {
            if (result.accepted())
            {
                state_.accept_boundary_handoff(result);
                return TBridgeResult::success(descriptor_.correlation);
            }

            if (result.completed())
            {
                state_.complete_boundary_handoff(result);
                return TBridgeResult::success(descriptor_.correlation);
            }

            if (result.deferred())
            {
                return TBridgeResult::defer(
                    result.bridge_result.error,
                    descriptor_.correlation);
            }

            return TBridgeResult::fail(
                result.bridge_result.error.has_error()
                    ? result.bridge_result.error
                    : TBridgeError::make(
                        TBridgeErrorCode::endpoint_error,
                        "registry delivery boundary handoff was not accepted"),
                descriptor_.correlation);
        }

        constexpr void reset_state() noexcept
        {
            state_.reset();
        }

    private:
        TWriteSideRegistryDeliveryMaterialDescriptor descriptor_{};
        TWriteSideRegistryDeliveryPluginAdapterConfig config_{};
        TWriteSideRegistryDeliveryPluginAdapterState state_{};
    };
}
