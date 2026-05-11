#pragma once
    #include <cstdint>

    /*
        TReceiverAdmissionRequestStatus.hpp

        Delivery:
            CME-READSIDE-PROD-W03 — ReadSide Backpressure And Receiver Admission Runtime

        Responsibility:
            Classifies receiver admission request status.

        Explicit non-ownership:
            - Does not execute receiver behavior.
            - Does not call bridge.
            - Does not schedule retry.
            - Does not persist payload.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReceiverAdmissionRequestStatus : std::uint8_t {
        undefined, ready, blocked, expired, invalid
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
