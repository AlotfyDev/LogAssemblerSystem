#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideRetryIssueKind : std::uint8_t { none, retry_disabled, max_attempts_reached, receiver_ack_missing, receiver_rejected, bridge_boundary_missing, persistence_boundary_missing, retry_blocked, failed_dispatch_not_retryable };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
