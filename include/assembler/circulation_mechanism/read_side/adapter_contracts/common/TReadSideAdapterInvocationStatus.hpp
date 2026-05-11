#pragma once
    #include <cstdint>

    /*
        TReadSideAdapterInvocationStatus.hpp

        Delivery:
            CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

        Responsibility:
            Classifies adapter contract invocation evaluation result.

        Explicit non-ownership:
            - Does not execute external I/O.
            - Does not implement database, file, telemetry, ABI, or diagnostic sink behavior.
            - Does not own receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReadSideAdapterInvocationStatus : std::uint8_t {
        not_attempted, accepted, rejected_invalid_contract, rejected_not_ready, rejected_capability_missing, rejected_payload_invalid, rejected_external_runtime_required, deferred
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
