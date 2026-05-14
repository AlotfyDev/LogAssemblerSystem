#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationResult.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
namespace assembler::communication_context
{
    struct TCarrierValidationReport final
    {
        TCarrierView carrier_view{};
        TCarrierValidationResult result{};
        std::string_view report_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return carrier_view.is_valid() && result.carrier_kind != TAsccCarrierKind::unknown; }
        [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && result.passed(); }
    };
}
