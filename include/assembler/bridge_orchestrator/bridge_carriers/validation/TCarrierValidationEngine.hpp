#pragma once

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationReport.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationResult.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"

/**
 * @file TCarrierValidationEngine.hpp
 * @brief Runtime validation policy for ASCC carrier views.
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

            if (!view.is_valid())
            {
                return TCarrierValidationResult::fail(
                    expected,
                    TCarrierValidationStatus::invalid_shape,
                    TBridgeError::make(
                        TBridgeErrorCode::protocol_violation,
                        "carrier view is invalid"));
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

            return TCarrierValidationResult::pass(expected);
        }

        [[nodiscard]] static constexpr TCarrierValidationReport report_view(
            TCarrierView view,
            TAsccCarrierKind expected,
            std::string_view note = {}) noexcept
        {
            return TCarrierValidationReport::make(
                view,
                validate_view(view, expected),
                note);
        }
    };
}
