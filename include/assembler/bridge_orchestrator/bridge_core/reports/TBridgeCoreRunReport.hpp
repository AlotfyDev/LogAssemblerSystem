#pragma once
#include <cstdint>
#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"

namespace assembler::communication_context
{
    struct TBridgeCoreRunReport final
    {
        TBridgeCoreResult final_result{};
        std::uint32_t attempted_steps{0u};
        std::uint32_t completed_steps{0u};
        bool terminal_reached{false};

        [[nodiscard]] constexpr bool completed() const noexcept
        {
            return terminal_reached && final_result.completed();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return final_result.failed() || final_result.rejected() || final_result.exhausted();
        }
    };
}
