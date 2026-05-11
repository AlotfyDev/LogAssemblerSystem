#pragma once
    #include <cstdint>

    /*
        TReadSideAdapterStatus.hpp

        Delivery:
            CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

        Responsibility:
            Classifies adapter contract readiness status.

        Explicit non-ownership:
            - Does not execute external I/O.
            - Does not implement database, file, telemetry, ABI, or diagnostic sink behavior.
            - Does not own receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReadSideAdapterStatus : std::uint8_t {
        undefined, declared, ready, blocked, mismatch, deferred, closed
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
