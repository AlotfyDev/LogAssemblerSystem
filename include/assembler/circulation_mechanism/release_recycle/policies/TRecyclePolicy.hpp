#pragma once
#include "assembler/circulation_mechanism/release_recycle/TReleaseRecycleRecord.hpp"
#include "assembler/circulation_mechanism/release_recycle/views/TReleaseRecycleView.hpp"
#include "assembler/circulation_mechanism/state/TReleaseRecycleStateHelpers.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
#include "assembler/circulation_mechanism/state/TReferenceValidityState.hpp"
#include "assembler/circulation_mechanism/state/TDispatchExposureState.hpp"
#include "assembler/circulation_mechanism/state/TRoundState.hpp"
#include "assembler/circulation_mechanism/state/TSafePointState.hpp"

/*
    TRecyclePolicy.hpp

    Delivery:
        CME-RELEASE-RECYCLE-PROD-W01 — Production Lifecycle Contract

    Responsibility:
        Provides pure functions for validating release/recycle/reset/reentry lifecycle.

    Non-ownership:
        Does not mutate containers, references, registry, bridge, or receiver.
*/
namespace assembler {
namespace circulation_mechanism {

struct TRecyclePolicy final {
    [[nodiscard]] static constexpr TReleaseRecycleStatus can_release_reference(TReferenceValidityState state) noexcept {
        return reference_released(state) ? TReleaseRecycleStatus::accepted : TReleaseRecycleStatus::rejected_active_reference;
    }

    [[nodiscard]] static constexpr TReleaseRecycleStatus can_release_exposure(TDispatchExposureState state) noexcept {
        return exposure_release_ready(state) ? TReleaseRecycleStatus::accepted : TReleaseRecycleStatus::rejected_active_exposure;
    }

    [[nodiscard]] static constexpr TReleaseRecycleStatus can_release_round(TRoundState state) noexcept {
        return round_release_ready(state) ? TReleaseRecycleStatus::accepted : TReleaseRecycleStatus::rejected_not_releasable;
    }

    [[nodiscard]] static constexpr TReleaseRecycleStatus can_reset_container(TContainerState container_state, TSafePointState safe_point) noexcept {
        if (!container_release_ready(container_state)) return TReleaseRecycleStatus::rejected_not_resettable;
        if (!safe_point_available(safe_point)) return TReleaseRecycleStatus::rejected_missing_safe_point;
        return TReleaseRecycleStatus::accepted;
    }

    [[nodiscard]] static constexpr TReleaseRecycleStatus can_recycle(TReleaseRecycleView view, TSafePointState safe_point) noexcept {
        if (!view.is_valid()) return TReleaseRecycleStatus::rejected_invalid_id;
        if (!view.active_references_cleared) return TReleaseRecycleStatus::rejected_active_reference;
        if (!view.exposure_closed) return TReleaseRecycleStatus::rejected_active_exposure;
        if (!view.can_recycle()) return TReleaseRecycleStatus::rejected_not_recyclable;
        if (!safe_point_available(safe_point)) return TReleaseRecycleStatus::rejected_missing_safe_point;
        return TReleaseRecycleStatus::accepted;
    }

    [[nodiscard]] static constexpr TReleaseRecycleStatus can_reenter(TContainerState container_state, bool reset_applied) noexcept {
        return reset_applied && (container_state == TContainerState::default_empty || container_state == TContainerState::ingress_ready)
            ? TReleaseRecycleStatus::accepted
            : TReleaseRecycleStatus::rejected_not_reentry_eligible;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
