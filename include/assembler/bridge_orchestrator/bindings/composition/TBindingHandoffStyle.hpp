#pragma once

#include <string_view>

/**
 * @file TBindingHandoffStyle.hpp
 * @brief Handoff-style vocabulary for ASCC binding composition metadata.
 *
 * @section ascc_comp_w04 Purpose
 * Handoff style describes how payload/material carriers are intended to move
 * across the binding boundary.  It is metadata only; it does not perform
 * endpoint invocation, protocol stepping, scheduling, or delivery.
 */

namespace assembler::communication_context
{
    enum class TBindingHandoffStyle
    {
        unknown,
        direct,
        bridge_mediated,
        passive_pull,
        push,
        hybrid,
        diagnostic_only
    };

    [[nodiscard]] constexpr bool requires_bridge_mediation(
        TBindingHandoffStyle style) noexcept
    {
        return style == TBindingHandoffStyle::bridge_mediated
            || style == TBindingHandoffStyle::passive_pull
            || style == TBindingHandoffStyle::push
            || style == TBindingHandoffStyle::hybrid;
    }

    [[nodiscard]] constexpr bool is_direct_handoff(
        TBindingHandoffStyle style) noexcept
    {
        return style == TBindingHandoffStyle::direct;
    }

    [[nodiscard]] constexpr bool is_diagnostic_only_handoff(
        TBindingHandoffStyle style) noexcept
    {
        return style == TBindingHandoffStyle::diagnostic_only;
    }

    [[nodiscard]] constexpr bool can_claim_payload_delivery(
        TBindingHandoffStyle style) noexcept
    {
        return style != TBindingHandoffStyle::unknown
            && style != TBindingHandoffStyle::diagnostic_only;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBindingHandoffStyle style) noexcept
    {
        switch (style)
        {
            case TBindingHandoffStyle::unknown: return "unknown";
            case TBindingHandoffStyle::direct: return "direct";
            case TBindingHandoffStyle::bridge_mediated: return "bridge_mediated";
            case TBindingHandoffStyle::passive_pull: return "passive_pull";
            case TBindingHandoffStyle::push: return "push";
            case TBindingHandoffStyle::hybrid: return "hybrid";
            case TBindingHandoffStyle::diagnostic_only: return "diagnostic_only";
        }

        return "unknown";
    }
}
