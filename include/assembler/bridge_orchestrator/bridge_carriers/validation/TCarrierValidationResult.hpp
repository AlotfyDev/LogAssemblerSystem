#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
namespace assembler::communication_context
{
    struct TCarrierValidationResult final
    {
        TAsccCarrierKind carrier_kind{TAsccCarrierKind::unknown};
        bool valid{false};
        TBridgeError error{TBridgeError::none()};
        std::string_view note{};
        [[nodiscard]] constexpr bool passed() const noexcept { return valid && !error.has_error(); }
        [[nodiscard]] static constexpr TCarrierValidationResult pass(TAsccCarrierKind kind, std::string_view text = {}) noexcept { return {kind, true, TBridgeError::none(), text}; }
        [[nodiscard]] static constexpr TCarrierValidationResult fail(TAsccCarrierKind kind, TBridgeError reason, std::string_view text = {}) noexcept { return {kind, false, reason, text}; }
    };
}
