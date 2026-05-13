#pragma once

#include <string_view>

/**
 * @file TParticipantCapabilityKind.hpp
 * @brief Functional capability vocabulary for bridge-visible participants.
 *
 * @section ascc_comp_w03 Purpose
 * This enum names what a participant can do inside ASCC carrier exchange.  It
 * is not a policy model and it is not an endpoint implementation model.
 */

namespace assembler::communication_context
{
    enum class TParticipantCapabilityKind
    {
        unknown,

        // content-provider / plugin-adapter side
        exposes_payload,
        exposes_envelope,
        exposes_container_material,
        reports_content_readiness,
        prepares_request_carrier,
        accepts_handle_carrier,
        accepts_admission_result,
        emits_load_signal,
        requests_next_destination,
        receives_bridge_result,

        // receiver / container-provider / port side
        reports_receiver_readiness,
        accepts_request_carrier,
        supports_admission,
        supports_deferred_admission,
        supports_rejection_reason,
        produces_handle_carrier,
        accepts_load_signal,
        acknowledges_next_destination,
        produces_bridge_result,
        supports_backpressure_view,
        supports_receiver_ack,

        // shared support capabilities
        supports_correlation,
        supports_diagnostics,
        supports_registry_view,
        supports_ordered_handoff,
        supports_unordered_handoff
    };

    [[nodiscard]] constexpr bool is_content_side_capability(
        TParticipantCapabilityKind kind) noexcept
    {
        return kind == TParticipantCapabilityKind::exposes_payload
            || kind == TParticipantCapabilityKind::exposes_envelope
            || kind == TParticipantCapabilityKind::exposes_container_material
            || kind == TParticipantCapabilityKind::reports_content_readiness
            || kind == TParticipantCapabilityKind::prepares_request_carrier
            || kind == TParticipantCapabilityKind::accepts_handle_carrier
            || kind == TParticipantCapabilityKind::accepts_admission_result
            || kind == TParticipantCapabilityKind::emits_load_signal
            || kind == TParticipantCapabilityKind::requests_next_destination
            || kind == TParticipantCapabilityKind::receives_bridge_result;
    }

    [[nodiscard]] constexpr bool is_receiver_side_capability(
        TParticipantCapabilityKind kind) noexcept
    {
        return kind == TParticipantCapabilityKind::reports_receiver_readiness
            || kind == TParticipantCapabilityKind::accepts_request_carrier
            || kind == TParticipantCapabilityKind::supports_admission
            || kind == TParticipantCapabilityKind::supports_deferred_admission
            || kind == TParticipantCapabilityKind::supports_rejection_reason
            || kind == TParticipantCapabilityKind::produces_handle_carrier
            || kind == TParticipantCapabilityKind::accepts_load_signal
            || kind == TParticipantCapabilityKind::acknowledges_next_destination
            || kind == TParticipantCapabilityKind::produces_bridge_result
            || kind == TParticipantCapabilityKind::supports_backpressure_view
            || kind == TParticipantCapabilityKind::supports_receiver_ack;
    }

    [[nodiscard]] constexpr bool is_shared_participant_capability(
        TParticipantCapabilityKind kind) noexcept
    {
        return kind == TParticipantCapabilityKind::supports_correlation
            || kind == TParticipantCapabilityKind::supports_diagnostics
            || kind == TParticipantCapabilityKind::supports_registry_view
            || kind == TParticipantCapabilityKind::supports_ordered_handoff
            || kind == TParticipantCapabilityKind::supports_unordered_handoff;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TParticipantCapabilityKind kind) noexcept
    {
        switch (kind)
        {
            case TParticipantCapabilityKind::unknown: return "unknown";
            case TParticipantCapabilityKind::exposes_payload: return "exposes_payload";
            case TParticipantCapabilityKind::exposes_envelope: return "exposes_envelope";
            case TParticipantCapabilityKind::exposes_container_material: return "exposes_container_material";
            case TParticipantCapabilityKind::reports_content_readiness: return "reports_content_readiness";
            case TParticipantCapabilityKind::prepares_request_carrier: return "prepares_request_carrier";
            case TParticipantCapabilityKind::accepts_handle_carrier: return "accepts_handle_carrier";
            case TParticipantCapabilityKind::accepts_admission_result: return "accepts_admission_result";
            case TParticipantCapabilityKind::emits_load_signal: return "emits_load_signal";
            case TParticipantCapabilityKind::requests_next_destination: return "requests_next_destination";
            case TParticipantCapabilityKind::receives_bridge_result: return "receives_bridge_result";
            case TParticipantCapabilityKind::reports_receiver_readiness: return "reports_receiver_readiness";
            case TParticipantCapabilityKind::accepts_request_carrier: return "accepts_request_carrier";
            case TParticipantCapabilityKind::supports_admission: return "supports_admission";
            case TParticipantCapabilityKind::supports_deferred_admission: return "supports_deferred_admission";
            case TParticipantCapabilityKind::supports_rejection_reason: return "supports_rejection_reason";
            case TParticipantCapabilityKind::produces_handle_carrier: return "produces_handle_carrier";
            case TParticipantCapabilityKind::accepts_load_signal: return "accepts_load_signal";
            case TParticipantCapabilityKind::acknowledges_next_destination: return "acknowledges_next_destination";
            case TParticipantCapabilityKind::produces_bridge_result: return "produces_bridge_result";
            case TParticipantCapabilityKind::supports_backpressure_view: return "supports_backpressure_view";
            case TParticipantCapabilityKind::supports_receiver_ack: return "supports_receiver_ack";
            case TParticipantCapabilityKind::supports_correlation: return "supports_correlation";
            case TParticipantCapabilityKind::supports_diagnostics: return "supports_diagnostics";
            case TParticipantCapabilityKind::supports_registry_view: return "supports_registry_view";
            case TParticipantCapabilityKind::supports_ordered_handoff: return "supports_ordered_handoff";
            case TParticipantCapabilityKind::supports_unordered_handoff: return "supports_unordered_handoff";
        }

        return "unknown";
    }
}
