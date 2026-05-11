#pragma once
#include "TDelayedReleaseRecordId.hpp"
#include "TDelayedReleaseState.hpp"
#include "TDelayedReleaseTriggerKind.hpp"
#include "TDelayedReleaseDecisionKind.hpp"

/*
    TDelayedReleaseRecord.hpp

    Responsibility:
        State record for a delayed release.

    Non-ownership:
        Does not release or call receiver/persistence.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TDelayedReleaseRecord final {
    TDelayedReleaseRecordId record_id{};
    TDelayedReleaseState state{TDelayedReleaseState::not_delayed};
    TDelayedReleaseTriggerKind expected_trigger{TDelayedReleaseTriggerKind::none};
    std::uint32_t elapsed_ticks{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return record_id.is_valid(); }
    [[nodiscard]] constexpr bool pending() const noexcept {
        return state == TDelayedReleaseState::pending || state == TDelayedReleaseState::waiting_for_trigger;
    }
    constexpr void apply_decision(TDelayedReleaseDecisionKind decision) noexcept {
        if (decision == TDelayedReleaseDecisionKind::release_now) state = TDelayedReleaseState::released;
        else if (decision == TDelayedReleaseDecisionKind::expired) state = TDelayedReleaseState::expired;
        else if (decision == TDelayedReleaseDecisionKind::blocked) state = TDelayedReleaseState::blocked;
        else if (decision == TDelayedReleaseDecisionKind::wait_for_trigger) state = TDelayedReleaseState::waiting_for_trigger;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
