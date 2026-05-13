#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bindings/composition/TBindingCardinality.hpp"
#include "assembler/communication_context/bindings/composition/TBindingExecutionAssumption.hpp"
#include "assembler/communication_context/bindings/composition/TBindingHandoffStyle.hpp"
#include "assembler/communication_context/bindings/composition/TBindingOwnershipBoundary.hpp"

/**
 * @file TBindingCompositionMetadata.hpp
 * @brief Composition metadata for ASCC binding declarations.
 *
 * @section ascc_comp_w04 Purpose
 * This metadata describes how a binding should be understood by ASCC and by
 * later pipeline-composition/readiness layers.  It is intentionally separate
 * from `TBindingProfile` in W04 to avoid breaking existing W06/W15 behavior.
 *
 * @section ascc_boundary_rule Boundary Rule
 * This file must not execute bindings, materialize sessions, step protocols,
 * invoke endpoints, own endpoint internals, or decide pipeline policy.  It is
 * descriptive metadata only.
 */

namespace assembler::communication_context
{
    struct TBindingCompositionMetadata final
    {
        TBindingCardinality cardinality{TBindingCardinality::unknown};
        TBindingHandoffStyle handoff_style{TBindingHandoffStyle::unknown};
        TBindingExecutionAssumption execution_assumption{TBindingExecutionAssumption::unknown};
        TBindingOwnershipBoundary ownership_boundary{TBindingOwnershipBoundary::unknown};

        bool requires_protocol{false};
        bool requires_session{false};
        bool requires_bridge{false};
        bool allows_diagnostic_only{false};
        bool allows_payload_delivery_claim{false};

        std::uint32_t version{1u};
        std::string_view metadata_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return cardinality != TBindingCardinality::unknown
                && handoff_style != TBindingHandoffStyle::unknown
                && execution_assumption != TBindingExecutionAssumption::unknown
                && ownership_boundary != TBindingOwnershipBoundary::unknown
                && version > 0u
                && !metadata_name.empty();
        }

        [[nodiscard]] constexpr bool is_bridge_mediated() const noexcept
        {
            return requires_bridge_mediation(handoff_style)
                || requires_bridge
                || requires_protocol
                || requires_session;
        }

        [[nodiscard]] constexpr bool is_direct() const noexcept
        {
            return is_direct_handoff(handoff_style)
                && !requires_bridge
                && !requires_protocol
                && !requires_session;
        }

        [[nodiscard]] constexpr bool is_diagnostic_only() const noexcept
        {
            return is_diagnostic_only_handoff(handoff_style)
                || allows_diagnostic_only;
        }

        [[nodiscard]] constexpr bool preserves_endpoint_boundary() const noexcept
        {
            return preserves_endpoint_ownership(ownership_boundary);
        }

        [[nodiscard]] constexpr bool can_claim_payload_delivery() const noexcept
        {
            return allows_payload_delivery_claim
                && can_claim_payload_delivery(handoff_style)
                && !is_diagnostic_only();
        }

        [[nodiscard]] static constexpr TBindingCompositionMetadata
        strict_static_one_to_one_bridge_mediated(
            std::string_view name = "strict_static_one_to_one_bridge_mediated") noexcept
        {
            return TBindingCompositionMetadata{
                TBindingCardinality::one_to_one,
                TBindingHandoffStyle::bridge_mediated,
                TBindingExecutionAssumption::bounded_step,
                TBindingOwnershipBoundary::no_endpoint_internals,
                true,
                true,
                true,
                false,
                true,
                1u,
                name
            };
        }

        [[nodiscard]] static constexpr TBindingCompositionMetadata
        direct_single_writer_compatible(
            std::string_view name = "direct_single_writer_compatible") noexcept
        {
            return TBindingCompositionMetadata{
                TBindingCardinality::one_to_one,
                TBindingHandoffStyle::direct,
                TBindingExecutionAssumption::single_writer_compatible,
                TBindingOwnershipBoundary::endpoint_owned,
                false,
                false,
                false,
                false,
                true,
                1u,
                name
            };
        }

        [[nodiscard]] static constexpr TBindingCompositionMetadata
        passive_pull_bridge_mediated(
            std::string_view name = "passive_pull_bridge_mediated") noexcept
        {
            return TBindingCompositionMetadata{
                TBindingCardinality::one_to_one,
                TBindingHandoffStyle::passive_pull,
                TBindingExecutionAssumption::bounded_step,
                TBindingOwnershipBoundary::no_endpoint_internals,
                true,
                true,
                true,
                false,
                true,
                1u,
                name
            };
        }

        [[nodiscard]] static constexpr TBindingCompositionMetadata
        diagnostic_only(
            std::string_view name = "diagnostic_only_binding") noexcept
        {
            return TBindingCompositionMetadata{
                TBindingCardinality::observer_only,
                TBindingHandoffStyle::diagnostic_only,
                TBindingExecutionAssumption::model_only,
                TBindingOwnershipBoundary::diagnostic_only,
                false,
                false,
                false,
                true,
                false,
                1u,
                name
            };
        }
    };
}
