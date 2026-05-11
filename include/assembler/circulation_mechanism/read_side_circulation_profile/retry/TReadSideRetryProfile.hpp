#pragma once
#include <cstdint>
#include "TRetryProfileId.hpp"
#include "TRetryPolicyKind.hpp"
#include "TRetryDecisionKind.hpp"
#include "../failed_dispatch/TFailedDispatchRecord.hpp"
#include "../receiver_acknowledgement/TReceiverAcknowledgementRecord.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideRetryProfile final {
    TRetryProfileId retry_profile_id{};
    TRetryPolicyKind policy_kind{TRetryPolicyKind::disabled};
    std::uint32_t max_attempts{0};
    bool requires_receiver_ack{false};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return retry_profile_id.is_valid(); }
    [[nodiscard]] constexpr bool retry_enabled() const noexcept { return policy_kind != TRetryPolicyKind::disabled && max_attempts > 0U; }
    [[nodiscard]] constexpr TRetryDecisionKind decide(TFailedDispatchRecord failed, TReceiverAcknowledgementRecord ack) const noexcept {
        if (!retry_enabled()) return TRetryDecisionKind::retry_disabled;
        if (!failed.retry_candidate()) return TRetryDecisionKind::not_applicable;
        if (requires_receiver_ack && ack.pending_or_required()) return TRetryDecisionKind::waiting_for_ack;
        if (ack.rejected()) return TRetryDecisionKind::receiver_rejected;
        if (failed.retry_attempts_observed >= max_attempts) return TRetryDecisionKind::retry_exhausted;
        if (policy_kind == TRetryPolicyKind::manual_review) return TRetryDecisionKind::manual_review_required;
        return TRetryDecisionKind::retry_allowed;
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
