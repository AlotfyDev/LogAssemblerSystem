#pragma once

#include "TSafePointId.hpp"
#include "TSafePointKind.hpp"
#include "assembler/circulation_mechanism/state/TSafePointState.hpp"
#include "TSafePointIssueKind.hpp"

/*
    TSafePointViolationReport.hpp

    Delivery:
        CME-SAFEPOINT-PROD-W01 — Production Guard And Claim Contract

    Current responsibility:
        Records evidence that a guarded operation was attempted without a valid
        safe point.

    Production capabilities:
        - Capture required kind.
        - Capture observed state.
        - Capture issue classification.
        - Indicate whether operation must be blocked.

    Explicit non-ownership:
        - Does not recover.
        - Does not execute operation.
        - Does not mutate component state.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSafePointViolationReport final
{
    TSafePointId safe_point_id{};
    TSafePointKind required_kind{TSafePointKind::container_reset};
    TSafePointState observed_state{TSafePointState::violated};
    TSafePointIssueKind issue{TSafePointIssueKind::violated};
    bool block_operation{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return safe_point_id.is_valid();
    }

    [[nodiscard]] constexpr bool should_block() const noexcept
    {
        return block_operation && issue != TSafePointIssueKind::none;
    }
};

} // namespace circulation_mechanism
} // namespace assembler
