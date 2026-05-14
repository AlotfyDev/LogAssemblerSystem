#pragma once
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationResult.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
namespace assembler::communication_context
{
    struct TCarrierValidationEngine final
    {
        [[nodiscard]] static constexpr TCarrierValidationResult validate_view(TCarrierView view, TAsccCarrierKind expected) noexcept
        {
            if (!view.is_valid())
            {
                return TCarrierValidationResult::fail(expected, TBridgeError::make(TBridgeErrorCode::protocol_violation, "carrier view is invalid"));
            }
            if (expected == TAsccCarrierKind::unknown)
            {
                return TCarrierValidationResult::fail(expected, TBridgeError::make(TBridgeErrorCode::protocol_violation, "expected carrier kind is unknown"));
            }
            return TCarrierValidationResult::pass(expected);
        }
    };
}
