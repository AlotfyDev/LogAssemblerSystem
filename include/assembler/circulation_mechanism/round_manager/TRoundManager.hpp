#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "TRoundKind.hpp"
#include "TRoundAdmissionDecisionKind.hpp"
#include "TRoundLifecycleStatus.hpp"
#include "TRoundView.hpp"
#include "TRoundAdmissionReport.hpp"
#include "TRoundClosureReport.hpp"
#include "TRoundMembershipView.hpp"
#include "assembler/circulation_mechanism/ids/TRoundId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TRoundState.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"

/*
    TRoundManager.hpp

    Delivery:
        CME-ROUNDMANAGER-PROD-W01 — Production Membership And Round Lifecycle Contract

    Current responsibility:
        Production-grade round membership and lifecycle manager.

    Production capabilities:
        - round identity/kind/state,
        - open/lock/drain/close/complete lifecycle,
        - container candidate admission validation,
        - duplicate rejection,
        - capacity rejection,
        - membership view,
        - admission and closure reports,
        - ingress vs dispatch eligibility rules.

    Explicit non-ownership:
        - Does not create containers.
        - Does not reset containers.
        - Does not store payloads.
        - Does not calculate access references.
        - Does not execute ingress or dispatch.
        - Does not own bridge handoff or receiver lifecycle.
*/
namespace assembler {
namespace circulation_mechanism {

template <std::size_t MaxMembers>
class TRoundManager final {
public:
    static_assert(MaxMembers > 0U, "Round member capacity must be greater than zero.");

    constexpr TRoundManager(TRoundId id, TRoundKind kind) noexcept : id_(id), kind_(kind) {
        state_ = id_.is_valid() ? TRoundState::idle : TRoundState::invariant_violation;
        generation_ = id_.is_valid() ? 1U : 0U;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return id_.is_valid() && generation_ > 0U; }
    [[nodiscard]] constexpr TRoundState state() const noexcept { return state_; }
    [[nodiscard]] constexpr TRoundKind kind() const noexcept { return kind_; }
    [[nodiscard]] constexpr std::uint32_t member_count() const noexcept { return member_count_; }

    [[nodiscard]] constexpr TRoundView view() const noexcept {
        return TRoundView{id_, kind_, state_, member_count_, static_cast<std::uint32_t>(MaxMembers), generation_};
    }

    constexpr TRoundLifecycleStatus begin_collecting() noexcept {
        return transition_to(TRoundState::collecting_candidates);
    }

    constexpr TRoundLifecycleStatus open() noexcept {
        return transition_to(TRoundState::open);
    }

    constexpr TRoundAdmissionReport admit(TContainerRegistryIndex candidate, TContainerState container_state) noexcept {
        if (!is_valid()) return {id_, kind_, candidate, TRoundAdmissionDecisionKind::rejected_invalid_round, member_count_};
        if (!candidate.is_valid()) return {id_, kind_, candidate, TRoundAdmissionDecisionKind::rejected_invalid_index, member_count_};
        if (!round_accepts_candidates(state_)) return {id_, kind_, candidate, TRoundAdmissionDecisionKind::rejected_round_closed, member_count_};
        if (!container_state_matches_round(container_state)) return {id_, kind_, candidate, TRoundAdmissionDecisionKind::rejected_state_not_eligible, member_count_};
        if (contains(candidate)) return {id_, kind_, candidate, TRoundAdmissionDecisionKind::rejected_duplicate, member_count_};
        if (member_count_ >= MaxMembers) return {id_, kind_, candidate, TRoundAdmissionDecisionKind::rejected_membership_full, member_count_};
        members_[member_count_++] = candidate;
        return {id_, kind_, candidate, TRoundAdmissionDecisionKind::accepted, member_count_};
    }

    constexpr TRoundLifecycleStatus lock_membership() noexcept {
        if (member_count_ == 0U) return TRoundLifecycleStatus::rejected_empty_membership;
        return transition_to(TRoundState::locked);
    }

    constexpr TRoundLifecycleStatus mark_draining() noexcept {
        if (state_ != TRoundState::locked) return TRoundLifecycleStatus::rejected_not_locked;
        return transition_to(TRoundState::draining);
    }

    constexpr TRoundClosureReport close() noexcept {
        const auto before = state_;
        auto status = transition_to(TRoundState::closed);
        return {id_, kind_, before, state_, status};
    }

    constexpr TRoundClosureReport complete() noexcept {
        const auto before = state_;
        auto status = transition_to(TRoundState::completed);
        return {id_, kind_, before, state_, status};
    }

    [[nodiscard]] constexpr TRoundMembershipView<MaxMembers> membership_view() const noexcept {
        return TRoundMembershipView<MaxMembers>{members_, member_count_};
    }

private:
    [[nodiscard]] constexpr bool container_state_matches_round(TContainerState s) const noexcept {
        return kind_ == TRoundKind::ingress ? ingress_round_eligible(s) : dispatch_round_eligible(s);
    }

    [[nodiscard]] constexpr bool contains(TContainerRegistryIndex idx) const noexcept {
        for (std::uint32_t i = 0; i < member_count_; ++i) {
            if (members_[i] == idx) return true;
        }
        return false;
    }

    constexpr TRoundLifecycleStatus transition_to(TRoundState next) noexcept {
        if (!is_valid()) return TRoundLifecycleStatus::rejected_invalid_round;
        if (!can_transition(state_, next)) return TRoundLifecycleStatus::rejected_invalid_transition;
        state_ = next;
        ++generation_;
        return TRoundLifecycleStatus::accepted;
    }

    TRoundId id_{TRoundId::invalid()};
    TRoundKind kind_{TRoundKind::ingress};
    TRoundState state_{TRoundState::idle};
    std::array<TContainerRegistryIndex, MaxMembers> members_{};
    std::uint32_t member_count_{0};
    std::uint64_t generation_{0};
};
} // namespace circulation_mechanism
} // namespace assembler
