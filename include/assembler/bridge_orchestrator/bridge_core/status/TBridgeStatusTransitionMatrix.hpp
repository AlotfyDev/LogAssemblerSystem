#pragma once
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"

namespace assembler::communication_context
{
    struct TBridgeStatusTransitionMatrix final
    {
        [[nodiscard]] static constexpr bool can_transition(TBridgeStatus from, TBridgeStatus to) noexcept
        {
            if (from == to) return true;
            if (is_terminal_bridge_status(from)) return false;

            switch (from)
            {
                case TBridgeStatus::unknown:
                    return to == TBridgeStatus::declared || to == TBridgeStatus::ready || to == TBridgeStatus::rejected;
                case TBridgeStatus::declared:
                    return to == TBridgeStatus::ready || to == TBridgeStatus::rejected || to == TBridgeStatus::failed;
                case TBridgeStatus::ready:
                    return to == TBridgeStatus::running || to == TBridgeStatus::failed || to == TBridgeStatus::exhausted || to == TBridgeStatus::cancelled;
                case TBridgeStatus::running:
                    return to == TBridgeStatus::completed || to == TBridgeStatus::failed || to == TBridgeStatus::rejected || to == TBridgeStatus::exhausted || to == TBridgeStatus::paused;
                case TBridgeStatus::paused:
                    return to == TBridgeStatus::running || to == TBridgeStatus::cancelled || to == TBridgeStatus::failed;
                case TBridgeStatus::completed:
                case TBridgeStatus::rejected:
                case TBridgeStatus::failed:
                case TBridgeStatus::exhausted:
                case TBridgeStatus::cancelled:
                    return false;
            }

            return false;
        }
    };
}
