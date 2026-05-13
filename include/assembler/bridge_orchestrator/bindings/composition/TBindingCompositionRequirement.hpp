#pragma once

#include <string_view>

#include "assembler/communication_context/bindings/composition/TBindingCardinality.hpp"
#include "assembler/communication_context/bindings/composition/TBindingExecutionAssumption.hpp"
#include "assembler/communication_context/bindings/composition/TBindingHandoffStyle.hpp"
#include "assembler/communication_context/bindings/composition/TBindingOwnershipBoundary.hpp"

/**
 * @file TBindingCompositionRequirement.hpp
 * @brief Required composition shape for an ASCC binding.
 *
 * @section ascc_comp_w04 Purpose
 * A requirement describes the expected composition semantics for a binding.
 * It is checked against `TBindingCompositionMetadata` and does not execute or
 * materialize a binding.
 */

namespace assembler::communication_context
{
    struct TBindingCompositionRequirement final
    {
        TBindingCardinality cardinality{TBindingCardinality::unknown};
        TBindingHandoffStyle handoff_style{TBindingHandoffStyle::unknown};
        TBindingExecutionAssumption execution_assumption{TBindingExecutionAssumption::unknown};
        TBindingOwnershipBoundary ownership_boundary{TBindingOwnershipBoundary::unknown};

        bool require_protocol{false};
        bool require_session{false};
        bool require_bridge{false};
        bool allow_payload_delivery_claim{true};
        bool allow_diagnostic_only{false};

        std::string_view requirement_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return cardinality != TBindingCardinality::unknown
                && handoff_style != TBindingHandoffStyle::unknown
                && execution_assumption != TBindingExecutionAssumption::unknown
                && ownership_boundary != TBindingOwnershipBoundary::unknown
                && !requirement_name.empty();
        }

        [[nodiscard]] static constexpr TBindingCompositionRequirement
        bridge_mediated_one_to_one(
            std::string_view name = "bridge_mediated_one_to_one_requirement") noexcept
        {
            return TBindingCompositionRequirement{
                TBindingCardinality::one_to_one,
                TBindingHandoffStyle::bridge_mediated,
                TBindingExecutionAssumption::bounded_step,
                TBindingOwnershipBoundary::no_endpoint_internals,
                true,
                true,
                true,
                true,
                false,
                name
            };
        }

        [[nodiscard]] static constexpr TBindingCompositionRequirement
        direct_single_writer(
            std::string_view name = "direct_single_writer_requirement") noexcept
        {
            return TBindingCompositionRequirement{
                TBindingCardinality::one_to_one,
                TBindingHandoffStyle::direct,
                TBindingExecutionAssumption::single_writer_compatible,
                TBindingOwnershipBoundary::endpoint_owned,
                false,
                false,
                false,
                true,
                false,
                name
            };
        }

        [[nodiscard]] static constexpr TBindingCompositionRequirement
        diagnostic_only(
            std::string_view name = "diagnostic_only_requirement") noexcept
        {
            return TBindingCompositionRequirement{
                TBindingCardinality::observer_only,
                TBindingHandoffStyle::diagnostic_only,
                TBindingExecutionAssumption::model_only,
                TBindingOwnershipBoundary::diagnostic_only,
                false,
                false,
                false,
                false,
                true,
                name
            };
        }
    };
}
