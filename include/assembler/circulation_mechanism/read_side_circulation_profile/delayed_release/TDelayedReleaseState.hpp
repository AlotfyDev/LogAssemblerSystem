#pragma once
    #include <cstdint>

    /*
        TDelayedReleaseState.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Delayed release state.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TDelayedReleaseState : std::uint8_t {
        not_delayed, pending, waiting_for_trigger, released, expired, blocked, faulted
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
