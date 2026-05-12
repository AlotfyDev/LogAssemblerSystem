#pragma once

#include <string_view>

/**
 * @file TAsccComposableCapabilityKind.hpp
 * @brief Functional capability categories exposed by ASCC as a composable component.
 */

namespace assembler::communication_context
{
    enum class TAsccComposableCapabilityKind
    {
        unknown,
        participant_identity,
        participant_role_classification,
        plugin_adapter_surface,
        port_surface,
        channel_topology,
        binding_declaration,
        session_lifecycle,
        protocol_model,
        carrier_vocabulary,
        registry_catalog,
        diagnostic_reporting,
        integration_boundary_surface,
        readiness_evidence,
        composition_metadata
    };

    [[nodiscard]] constexpr bool is_identity_capability(
        TAsccComposableCapabilityKind kind) noexcept
    {
        return kind == TAsccComposableCapabilityKind::participant_identity
            || kind == TAsccComposableCapabilityKind::participant_role_classification;
    }

    [[nodiscard]] constexpr bool is_surface_capability(
        TAsccComposableCapabilityKind kind) noexcept
    {
        return kind == TAsccComposableCapabilityKind::plugin_adapter_surface
            || kind == TAsccComposableCapabilityKind::port_surface
            || kind == TAsccComposableCapabilityKind::integration_boundary_surface;
    }

    [[nodiscard]] constexpr bool is_model_capability(
        TAsccComposableCapabilityKind kind) noexcept
    {
        return kind == TAsccComposableCapabilityKind::channel_topology
            || kind == TAsccComposableCapabilityKind::binding_declaration
            || kind == TAsccComposableCapabilityKind::session_lifecycle
            || kind == TAsccComposableCapabilityKind::protocol_model
            || kind == TAsccComposableCapabilityKind::carrier_vocabulary;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TAsccComposableCapabilityKind kind) noexcept
    {
        switch (kind)
        {
            case TAsccComposableCapabilityKind::unknown: return "unknown";
            case TAsccComposableCapabilityKind::participant_identity: return "participant_identity";
            case TAsccComposableCapabilityKind::participant_role_classification: return "participant_role_classification";
            case TAsccComposableCapabilityKind::plugin_adapter_surface: return "plugin_adapter_surface";
            case TAsccComposableCapabilityKind::port_surface: return "port_surface";
            case TAsccComposableCapabilityKind::channel_topology: return "channel_topology";
            case TAsccComposableCapabilityKind::binding_declaration: return "binding_declaration";
            case TAsccComposableCapabilityKind::session_lifecycle: return "session_lifecycle";
            case TAsccComposableCapabilityKind::protocol_model: return "protocol_model";
            case TAsccComposableCapabilityKind::carrier_vocabulary: return "carrier_vocabulary";
            case TAsccComposableCapabilityKind::registry_catalog: return "registry_catalog";
            case TAsccComposableCapabilityKind::diagnostic_reporting: return "diagnostic_reporting";
            case TAsccComposableCapabilityKind::integration_boundary_surface: return "integration_boundary_surface";
            case TAsccComposableCapabilityKind::readiness_evidence: return "readiness_evidence";
            case TAsccComposableCapabilityKind::composition_metadata: return "composition_metadata";
        }

        return "unknown";
    }
}
