#pragma once
#include "assembler/communication_context/bridge_core/budget/TBridgeBudgetReport.hpp"
#include "assembler/communication_context/bridge_core/budget/TBridgeStepBudget.hpp"

namespace assembler::communication_context
{
    struct TBridgeBudgetPolicy final
    {
        [[nodiscard]] static constexpr bool can_consume(TBridgeStepBudget budget) noexcept
        {
            return budget.is_valid() && !budget.exhausted();
        }

        [[nodiscard]] static constexpr TBridgeBudgetReport report(TBridgeStepBudget budget) noexcept
        {
            return {budget.max_steps, budget.consumed_steps, budget.remaining(), budget.exhausted()};
        }
    };
}
