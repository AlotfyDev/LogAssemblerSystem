#pragma once
    #include <cstdint>

    /*
        TReadSideBackpressureState.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Read-side backpressure lifecycle state.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideBackpressureState : std::uint8_t {
        none, normal, pressure_detected, throttling, blocked, delegated, faulted
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
