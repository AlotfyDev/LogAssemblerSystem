#pragma once

#include <string_view>

/**
 * @file TBindingOwnershipBoundary.hpp
 * @brief Ownership-boundary vocabulary for ASCC binding composition metadata.
 *
 * @section ascc_comp_w04 Purpose
 * Ownership boundary records what a binding must not collapse into. It protects
 * endpoint internals from being owned by ASCC and distinguishes orchestration
 * from endpoint lifecycle, mutation, persistence, scheduling, or delivery.
 */

namespace assembler::communication_context
{
    enum class TBindingOwnershipBoundary
    {
        unknown,
        endpoint_owned,
        bridge_orchestrated,
        no_endpoint_internals,
        diagnostic_only
    };

    [[nodiscard]] constexpr bool preserves_endpoint_ownership(
        TBindingOwnershipBoundary boundary) noexcept
    {
        return boundary == TBindingOwnershipBoundary::endpoint_owned
            || boundary == TBindingOwnershipBoundary::no_endpoint_internals
            || boundary == TBindingOwnershipBoundary::diagnostic_only;
    }

    [[nodiscard]] constexpr bool is_bridge_orchestrated_boundary(
        TBindingOwnershipBoundary boundary) noexcept
    {
        return boundary == TBindingOwnershipBoundary::bridge_orchestrated;
    }

    [[nodiscard]] constexpr bool is_diagnostic_only_boundary(
        TBindingOwnershipBoundary boundary) noexcept
    {
        return boundary == TBindingOwnershipBoundary::diagnostic_only;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBindingOwnershipBoundary boundary) noexcept
    {
        switch (boundary)
        {
            case TBindingOwnershipBoundary::unknown: return "unknown";
            case TBindingOwnershipBoundary::endpoint_owned: return "endpoint_owned";
            case TBindingOwnershipBoundary::bridge_orchestrated: return "bridge_orchestrated";
            case TBindingOwnershipBoundary::no_endpoint_internals: return "no_endpoint_internals";
            case TBindingOwnershipBoundary::diagnostic_only: return "diagnostic_only";
        }

        return "unknown";
    }
}
