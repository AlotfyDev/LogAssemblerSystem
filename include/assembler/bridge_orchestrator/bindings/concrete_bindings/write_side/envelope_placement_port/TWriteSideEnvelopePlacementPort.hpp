#pragma once

#include "assembler/communication_context/bridge_carriers/admission/TAdmissionResult.hpp"
#include "assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/obligations/ports/TPort.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/carriers/TWriteSidePlacementTargetDescriptor.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/config/TWriteSideEnvelopePlacementPortConfig.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/policies/TWriteSideEnvelopePlacementAdmissionPolicy.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/state/TWriteSideEnvelopePlacementPortState.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/views/TWriteSideEnvelopePlacementPortViewBuilder.hpp"

/**
 * @file TWriteSideEnvelopePlacementPort.hpp
 * @brief Concrete host-side port for Write Side envelope placement.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Write Side envelope
 * placement host-port binding surface when ASCC matures. The final version
 * should preserve:
 *
 * - concrete port satisfying W05 `TPort` obligations for Log Level Envelope
 *   placement admission;
 * - future bridge between a content-side envelope PluginAdapter and real
 *   Write Side placement infrastructure;
 * - strict boundary that produces opaque placement handles without exposing
 *   slots, containers, moderators, rounds, or reference precalculators.
 *
 * @section ascc_current_wave Current W14B Implementation Scope
 * This W14B version implements the host-side concrete placement port surface
 * only. It adapts bridge-visible placement carriers into a Write Side-facing
 * boundary contract while remaining compatible with W01-W10 Communication
 * Context foundations and W14A Log Level API envelope PluginAdapter.
 *
 * - CRTP inheritance from `TPort<TWriteSideEnvelopePlacementPort>`;
 * - readiness, admission, opaque handle production, load-signal receipt, and
 *   next-destination acknowledgement;
 * - local descriptor/config/state only.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - Write Side slot/container/round implementation;
 * - Slots Container Moderator implementation;
 * - Slots Containers Bundle Agent implementation;
 * - Reference Precalculator implementation;
 * - Dispatcher, registry, persistence, database, telemetry, scheduler, thread, or ABI behavior;
 * - Log Level API envelope assembly or content validation;
 * - direct payload memory movement or endpoint object ownership.
 * - concrete host runtime placement or real envelope loading.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14B concrete port headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPort` obligations, and W14A only for integration smoke
 * tests. They must not include concrete `assembler/write_side/...` endpoint
 * internals or concrete `assembler/log_level_api/...` endpoint internals.
 */

