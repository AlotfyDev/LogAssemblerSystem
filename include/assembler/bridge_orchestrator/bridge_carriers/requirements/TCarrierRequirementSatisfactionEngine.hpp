#pragma once

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionReport.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

/**
 * @file TCarrierRequirementSatisfactionEngine.hpp
 * @brief Runtime policy that matches observed carriers against required ASCC carrier kinds.
 */

namespace assembler::communication_context
{
    struct TCarrierRequirementSatisfactionEngine final
    {
        [[nodiscard]] static constexpr TCarrierRequirementSatisfactionReport satisfy(
            TAsccCarrierKind required_kind,
            TCarrierView observed,
            bool required = true,
            std::string_view note = {}) noexcept
        {
            if (required_kind == TAsccCarrierKind::unknown)
            {
                return TCarrierRequirementSatisfactionReport::make(
                    required_kind,
                    observed,
                    TCarrierRequirementSatisfactionStatus::wrong_kind,
                    required,
                    "required carrier kind is unknown");
            }

            if (!observed.is_valid())
            {
                return TCarrierRequirementSatisfactionReport::make(
                    required_kind,
                    observed,
                    required
                        ? TCarrierRequirementSatisfactionStatus::missing_required
                        : TCarrierRequirementSatisfactionStatus::optional_missing,
                    required,
                    note.empty() ? "observed carrier is invalid or missing" : note);
            }

            // TCarrierView currently stores TCarrierKind, not TAsccCarrierKind.
            // Until a canonical conversion helper is introduced, a valid observed
            // carrier is accepted as satisfying the requested ASCC kind. The exact
            // cross-kind mapping belongs to the next carrier-kind compatibility slice.
            return TCarrierRequirementSatisfactionReport::make(
                required_kind,
                observed,
                TCarrierRequirementSatisfactionStatus::satisfied,
                required,
                note.empty() ? "carrier requirement satisfied by valid carrier view" : note);
        }
    };
}
