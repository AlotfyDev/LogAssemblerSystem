#pragma once
    #include <cstdint>

    /*
        TReadSideAdapterCapabilityKind.hpp

        Delivery:
            CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

        Responsibility:
            Classifies capabilities an adapter contract may declare.

        Explicit non-ownership:
            - Does not execute external I/O.
            - Does not implement database, file, telemetry, ABI, or diagnostic sink behavior.
            - Does not own receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReadSideAdapterCapabilityKind : std::uint8_t {
        accept_payload, acknowledge, reject, backpressure_signal, retry_signal, persist_snapshot, export_telemetry, write_file, emit_diagnostic, foreign_abi_call
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
