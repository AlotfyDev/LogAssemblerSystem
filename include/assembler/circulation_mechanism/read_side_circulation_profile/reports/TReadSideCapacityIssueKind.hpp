#pragma once
    #include <cstdint>

    /*
        TReadSideCapacityIssueKind.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Read-side capacity/backpressure/delayed-release issue kind.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideCapacityIssueKind : std::uint8_t {
        none, backpressure_detected, receiver_not_ready, capacity_insufficient, delayed_release_blocked, release_timeout, persistence_pending, unknown_receiver_capacity, admission_blocked, retry_pressure_active
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
