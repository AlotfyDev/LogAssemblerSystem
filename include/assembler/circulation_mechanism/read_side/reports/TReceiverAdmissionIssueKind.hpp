#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

enum class TReceiverAdmissionIssueKind : std::uint8_t { none, invalid_request, no_capacity, receiver_not_ready, backpressure_blocked, retry_required, manual_review };
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
