#pragma once

#include <string_view>

/**
 * @file TAsccEvidenceDimension.hpp
 * @brief Evidence dimensions consumed by ASCC readiness aggregation.
 */

namespace assembler::communication_context
{
    enum class TAsccEvidenceDimension
    {
        unknown,
        identity_valid,
        role_valid,
        participant_capabilities_satisfied,
        binding_compatible,
        composition_metadata_valid,
        protocol_requirements_satisfied,
        carrier_flow_supported,
        session_openable,
        bridge_model_valid,
        diagnostics_available,
        registry_snapshot_available
    };

    [[nodiscard]] constexpr bool is_participant_evidence_dimension(
        TAsccEvidenceDimension dimension) noexcept
    {
        return dimension == TAsccEvidenceDimension::identity_valid
            || dimension == TAsccEvidenceDimension::role_valid
            || dimension == TAsccEvidenceDimension::participant_capabilities_satisfied
            || dimension == TAsccEvidenceDimension::carrier_flow_supported;
    }

    [[nodiscard]] constexpr bool is_binding_evidence_dimension(
        TAsccEvidenceDimension dimension) noexcept
    {
        return dimension == TAsccEvidenceDimension::binding_compatible
            || dimension == TAsccEvidenceDimension::composition_metadata_valid;
    }

    [[nodiscard]] constexpr bool is_protocol_evidence_dimension(
        TAsccEvidenceDimension dimension) noexcept
    {
        return dimension == TAsccEvidenceDimension::protocol_requirements_satisfied
            || dimension == TAsccEvidenceDimension::carrier_flow_supported;
    }

    [[nodiscard]] constexpr bool is_operational_evidence_dimension(
        TAsccEvidenceDimension dimension) noexcept
    {
        return dimension == TAsccEvidenceDimension::session_openable
            || dimension == TAsccEvidenceDimension::bridge_model_valid
            || dimension == TAsccEvidenceDimension::diagnostics_available
            || dimension == TAsccEvidenceDimension::registry_snapshot_available;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TAsccEvidenceDimension dimension) noexcept
    {
        switch (dimension)
        {
            case TAsccEvidenceDimension::unknown: return "unknown";
            case TAsccEvidenceDimension::identity_valid: return "identity_valid";
            case TAsccEvidenceDimension::role_valid: return "role_valid";
            case TAsccEvidenceDimension::participant_capabilities_satisfied: return "participant_capabilities_satisfied";
            case TAsccEvidenceDimension::binding_compatible: return "binding_compatible";
            case TAsccEvidenceDimension::composition_metadata_valid: return "composition_metadata_valid";
            case TAsccEvidenceDimension::protocol_requirements_satisfied: return "protocol_requirements_satisfied";
            case TAsccEvidenceDimension::carrier_flow_supported: return "carrier_flow_supported";
            case TAsccEvidenceDimension::session_openable: return "session_openable";
            case TAsccEvidenceDimension::bridge_model_valid: return "bridge_model_valid";
            case TAsccEvidenceDimension::diagnostics_available: return "diagnostics_available";
            case TAsccEvidenceDimension::registry_snapshot_available: return "registry_snapshot_available";
        }

        return "unknown";
    }
}
