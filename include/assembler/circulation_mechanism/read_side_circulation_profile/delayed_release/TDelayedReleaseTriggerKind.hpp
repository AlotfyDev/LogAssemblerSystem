#pragma once
    #include <cstdint>

    /*
        TDelayedReleaseTriggerKind.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Delayed release trigger kind.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TDelayedReleaseTriggerKind : std::uint8_t {
        none, bridge_observation, receiver_acknowledgement, persistence_completion, retry_exhausted, manual_review, timeout
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
