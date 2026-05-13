#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/composition/TBindingCompositionMetadata.hpp"
#include "assembler/communication_context/bindings/composition/TBindingCompositionRequirement.hpp"
#include "assembler/communication_context/bindings/composition/TBindingCompositionView.hpp"

/**
 * @file TBindingCompositionReport.hpp
 * @brief Result report for checking binding composition metadata against a requirement.
 */

namespace assembler::communication_context
{
    struct TBindingCompositionReport final
    {
        TBindingCompositionView view{};
        TBindingCompositionRequirement requirement{};
        bool metadata_valid{false};
        bool requirement_valid{false};
        bool cardinality_matched{false};
        bool handoff_style_matched{false};
        bool execution_assumption_matched{false};
        bool ownership_boundary_preserved{false};
        bool protocol_requirement_satisfied{false};
        bool session_requirement_satisfied{false};
        bool bridge_requirement_satisfied{false};
        bool payload_delivery_claim_allowed{false};
        bool diagnostic_rule_satisfied{false};
        std::string_view note{};

        [[nodiscard]] constexpr bool passed() const noexcept
        {
            return metadata_valid
                && requirement_valid
                && cardinality_matched
                && handoff_style_matched
                && execution_assumption_matched
                && ownership_boundary_preserved
                && protocol_requirement_satisfied
                && session_requirement_satisfied
                && bridge_requirement_satisfied
                && payload_delivery_claim_allowed
                && diagnostic_rule_satisfied;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !passed();
        }

        [[nodiscard]] static constexpr TBindingCompositionReport evaluate(
            TBindingCompositionMetadata metadata,
            TBindingCompositionRequirement required,
            std::string_view report_note = {}) noexcept
        {
            const auto metadata_view = TBindingCompositionView::from_metadata(metadata);
            const bool metadata_ok = metadata.is_valid();
            const bool requirement_ok = required.is_valid();
            const bool diagnostic_ok = required.allow_diagnostic_only
                ? metadata.is_diagnostic_only()
                : !metadata.is_diagnostic_only();
            const bool delivery_ok = required.allow_payload_delivery_claim
                ? true
                : !metadata.can_claim_payload_delivery();

            return TBindingCompositionReport{
                metadata_view,
                required,
                metadata_ok,
                requirement_ok,
                metadata.cardinality == required.cardinality,
                metadata.handoff_style == required.handoff_style,
                metadata.execution_assumption == required.execution_assumption,
                metadata.ownership_boundary == required.ownership_boundary
                    && metadata.preserves_endpoint_boundary(),
                (!required.require_protocol || metadata.requires_protocol),
                (!required.require_session || metadata.requires_session),
                (!required.require_bridge || metadata.requires_bridge),
                delivery_ok,
                diagnostic_ok,
                report_note
            };
        }
    };
}
