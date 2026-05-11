#pragma once
    #include <cstdint>

    /*
        TBackpressureDecisionKind.hpp
        Delivery: CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile
        Responsibility: Decision produced by backpressure profile.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TBackpressureDecisionKind : std::uint8_t {
        allow_admission, observe_only, block_admission, delay_release, route_to_retry, delegate_to_receiver, fault
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
