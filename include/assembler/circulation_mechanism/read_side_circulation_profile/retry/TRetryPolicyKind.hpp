#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TRetryPolicyKind : std::uint8_t { disabled, immediate, bounded_attempts, delayed, exponential_backoff_candidate, receiver_controlled, manual_review };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
