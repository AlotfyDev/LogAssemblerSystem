#pragma once
    #include <cstdint>

    /*
        TReadSideBackpressureMode.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Read-side backpressure response mode.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideBackpressureMode : std::uint8_t {
        disabled, observe_only, block_admission, delay_release, retry_pressure, receiver_controlled
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
