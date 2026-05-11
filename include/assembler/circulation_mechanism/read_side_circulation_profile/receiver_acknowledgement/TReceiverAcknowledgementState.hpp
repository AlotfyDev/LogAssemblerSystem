#pragma once
    #include <cstdint>
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReceiverAcknowledgementState : std::uint8_t { not_required, required, pending, acknowledged, rejected, timed_out, unknown };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
