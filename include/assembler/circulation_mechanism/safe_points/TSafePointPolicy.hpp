#pragma once

#include "TSafePointView.hpp"
#include "TSafePointClaim.hpp"

/*
    TSafePointPolicy.hpp

    Delivery:
        CME-SAFEPOINT-PROD-W01 — Production Guard And Claim Contract

    Current responsibility:
        Provides production-grade safe-point guard and claim helpers.

    Production capabilities:
        - Validate if an operation can be performed.
        - Validate if a safe point can be claimed for a specific kind.
        - Create claim artifact only from valid available view.
        - Keep operation execution outside the policy.

    Explicit non-ownership:
        - Does not execute guarded operations.
        - Does not mutate owner state.
        - Does not implement reset/scaling/eviction/rebuild/invalidation.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSafePointPolicy final
{
    [[nodiscard]] static constexpr bool can_perform(TSafePointView view, TSafePointKind requested_kind) noexcept
    {
        return view.can_claim_for(requested_kind).accepted;
    }

    [[nodiscard]] static constexpr TSafePointGuardResult validate_claim(TSafePointView view, TSafePointKind requested_kind) noexcept
    {
        return view.can_claim_for(requested_kind);
    }

    [[nodiscard]] static constexpr TSafePointClaim claim(TSafePointView view, TSafePointKind requested_kind) noexcept
    {
        return can_perform(view, requested_kind)
            ? TSafePointClaim{view.id(), requested_kind, view.generation()}
            : TSafePointClaim{TSafePointId::invalid(), requested_kind, 0U};
    }
};

} // namespace circulation_mechanism
} // namespace assembler
