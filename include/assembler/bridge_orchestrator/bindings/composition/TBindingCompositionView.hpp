#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bindings/composition/TBindingCompositionMetadata.hpp"

/**
 * @file TBindingCompositionView.hpp
 * @brief Read-only projection of binding composition metadata.
 */

namespace assembler::communication_context
{
    struct TBindingCompositionView final
    {
        TBindingCardinality cardinality{TBindingCardinality::unknown};
        TBindingHandoffStyle handoff_style{TBindingHandoffStyle::unknown};
        TBindingExecutionAssumption execution_assumption{TBindingExecutionAssumption::unknown};
        TBindingOwnershipBoundary ownership_boundary{TBindingOwnershipBoundary::unknown};

        bool requires_protocol{false};
        bool requires_session{false};
        bool requires_bridge{false};
        bool diagnostic_only{false};
        bool can_claim_payload_delivery{false};
        bool valid{false};

        std::uint32_t version{0u};
        std::string_view display_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return valid
                && cardinality != TBindingCardinality::unknown
                && handoff_style != TBindingHandoffStyle::unknown
                && execution_assumption != TBindingExecutionAssumption::unknown
                && ownership_boundary != TBindingOwnershipBoundary::unknown
                && version > 0u;
        }

        [[nodiscard]] static constexpr TBindingCompositionView from_metadata(
            TBindingCompositionMetadata metadata) noexcept
        {
            return TBindingCompositionView{
                metadata.cardinality,
                metadata.handoff_style,
                metadata.execution_assumption,
                metadata.ownership_boundary,
                metadata.requires_protocol,
                metadata.requires_session,
                metadata.requires_bridge,
                metadata.is_diagnostic_only(),
                metadata.can_claim_payload_delivery(),
                metadata.is_valid(),
                metadata.version,
                metadata.metadata_name
            };
        }

        [[nodiscard]] static constexpr TBindingCompositionView invalid() noexcept
        {
            return TBindingCompositionView{};
        }
    };
}
