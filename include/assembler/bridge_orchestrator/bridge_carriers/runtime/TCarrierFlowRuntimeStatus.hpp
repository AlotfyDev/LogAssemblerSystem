#pragma once
#include <string_view>
namespace assembler::communication_context
{
    enum class TCarrierFlowRuntimeStatus { unknown, idle, accepting, validating, recording, blocked, completed, failed };
    [[nodiscard]] constexpr std::string_view to_string(TCarrierFlowRuntimeStatus status) noexcept
    {
        switch (status)
        {
            case TCarrierFlowRuntimeStatus::unknown: return "unknown";
            case TCarrierFlowRuntimeStatus::idle: return "idle";
            case TCarrierFlowRuntimeStatus::accepting: return "accepting";
            case TCarrierFlowRuntimeStatus::validating: return "validating";
            case TCarrierFlowRuntimeStatus::recording: return "recording";
            case TCarrierFlowRuntimeStatus::blocked: return "blocked";
            case TCarrierFlowRuntimeStatus::completed: return "completed";
            case TCarrierFlowRuntimeStatus::failed: return "failed";
        }
        return "unknown";
    }
}
