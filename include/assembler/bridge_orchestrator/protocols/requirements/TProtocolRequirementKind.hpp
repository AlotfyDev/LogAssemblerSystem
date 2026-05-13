#pragma once

#include <string_view>

/**
 * @file TProtocolRequirementKind.hpp
 * @brief Requirement categories declared by ASCC protocols.
 */

namespace assembler::communication_context
{
    enum class TProtocolRequirementKind
    {
        unknown,
        participant_role_requirement,
        carrier_requirement,
        binding_composition_requirement,
        session_requirement,
        bridge_requirement,
        failure_semantics_requirement,
        diagnostic_requirement
    };

    [[nodiscard]] constexpr bool is_participant_requirement(
        TProtocolRequirementKind kind) noexcept
    {
        return kind == TProtocolRequirementKind::participant_role_requirement;
    }

    [[nodiscard]] constexpr bool is_carrier_requirement(
        TProtocolRequirementKind kind) noexcept
    {
        return kind == TProtocolRequirementKind::carrier_requirement;
    }

    [[nodiscard]] constexpr bool is_binding_requirement(
        TProtocolRequirementKind kind) noexcept
    {
        return kind == TProtocolRequirementKind::binding_composition_requirement;
    }

    [[nodiscard]] constexpr bool is_runtime_shape_requirement(
        TProtocolRequirementKind kind) noexcept
    {
        return kind == TProtocolRequirementKind::session_requirement
            || kind == TProtocolRequirementKind::bridge_requirement;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TProtocolRequirementKind kind) noexcept
    {
        switch (kind)
        {
            case TProtocolRequirementKind::unknown: return "unknown";
            case TProtocolRequirementKind::participant_role_requirement: return "participant_role_requirement";
            case TProtocolRequirementKind::carrier_requirement: return "carrier_requirement";
            case TProtocolRequirementKind::binding_composition_requirement: return "binding_composition_requirement";
            case TProtocolRequirementKind::session_requirement: return "session_requirement";
            case TProtocolRequirementKind::bridge_requirement: return "bridge_requirement";
            case TProtocolRequirementKind::failure_semantics_requirement: return "failure_semantics_requirement";
            case TProtocolRequirementKind::diagnostic_requirement: return "diagnostic_requirement";
        }

        return "unknown";
    }
}
