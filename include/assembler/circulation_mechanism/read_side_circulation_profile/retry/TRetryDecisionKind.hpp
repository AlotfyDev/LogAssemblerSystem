#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TRetryDecisionKind : std::uint8_t { not_applicable, retry_allowed, retry_disabled, retry_exhausted, waiting_for_ack, receiver_rejected, manual_review_required };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
