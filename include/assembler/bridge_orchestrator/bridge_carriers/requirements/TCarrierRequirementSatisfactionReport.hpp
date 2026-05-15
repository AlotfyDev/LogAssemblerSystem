#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

/**
 * @file TCarrierRequirementSatisfactionReport.hpp
 * @brief Evidence that an observed carrier satisfies a required carrier kind.
 */

namespace assembler::communication_context
{
    enum class TCarrierRequirementSatisfactionStatus
    {
        unknown,
        satisfied,
        optional_missing,
        missing_required,
        wrong_kind,
        invalid_observed_carrier
    };

    struct TCarrierRequirementSatisfactionReport final
    {
        TAsccCarrierKind required_kind{TAsccCarrierKind::unknown};
        TCarrierView observed_carrier{};
        TCarrierRequirementSatisfactionStatus status{TCarrierRequirementSatisfactionStatus::unknown};
        bool required{true};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return required_kind != TAsccCarrierKind::unknown
                && status != TCarrierRequirementSatisfactionStatus::unknown;
        }

        [[nodiscard]] constexpr bool satisfied() const noexcept
        {
            return is_valid()
                && (status == TCarrierRequirementSatisfactionStatus::satisfied
                    || status == TCarrierRequirementSatisfactionStatus::optional_missing);
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return is_valid() && !satisfied();
        }

        [[nodiscard]] static constexpr TCarrierRequirementSatisfactionReport make(
            TAsccCarrierKind required,
            TCarrierView observed,
            TCarrierRequirementSatisfactionStatus result_status,
            bool is_required = true,
            std::string_view text = {}) noexcept
        {
            return TCarrierRequirementSatisfactionReport{
                required,
                observed,
                result_status,
                is_required,
                text
            };
        }
    };
}
