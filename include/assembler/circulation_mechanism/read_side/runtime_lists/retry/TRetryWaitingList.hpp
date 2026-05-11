#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "assembler/circulation_mechanism/read_side_circulation_profile/retry/TRetryAttempt.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/retry/TReadSideRetryProfile.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/receiver_acknowledgement/TReceiverAcknowledgementRecord.hpp"
#include "assembler/circulation_mechanism/read_side/runtime_lists/TReadSideListOperationResult.hpp"

/*
    TRetryWaitingList.hpp

    Current responsibility:
        Fixed-capacity runtime list for retry attempts.

    Production capabilities:
        - creates retry attempts from failed-dispatch records when policy allows,
        - stores retry attempts FIFO,
        - rejects terminal attempts,
        - supports pop-front,
        - does not execute retry.

    Explicit non-ownership:
        - Does not schedule threads.
        - Does not call receiver or bridge.
        - Does not move payload.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

template <std::size_t Capacity>
class TRetryWaitingList final {
public:
    static_assert(Capacity > 0U, "Capacity must be greater than zero.");

    [[nodiscard]] constexpr std::uint32_t size() const noexcept { return size_; }
    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0U; }
    [[nodiscard]] constexpr bool full() const noexcept { return size_ >= Capacity; }

    constexpr TReadSideListOperationResult push(read_side_circulation_profile::TRetryAttempt attempt) noexcept {
        if (!attempt.is_valid()) return {TReadSideListStatus::rejected_invalid_record, size_};
        if (attempt.terminal()) return {TReadSideListStatus::rejected_terminal, size_};
        if (full()) return {TReadSideListStatus::rejected_full, size_};
        attempts_[size_++] = attempt;
        return {TReadSideListStatus::accepted, size_};
    }

    constexpr TReadSideListOperationResult enqueue_from_failed_dispatch(
        read_side_circulation_profile::TFailedDispatchRecord failed,
        read_side_circulation_profile::TReadSideRetryProfile profile,
        read_side_circulation_profile::TReceiverAcknowledgementRecord ack,
        read_side_circulation_profile::TRetryAttemptId attempt_id) noexcept
    {
        if (full()) return {TReadSideListStatus::rejected_full, size_};
        const auto decision = profile.decide(failed, ack);
        if (decision != read_side_circulation_profile::TRetryDecisionKind::retry_allowed) {
            return {TReadSideListStatus::rejected_not_retryable, size_};
        }
        return push(read_side_circulation_profile::TRetryAttempt{attempt_id, failed.failed_dispatch_id, read_side_circulation_profile::TRetryAttemptState::scheduled, failed.retry_attempts_observed + 1U});
    }

    [[nodiscard]] constexpr const read_side_circulation_profile::TRetryAttempt* front() const noexcept {
        return size_ > 0U ? &attempts_[0] : nullptr;
    }

    constexpr TReadSideListOperationResult pop_front() noexcept {
        if (empty()) return {TReadSideListStatus::rejected_empty, size_};
        for (std::uint32_t i = 1; i < size_; ++i) {
            attempts_[i - 1] = attempts_[i];
        }
        --size_;
        return {TReadSideListStatus::accepted, size_};
    }

private:
    std::array<read_side_circulation_profile::TRetryAttempt, Capacity> attempts_{};
    std::uint32_t size_{0};
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
