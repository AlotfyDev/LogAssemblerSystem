#pragma once
#include "TFailedDispatchId.hpp"
#include "TFailedDispatchKind.hpp"
#include "TFailedDispatchState.hpp"
#include "../receiver_acknowledgement/TReceiverAcknowledgementState.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TFailedDispatchRecord final {
    TFailedDispatchId failed_dispatch_id{};
    TFailedDispatchKind kind{TFailedDispatchKind::none};
    TFailedDispatchState state{TFailedDispatchState::none};
    TReceiverAcknowledgementState acknowledgement_state{TReceiverAcknowledgementState::unknown};
    std::uint32_t retry_attempts_observed{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return failed_dispatch_id.is_valid(); }
    [[nodiscard]] constexpr bool retryable_kind() const noexcept { return kind == TFailedDispatchKind::bridge_not_consumed || kind == TFailedDispatchKind::receiver_not_ready || kind == TFailedDispatchKind::ack_timeout || kind == TFailedDispatchKind::persistence_not_ready || kind == TFailedDispatchKind::boundary_mismatch || kind == TFailedDispatchKind::unknown; }
    [[nodiscard]] constexpr bool retry_candidate() const noexcept { return is_valid() && retryable_kind() && (state == TFailedDispatchState::recorded || state == TFailedDispatchState::queued_for_retry) && acknowledgement_state != TReceiverAcknowledgementState::acknowledged && acknowledgement_state != TReceiverAcknowledgementState::rejected; }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