namespace assembler::communication_context
{
    class TWriteSideEnvelopePlacementPort final
        : public TPort<TWriteSideEnvelopePlacementPort>
    {
    public:
        constexpr explicit TWriteSideEnvelopePlacementPort(
            TWriteSideEnvelopePlacementPortConfig config =
                TWriteSideEnvelopePlacementPortConfig::defaults(),
            TWriteSidePlacementTargetDescriptor target =
                TWriteSidePlacementTargetDescriptor::defaults()) noexcept
            : config_(config),
              target_(target),
              state_()
        {
            state_.reset(config_.first_handle_value);
        }

        [[nodiscard]] constexpr const TWriteSideEnvelopePlacementPortConfig& config() const noexcept
        {
            return config_;
        }

        [[nodiscard]] constexpr const TWriteSidePlacementTargetDescriptor& target() const noexcept
        {
            return target_;
        }

        [[nodiscard]] constexpr const TWriteSideEnvelopePlacementPortState& state() const noexcept
        {
            return state_;
        }

        [[nodiscard]] constexpr TPortView view() const noexcept
        {
            return TWriteSideEnvelopePlacementPortViewBuilder::view(config_);
        }

        [[nodiscard]] constexpr TReadinessView readiness(
            const TPlacementRequest& request) noexcept
        {
            if (!config_.is_valid() || !target_.is_valid())
            {
                return TReadinessView::not_ready(
                    "write_side_envelope_placement_port_config_or_target_invalid",
                    request.correlation);
            }

            if (!request.is_valid())
            {
                return TReadinessView::not_ready(
                    "placement_request_invalid",
                    request.correlation);
            }

            if (!TWriteSideEnvelopePlacementAdmissionPolicy::payload_kind_is_supported(request, config_))
            {
                return TReadinessView::not_ready(
                    "unsupported_payload_kind",
                    request.correlation);
            }

            if (!TWriteSideEnvelopePlacementAdmissionPolicy::destination_is_supported(request, config_))
            {
                return TReadinessView::deferred(
                    "unsupported_destination_family",
                    request.correlation);
            }

            if (request.requires_ordered_placement && !target_.supports_ordered_placement)
            {
                return TReadinessView::deferred(
                    "ordered_placement_not_supported_by_target",
                    request.correlation);
            }

            return TReadinessView::ready(
                request.correlation,
                TWriteSideEnvelopePlacementAdmissionPolicy::readiness_capacity_hint(config_));
        }

        [[nodiscard]] constexpr TAdmissionResult admit(
            const TPlacementRequest& request) noexcept
        {
            const auto readiness_view = readiness(request);

            if (readiness_view.is_ready())
            {
                state_.record_admission();
                return TAdmissionResult::accept(request.correlation);
            }

            if (readiness_view.is_deferred())
            {
                return TAdmissionResult::defer(
                    readiness_view.reason,
                    request.correlation);
            }

            return TAdmissionResult::reject(
                readiness_view.reason.empty() ? "placement_request_not_admissible" : readiness_view.reason,
                request.correlation);
        }

        [[nodiscard]] constexpr TPlacementHandle placement_handle(
            const TPlacementRequest& request) noexcept
        {
            if (!TWriteSideEnvelopePlacementAdmissionPolicy::request_is_admissible(request, config_))
            {
                return TPlacementHandle::invalid();
            }

            const auto value = state_.allocate_handle_value();

            if (value == 0u)
            {
                return TPlacementHandle::invalid();
            }

            auto handle = TPlacementHandle::make(
                value,
                request.correlation,
                target_.handle_family.empty() ? config_.handle_family : target_.handle_family);

            state_.record_handle(handle);
            return handle;
        }

        [[nodiscard]] constexpr TBridgeResult receive_load_signal(
            const TLoadSignal& signal) noexcept
        {
            if (!signal.placement.is_valid())
            {
                return TBridgeResult::reject(
                    TBridgeError::make(
                        TBridgeErrorCode::handle_unavailable,
                        "load signal carries invalid placement handle"),
                    signal.correlation);
            }

            if (state_.has_last_handle() && signal.placement != state_.last_handle)
            {
                return TBridgeResult::reject(
                    TBridgeError::make(
                        TBridgeErrorCode::invalid_correlation,
                        "load signal placement does not match last produced handle"),
                    signal.correlation);
            }

            if (signal.failed())
            {
                state_.record_signal(signal);
                return TBridgeResult::fail(
                    TBridgeError::make(
                        TBridgeErrorCode::endpoint_error,
                        signal.note.empty() ? "load signal failed" : signal.note),
                    signal.correlation);
            }

            if (!signal.completed())
            {
                state_.record_signal(signal);
                return TBridgeResult::defer(
                    TBridgeError::make(
                        TBridgeErrorCode::admission_deferred,
                        "load signal is not completed"),
                    signal.correlation);
            }

            state_.record_signal(signal);
            return TBridgeResult::success(signal.correlation);
        }

        [[nodiscard]] constexpr TBridgeResult next_destination(
            const TNextDestinationRequest& request) noexcept
        {
            if (!request.is_valid())
            {
                return TBridgeResult::reject(
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "next destination request is invalid"),
                    request.correlation);
            }

            if (state_.has_last_handle() && request.current_handle != state_.last_handle)
            {
                return TBridgeResult::reject(
                    TBridgeError::make(
                        TBridgeErrorCode::invalid_correlation,
                        "next destination request placement does not match last produced handle"),
                    request.correlation);
            }

            return TBridgeResult::success(request.correlation);
        }

        constexpr void reset_state() noexcept
        {
            state_.reset(config_.first_handle_value);
        }

    private:
        TWriteSideEnvelopePlacementPortConfig config_{};
        TWriteSidePlacementTargetDescriptor target_{};
        TWriteSideEnvelopePlacementPortState state_{};
    };
}
