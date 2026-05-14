#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowDirection.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
namespace assembler::communication_context
{
    struct TCarrierFlowRecord final
    {
        TCarrierView carrier{};
        TCarrierFlowDirection direction{TCarrierFlowDirection::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view participant_label{};
        std::string_view note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return carrier.is_valid() && direction != TCarrierFlowDirection::unknown && correlation.is_valid(); }
    };
}
