#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TFailedDispatchKind : std::uint8_t { none, bridge_not_consumed, receiver_not_ready, receiver_rejected, ack_timeout, persistence_not_ready, boundary_mismatch, retry_exhausted, unknown };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
