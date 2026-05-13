#pragma once

#include <string_view>

/**
 * @file TProtocolCapabilityKind.hpp
 * @brief Capability vocabulary for ASCC bridge-visible protocols.
 *
 * @section ascc_comp_w05 Purpose
 * Protocol capabilities describe what a protocol can declare or require.
 * They do not execute protocol steps, invoke endpoints, move carriers, or own
 * session lifecycle.
 */

namespace assembler::communication_context
{
    enum class TProtocolCapabilityKind
    {
        unknown,

        declares_participant_roles,
        declares_carrier_requirements,
        declares_binding_requirements,
        declares_failure_semantics,

        supports_request_response_flow,
        supports_handle_exchange,
        supports_load_signal_flow,
        supports_next_destination_flow,
        supports_diagnostic_exchange,

        requires_bridge_mediation,
        requires_session_lifecycle,
        requires_bounded_step_execution
    };

    [[nodiscard]] constexpr bool is_declaration_capability(
        TProtocolCapabilityKind kind) noexcept
    {
        return kind == TProtocolCapabilityKind::declares_participant_roles
            || kind == TProtocolCapabilityKind::declares_carrier_requirements
            || kind == TProtocolCapabilityKind::declares_binding_requirements
            || kind == TProtocolCapabilityKind::declares_failure_semantics;
    }

    [[nodiscard]] constexpr bool is_flow_capability(
        TProtocolCapabilityKind kind) noexcept
    {
        return kind == TProtocolCapabilityKind::supports_request_response_flow
            || kind == TProtocolCapabilityKind::supports_handle_exchange
            || kind == TProtocolCapabilityKind::supports_load_signal_flow
            || kind == TProtocolCapabilityKind::supports_next_destination_flow
            || kind == TProtocolCapabilityKind::supports_diagnostic_exchange;
    }

    [[nodiscard]] constexpr bool is_runtime_requirement_capability(
        TProtocolCapabilityKind kind) noexcept
    {
        return kind == TProtocolCapabilityKind::requires_bridge_mediation
            || kind == TProtocolCapabilityKind::requires_session_lifecycle
            || kind == TProtocolCapabilityKind::requires_bounded_step_execution;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TProtocolCapabilityKind kind) noexcept
    {
        switch (kind)
        {
            case TProtocolCapabilityKind::unknown: return "unknown";
            case TProtocolCapabilityKind::declares_participant_roles: return "declares_participant_roles";
            case TProtocolCapabilityKind::declares_carrier_requirements: return "declares_carrier_requirements";
            case TProtocolCapabilityKind::declares_binding_requirements: return "declares_binding_requirements";
            case TProtocolCapabilityKind::declares_failure_semantics: return "declares_failure_semantics";
            case TProtocolCapabilityKind::supports_request_response_flow: return "supports_request_response_flow";
            case TProtocolCapabilityKind::supports_handle_exchange: return "supports_handle_exchange";
            case TProtocolCapabilityKind::supports_load_signal_flow: return "supports_load_signal_flow";
            case TProtocolCapabilityKind::supports_next_destination_flow: return "supports_next_destination_flow";
            case TProtocolCapabilityKind::supports_diagnostic_exchange: return "supports_diagnostic_exchange";
            case TProtocolCapabilityKind::requires_bridge_mediation: return "requires_bridge_mediation";
            case TProtocolCapabilityKind::requires_session_lifecycle: return "requires_session_lifecycle";
            case TProtocolCapabilityKind::requires_bounded_step_execution: return "requires_bounded_step_execution";
        }

        return "unknown";
    }
}
