#pragma once
#include "TDelayedReleaseProfileId.hpp"
#include "TDelayedReleaseTriggerKind.hpp"
#include "TDelayedReleaseDecisionKind.hpp"

/*
    TDelayedReleaseProfile.hpp

    Responsibility:
        Delayed-release trigger policy descriptor and decision contract.

    Non-ownership:
        Does not execute release or call external systems.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TDelayedReleaseProfile final {
    TDelayedReleaseProfileId profile_id{};
    TDelayedReleaseTriggerKind trigger{TDelayedReleaseTriggerKind::none};
    bool enabled{false};
    std::uint32_t timeout_ticks{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile_id.is_valid(); }

    [[nodiscard]] constexpr bool requires_external_trigger() const noexcept {
        return trigger == TDelayedReleaseTriggerKind::receiver_acknowledgement
            || trigger == TDelayedReleaseTriggerKind::persistence_completion
            || trigger == TDelayedReleaseTriggerKind::bridge_observation;
    }

    [[nodiscard]] constexpr TDelayedReleaseDecisionKind decide(bool trigger_observed, std::uint32_t elapsed_ticks) const noexcept {
        if (!enabled || trigger == TDelayedReleaseTriggerKind::none) return TDelayedReleaseDecisionKind::not_applicable;
        if (trigger == TDelayedReleaseTriggerKind::manual_review) return TDelayedReleaseDecisionKind::manual_review_required;
        if (trigger_observed) return TDelayedReleaseDecisionKind::release_now;
        if (timeout_ticks > 0U && elapsed_ticks >= timeout_ticks) return TDelayedReleaseDecisionKind::expired;
        return TDelayedReleaseDecisionKind::wait_for_trigger;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
