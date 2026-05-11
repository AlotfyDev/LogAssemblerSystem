#pragma once
    #include <cstdint>

    /*
        TPostBridgeCapacityStatus.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Post-bridge capacity profile status.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TPostBridgeCapacityStatus : std::uint8_t {
        undefined, draft, ready, active, insufficient, blocked, invalid
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
