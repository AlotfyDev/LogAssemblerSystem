#pragma once

#include <string_view>

/**
 * @file TAsccRequirementKind.hpp
 * @brief Requirement categories consumed by ASCC composability coverage.
 */

namespace assembler::communication_context
{
    enum class TAsccRequirementKind
    {
        unknown,
        requires_participant_identity,
        requires_adapter_port_surfaces,
        requires_channel_binding_model,
        requires_session_protocol_model,
        requires_carrier_set,
        requires_registry_evidence,
        requires_diagnostic_evidence,
        requires_readiness_surface,
        requires_integration_boundary,
        requires_pipeline_composer_decision
    };

    [[nodiscard]] constexpr bool is_core_requirement(TAsccRequirementKind kind) noexcept
    {
        return kind == TAsccRequirementKind::requires_participant_identity
            || kind == TAsccRequirementKind::requires_adapter_port_surfaces
            || kind == TAsccRequirementKind::requires_channel_binding_model
            || kind == TAsccRequirementKind::requires_session_protocol_model
            || kind == TAsccRequirementKind::requires_carrier_set
            || kind == TAsccRequirementKind::requires_registry_evidence
            || kind == TAsccRequirementKind::requires_diagnostic_evidence
            || kind == TAsccRequirementKind::requires_readiness_surface;
    }

    [[nodiscard]] constexpr bool is_deferred_requirement(TAsccRequirementKind kind) noexcept
    {
        return kind == TAsccRequirementKind::requires_integration_boundary
            || kind == TAsccRequirementKind::requires_pipeline_composer_decision;
    }

    [[nodiscard]] constexpr std::string_view to_string(TAsccRequirementKind kind) noexcept
    {
        switch (kind)
        {
            case TAsccRequirementKind::unknown: return "unknown";
            case TAsccRequirementKind::requires_participant_identity: return "requires_participant_identity";
            case TAsccRequirementKind::requires_adapter_port_surfaces: return "requires_adapter_port_surfaces";
            case TAsccRequirementKind::requires_channel_binding_model: return "requires_channel_binding_model";
            case TAsccRequirementKind::requires_session_protocol_model: return "requires_session_protocol_model";
            case TAsccRequirementKind::requires_carrier_set: return "requires_carrier_set";
            case TAsccRequirementKind::requires_registry_evidence: return "requires_registry_evidence";
            case TAsccRequirementKind::requires_diagnostic_evidence: return "requires_diagnostic_evidence";
            case TAsccRequirementKind::requires_readiness_surface: return "requires_readiness_surface";
            case TAsccRequirementKind::requires_integration_boundary: return "requires_integration_boundary";
            case TAsccRequirementKind::requires_pipeline_composer_decision: return "requires_pipeline_composer_decision";
        }

        return "unknown";
    }
}
