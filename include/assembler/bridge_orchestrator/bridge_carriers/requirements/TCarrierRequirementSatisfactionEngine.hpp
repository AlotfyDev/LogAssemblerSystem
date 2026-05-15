#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionReport.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

/**
 * @file TCarrierRequirementSatisfactionEngine.hpp
 * @brief Runtime policy that matches observed carriers against required ASCC carrier kinds.
 *
 * This engine evaluates whether an observed carrier view satisfies a required
 * carrier contract from protocol/session/binding/runtime layers.
 *
 * Responsibilities:
 * - Validate required carrier taxonomy.
 * - Detect missing required carriers.
 * - Detect optional carrier absence.
 * - Detect carrier-kind mismatches.
 * - Produce reusable requirement evidence reports.
 *
 * This component intentionally depends on the canonical
 * `TAsccCarrierKind` vocabulary shared by the entire carrier runtime.
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

            if (!observed.valid)
            {
                return TCarrierRequirementSatisfactionReport::make(
                    required_kind,
                    observed,
                    required
                        ? TCarrierRequirementSatisfactionStatus::missing_required
                        : TCarrierRequirementSatisfactionStatus::optional_missing,
                    required,
                    note.empty()
                        ? "observed carrier is missing or invalid"
                        : note);
            }

            if (observed.kind == TAsccCarrierKind::unknown)
            {
                return TCarrierRequirementSatisfactionReport::make(
                    required_kind,
                    observed,
                    TCarrierRequirementSatisfactionStatus::invalid_observed_carrier,
                    required,
                    note.empty()
                        ? "observed carrier kind is unknown"
                        : note);
            }

            if (!observed.correlation.is_valid())
            {
                return TCarrierRequirementSatisfactionReport::make(
                    required_kind,
                    observed,
                    TCarrierRequirementSatisfactionStatus::invalid_observed_carrier,
                    required,
                    note.empty()
                        ? "observed carrier correlation is invalid"
                        : note);
            }

            if (observed.kind != required_kind)
            {
                return TCarrierRequirementSatisfactionReport::make(
                    required_kind,
                    observed,
                    TCarrierRequirementSatisfactionStatus::wrong_kind,
                    required,
                    note.empty()
                        ? "observed carrier kind does not satisfy requirement"
                        : note);
            }

            return TCarrierRequirementSatisfactionReport::make(
                required_kind,
                observed,
                TCarrierRequirementSatisfactionStatus::satisfied,
                required,
                note.empty()
                    ? "carrier requirement satisfied"
                    : note);
        }
    };
}
