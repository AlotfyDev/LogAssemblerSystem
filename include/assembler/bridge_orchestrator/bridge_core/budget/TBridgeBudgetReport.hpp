#pragma once
#include <cstdint>

namespace assembler::communication_context
{
    struct TBridgeBudgetReport final
    {
        std::uint32_t max_steps{0u};
        std::uint32_t consumed_steps{0u};
        std::uint32_t remaining_steps{0u};
        bool exhausted{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return max_steps > 0u;
        }
    };
}
