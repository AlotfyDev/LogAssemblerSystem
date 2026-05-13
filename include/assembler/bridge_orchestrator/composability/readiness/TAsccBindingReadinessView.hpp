#pragma once

#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccBindingReadinessView.hpp
 * @brief Read-only readiness projection for ASCC binding declarations.
 *
 * @section ascc_comp_w06 Purpose
 * This view summarizes binding compatibility and W04 composition metadata
 * readiness without creating bindings, invoking endpoints, materializing
 * sessions, or acting as a pipeline composer.
 */

namespace assembler::communication_context
{
    struct TAsccBindingReadinessView final
    {
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        bool binding_identity_valid{false};
        bool compatibility_valid{false};
        bool composition_metadata_valid{false};
        bool ownership_boundary_preserved{false};
        bool payload_delivery_claim_allowed{false};
        std::string_view binding_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TAsccReadinessStatus::unknown
                && !binding_name.empty();
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && is_ready(status)
                && binding_identity_valid
                && compatibility_valid
                && composition_metadata_valid
                && ownership_boundary_preserved
                && payload_delivery_claim_allowed;
        }

        [[nodiscard]] constexpr bool blocked() const noexcept
        {
            return is_blocking_readiness_status(status)
                || !binding_identity_valid
                || !compatibility_valid
                || !composition_metadata_valid
                || !ownership_boundary_preserved;
        }

        [[nodiscard]] static constexpr TAsccBindingReadinessView make(
            TAsccReadinessStatus readiness_status,
            bool has_valid_identity,
            bool has_valid_compatibility,
            bool has_valid_composition_metadata,
            bool preserves_ownership_boundary,
            bool allows_payload_delivery_claim,
            std::string_view name = "binding_readiness") noexcept
        {
            return TAsccBindingReadinessView{
                readiness_status,
                has_valid_identity,
                has_valid_compatibility,
                has_valid_composition_metadata,
                preserves_ownership_boundary,
                allows_payload_delivery_claim,
                name
            };
        }
    };
}
