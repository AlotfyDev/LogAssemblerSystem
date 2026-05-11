#pragma once
    #include <cstdint>

    /*
        TReceiverLifecycleExpectation.hpp

        Delivery:
            CME-RSCP-PROD-W01 — ReadSide Profile Identity And Boundary Contracts

        Responsibility:
            Defines receiver lifecycle expectation.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReceiverLifecycleExpectation : std::uint8_t {
        none,
        ack_required,
        best_effort,
        delayed_ack,
        retry_capable,
        persistence_backed
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
