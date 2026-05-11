#pragma once
#include "assembler/circulation_mechanism/release_recycle/TReleaseRecycleId.hpp"
#include "assembler/circulation_mechanism/release_recycle/TReleaseKind.hpp"
#include "assembler/circulation_mechanism/release_recycle/TRecycleState.hpp"

/*
    TReleaseRecycleView.hpp

    Delivery:
        CME-RELEASE-RECYCLE-PROD-W01 — Production Lifecycle Contract

    Responsibility:
        Read-only projection of release/recycle state.

    Non-ownership:
        Does not execute release/recycle/reset/reentry.
*/
namespace assembler {
namespace circulation_mechanism {

struct TReleaseRecycleView final {
    TReleaseRecycleId id{};
    TReleaseKind kind{TReleaseKind::container_release};
    TRecycleState state{TRecycleState::not_recyclable};
    bool active_references_cleared{false};
    bool exposure_closed{false};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return id.is_valid(); }
    [[nodiscard]] constexpr bool released() const noexcept { return state == TRecycleState::released || state == TRecycleState::recyclable || state == TRecycleState::reset_pending || state == TRecycleState::default_empty || state == TRecycleState::reentry_eligible; }
    [[nodiscard]] constexpr bool can_recycle() const noexcept { return state == TRecycleState::recyclable || state == TRecycleState::reset_pending; }
    [[nodiscard]] constexpr bool can_reenter() const noexcept { return state == TRecycleState::default_empty || state == TRecycleState::reentry_eligible; }
};
} // namespace circulation_mechanism
} // namespace assembler
