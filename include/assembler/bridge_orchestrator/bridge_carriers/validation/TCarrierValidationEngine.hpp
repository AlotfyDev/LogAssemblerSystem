#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationReport.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationResult.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"

/**
 * @file TCarrierValidationEngine.hpp
 * @brief Runtime validation policy for ASCC carrier views.
 *
 * This engine validates canonical carrier views against the expected ASCC
 * carrier taxonomy. Validation here is semantic validation, not merely
 * structural validation.
 *
 * Responsibilities:
 * - Reject unknown expected carrier kinds.
 * - Reject invalid carrier views.
 * - Reject invalid correlations.
 * - Reject carrier kind mismatches.
 * - Produce reusable validation reports for facade/runtime layers.
 *
 * This component intentionally validates against the canonical
 * `TAsccCarrierKind` vocabulary to avoid duplicated runtime taxonomies.
 */

namespace assembler::communication_context
{
    struct TCarrierValidationEngine final
    {
        [[nodiscard]] static constexpr TCarrierValidationResult validate_view(
            TCarrierView view,
            TAsccCarrierKind expected) noexcept
        {
            if (expected == TAsccCarrierKind::unknown)
            {
                return TCarrierValidationResult::fail(
                    expected,
                    TCarrierValidationStatus::invalid_kind,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "expected carrier kind is unknown"));
            }

            if (!view.valid)
            {
                return TCarrierValidationResult::fail(
                    expected,
                    TCarrierValidationStatus::invalid_shape,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "carrier view is marked invalid"));
            }

            if (view.kind == TAsccCarrierKind::unknown)
            {
                return TCarrierValidationResult::fail(
                    expected,
                    TCarrierValidationStatus::invalid_kind,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "carrier view kind is unknown"));
            }

            if (!view.correlation.is_valid())
            {
                return TCarrierValidationResult::fail(
                    expected,
                    TCarrierValidationStatus::invalid_correlation,
                    TBridgeError::make(
                        TBridgeErrorCode::invalid_correlation,
                        "carrier correlation is invalid"));
            }

            if (view.kind != expected)
            {
                return TCarrierValidationResult::fail(
                    expected,
                    TCarrierValidationStatus::wrong_kind,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "carrier kind does not match expected kind"));
            }

            return TCarrierValidationResult::pass(
                expected,
                "carrier validation passed");
        }

        [[nodiscard]] static constexpr TCarrierValidationReport report_view(
            TCarrierView view,
            TAsccCarrierKind expected,
            std::string_view note = {}) noexcept
        {
            return TCarrierValidationReport::make(
                view,
                validate_view(view, expected),
                note.empty()
                    ? "carrier validation report generated"
                    : note);
        }
    };
}
