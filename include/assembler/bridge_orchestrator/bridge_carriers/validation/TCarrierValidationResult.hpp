#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"

/**
 * @file TCarrierValidationResult.hpp
 * @brief Result of validating one ASCC carrier contract for runtime use.
 */

namespace assembler::communication_context
{
    enum class TCarrierValidationStatus
    {
        unknown,
        passed,
        invalid_kind,
        invalid_correlation,
        invalid_shape,
        wrong_kind,
        failed
    };

    struct TCarrierValidationResult final
    {
        TAsccCarrierKind carrier_kind{TAsccCarrierKind::unknown};
        TCarrierValidationStatus status{TCarrierValidationStatus::unknown};
        TBridgeError error{TBridgeError::none()};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return carrier_kind != TAsccCarrierKind::unknown
                && status != TCarrierValidationStatus::unknown;
        }

        [[nodiscard]] constexpr bool passed() const noexcept
        {
            return status == TCarrierValidationStatus::passed
                && !error.has_error();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !passed();
        }

        [[nodiscard]] static constexpr TCarrierValidationResult pass(
            TAsccCarrierKind kind,
            std::string_view text = "carrier validation passed") noexcept
        {
            return TCarrierValidationResult{
                kind,
                TCarrierValidationStatus::passed,
                TBridgeError::none(),
                text
            };
        }

        [[nodiscard]] static constexpr TCarrierValidationResult fail(
            TAsccCarrierKind kind,
            TCarrierValidationStatus validation_status,
            TBridgeError reason,
            std::string_view text = {}) noexcept
        {
            return TCarrierValidationResult{
                kind,
                validation_status,
                reason,
                text.empty() ? reason.message : text
            };
        }
    };
}
