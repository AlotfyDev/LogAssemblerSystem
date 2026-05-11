#pragma once
    #include <cstdint>

    /*
        TReceiverAdmissionDecisionKind.hpp

        Delivery:
            CME-READSIDE-PROD-W03 — ReadSide Backpressure And Receiver Admission Runtime

        Responsibility:
            Classifies receiver admission decision outcome.

        Explicit non-ownership:
            - Does not execute receiver behavior.
            - Does not call bridge.
            - Does not schedule retry.
            - Does not persist payload.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReceiverAdmissionDecisionKind : std::uint8_t {
        not_evaluated, accept, reject_invalid_request, reject_no_capacity, reject_receiver_not_ready, delay_for_backpressure, route_to_retry, route_to_failed_dispatch, manual_review
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
