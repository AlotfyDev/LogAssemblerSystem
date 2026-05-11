#pragma once
#include <cstdint>
#include "TRetryAttemptId.hpp"
#include "TRetryAttemptState.hpp"
#include "../failed_dispatch/TFailedDispatchId.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TRetryAttempt final {
    TRetryAttemptId retry_attempt_id{};
    TFailedDispatchId failed_dispatch_id{};
    TRetryAttemptState state{TRetryAttemptState::not_started};
    std::uint32_t attempt_number{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return retry_attempt_id.is_valid() && failed_dispatch_id.is_valid() && attempt_number > 0U; }
    [[nodiscard]] constexpr bool terminal() const noexcept { return state == TRetryAttemptState::succeeded || state == TRetryAttemptState::exhausted || state == TRetryAttemptState::cancelled; }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
