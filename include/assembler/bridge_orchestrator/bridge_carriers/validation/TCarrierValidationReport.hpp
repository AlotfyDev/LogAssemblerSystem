#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationResult.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

/**
 * @file TCarrierValidationReport.hpp
 * @brief Evidence report for validating one ASCC carrier view.
 */

namespace assembler::communication_context
{
    struct TCarrierValidationReport final
    {
        TCarrierView carrier_view{};
        TCarrierValidationResult result{};
        std::string_view report_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return result.is_valid();
        }

        [[nodiscard]] constexpr bool passed() const noexcept
        {
            return is_valid() && result.passed();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return is_valid() && result.failed();
        }

        [[nodiscard]] static constexpr TCarrierValidationReport make(
            TCarrierView view,
            TCarrierValidationResult validation_result,
            std::string_view note = {}) noexcept
        {
            return TCarrierValidationReport{view, validation_result, note};
        }
    };
}
