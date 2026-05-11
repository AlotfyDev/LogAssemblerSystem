#pragma once
    #include <cstdint>

    /*
        TReceiverBackpressureGateStatus.hpp

        Delivery:
            CME-READSIDE-PROD-W03 — ReadSide Backpressure And Receiver Admission Runtime

        Responsibility:
            Classifies receiver backpressure gate status.

        Explicit non-ownership:
            - Does not execute receiver behavior.
            - Does not call bridge.
            - Does not schedule retry.
            - Does not persist payload.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReceiverBackpressureGateStatus : std::uint8_t {
        undefined, ready, pressure_observed, admission_blocked, release_delayed, retry_pressure, delegated, faulted
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
