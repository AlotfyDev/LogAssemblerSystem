#pragma once
#include "TEvictionCandidateId.hpp"
#include "TEvictionCandidateStatus.hpp"
#include "TEvictionEvaluationStatus.hpp"
#include "assembler/circulation_mechanism/container/TContainerTimeRange.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TEvictionGuardStateHelpers.hpp"

/*
    TEvictionCandidate.hpp

    Delivery:
        CME-EVICTION-PROD-W01 — Production SafePoint Candidate Contract

    Current responsibility:
        Represents a safe-point-guarded container candidate for eviction.

    Production capabilities:
        - identifies container and registry index,
        - carries container/time/reference/round/exposure/safe-point state,
        - evaluates eviction eligibility,
        - classifies rejection reason,
        - supports time-range ordering.

    Explicit non-ownership:
        - Does not remove container.
        - Does not mutate registry.
        - Does not invalidate references.
        - Does not execute read-side retry.
*/
namespace assembler {
namespace circulation_mechanism {

struct TEvictionCandidate final {
    TEvictionCandidateId candidate_id{};
    TContainerId container_id{};
    TContainerRegistryIndex registry_index{};
    TContainerState container_state{TContainerState::inactive};
    TContainerTimeRange time_range{};
    TSafePointState safe_point_state{TSafePointState::unavailable};
    TReferenceValidityState reference_state{TReferenceValidityState::consumed};
    TRoundState round_state{TRoundState::idle};
    TDispatchExposureState exposure_state{TDispatchExposureState::closed};
    TEvictionCandidateStatus status{TEvictionCandidateStatus::not_evaluated};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return candidate_id.is_valid() && container_id.is_valid() && registry_index.is_valid();
    }

    [[nodiscard]] constexpr TEvictionEvaluationStatus evaluate(bool requires_orderable_time_range = false) const noexcept {
        if (!is_valid()) return TEvictionEvaluationStatus::rejected_invalid_candidate;
        if (!eviction_safe_point_available(safe_point_state)) return TEvictionEvaluationStatus::rejected_no_safe_point;
        if (container_active_in_ingress(container_state)) return TEvictionEvaluationStatus::rejected_active_ingress;
        if (container_active_in_dispatch(container_state)) return TEvictionEvaluationStatus::rejected_active_dispatch;
        if (!round_clear_for_eviction(round_state)) return TEvictionEvaluationStatus::rejected_active_round;
        if (!reference_cleared_for_eviction(reference_state)) return TEvictionEvaluationStatus::rejected_active_refs;
        if (!exposure_clear_for_eviction(exposure_state)) return TEvictionEvaluationStatus::rejected_active_dispatch;
        if (requires_orderable_time_range && !time_range.is_orderable()) return TEvictionEvaluationStatus::rejected_invalid_time_range;
        return TEvictionEvaluationStatus::accepted;
    }

    [[nodiscard]] constexpr bool safe_to_evict() const noexcept {
        return evaluate(false) == TEvictionEvaluationStatus::accepted;
    }

    [[nodiscard]] constexpr bool has_orderable_time_range() const noexcept {
        return time_range.is_orderable();
    }
};
} // namespace circulation_mechanism
} // namespace assembler
