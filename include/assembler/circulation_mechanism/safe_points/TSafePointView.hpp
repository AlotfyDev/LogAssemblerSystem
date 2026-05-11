#pragma once

#include "TSafePointId.hpp"
#include "TSafePointKind.hpp"
#include "assembler/circulation_mechanism/state/TSafePointState.hpp"
#include "TSafePointGuardResult.hpp"

/*
    TSafePointView.hpp

    Delivery:
        CME-SAFEPOINT-PROD-W01 — Production Guard And Claim Contract

    Current responsibility:
        Defines a production-grade read-only safe-point projection.

    Production capabilities:
        - Identifies safe point.
        - Declares protected operation kind.
        - Declares current safe-point state.
        - Classifies availability, claimability, consumption, violation.
        - Validates kind-specific guard requests.

    Architectural role:
        A safe point is a local condition that permits a sensitive operation.
        It is not the operation and not a global stop-the-world event unless a
        profile explicitly defines that elsewhere.

    Explicit non-ownership:
        - Does not perform reset/scaling/eviction/rebuild/invalidation.
        - Does not mutate component state.
        - Does not manage process/thread scheduling.
*/

namespace assembler {
namespace circulation_mechanism {


class TSafePointView final
{
public:
    constexpr TSafePointView() noexcept = default;

    constexpr TSafePointView(
        TSafePointId id,
        TSafePointKind kind,
        TSafePointState state,
        std::uint64_t generation = 0U) noexcept
        : id_(id),
          kind_(kind),
          state_(state),
          generation_(generation)
    {
    }

    [[nodiscard]] constexpr TSafePointId id() const noexcept { return id_; }
    [[nodiscard]] constexpr TSafePointKind kind() const noexcept { return kind_; }
    [[nodiscard]] constexpr TSafePointState state() const noexcept { return state_; }
    [[nodiscard]] constexpr std::uint64_t generation() const noexcept { return generation_; }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return id_.is_valid(); }
    [[nodiscard]] constexpr bool available() const noexcept { return state_ == TSafePointState::available; }
    [[nodiscard]] constexpr bool claimed() const noexcept { return state_ == TSafePointState::claimed; }
    [[nodiscard]] constexpr bool consumed() const noexcept { return state_ == TSafePointState::consumed; }
    [[nodiscard]] constexpr bool violated() const noexcept { return state_ == TSafePointState::violated; }
    [[nodiscard]] constexpr bool terminal() const noexcept
    {
        return state_ == TSafePointState::consumed
            || state_ == TSafePointState::expired
            || state_ == TSafePointState::violated;
    }

    [[nodiscard]] constexpr TSafePointGuardResult can_claim_for(TSafePointKind requested_kind) const noexcept
    {
        if (!id_.is_valid()) return rejected_safe_point(TSafePointIssueKind::invalid_id);
        if (requested_kind != kind_) return rejected_safe_point(TSafePointIssueKind::kind_mismatch);
        if (state_ == TSafePointState::claimed) return rejected_safe_point(TSafePointIssueKind::already_claimed);
        if (state_ == TSafePointState::consumed) return rejected_safe_point(TSafePointIssueKind::already_consumed);
        if (state_ == TSafePointState::expired) return rejected_safe_point(TSafePointIssueKind::expired);
        if (state_ == TSafePointState::violated) return rejected_safe_point(TSafePointIssueKind::violated);
        if (state_ != TSafePointState::available) return rejected_safe_point(TSafePointIssueKind::unavailable);
        return accepted_safe_point();
    }

private:
    TSafePointId id_{TSafePointId::invalid()};
    TSafePointKind kind_{TSafePointKind::container_reset};
    TSafePointState state_{TSafePointState::unavailable};
    std::uint64_t generation_{0};
};

} // namespace circulation_mechanism
} // namespace assembler
