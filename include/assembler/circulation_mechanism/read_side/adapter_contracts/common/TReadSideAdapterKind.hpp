#pragma once
    #include <cstdint>

    /*
        TReadSideAdapterKind.hpp

        Delivery:
            CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

        Responsibility:
            Classifies read-side adapter contract kind.

        Explicit non-ownership:
            - Does not execute external I/O.
            - Does not implement database, file, telemetry, ABI, or diagnostic sink behavior.
            - Does not own receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReadSideAdapterKind : std::uint8_t {
        unknown, in_process_receiver, database_adapter, file_sink_adapter, open_telemetry_adapter, diagnostic_sink_adapter, thin_c_abi_adapter, custom
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
