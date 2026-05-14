#pragma once
#include <string_view>
namespace assembler::communication_context
{
    enum class TCarrierFlowDirection { unknown, produced, consumed, observed, relayed };
    [[nodiscard]] constexpr std::string_view to_string(TCarrierFlowDirection direction) noexcept
    {
        switch (direction)
        {
            case TCarrierFlowDirection::unknown: return "unknown";
            case TCarrierFlowDirection::produced: return "produced";
            case TCarrierFlowDirection::consumed: return "consumed";
            case TCarrierFlowDirection::observed: return "observed";
            case TCarrierFlowDirection::relayed: return "relayed";
        }
        return "unknown";
    }
}
