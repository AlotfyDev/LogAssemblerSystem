#pragma once
    #include <cstdint>

    /*
        TReadSideAdapterIssueKind.hpp

        Delivery:
            CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts

        Responsibility:
            Classifies read-side adapter contract report issues.

        Explicit non-ownership:
            - Does not execute external I/O.
            - Does not implement database, file, telemetry, ABI, or diagnostic sink behavior.
            - Does not own receiver lifecycle.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side {

    enum class TReadSideAdapterIssueKind : std::uint8_t {
        none, invalid_contract, adapter_not_ready, capability_missing, payload_invalid, external_runtime_required, boundary_mismatch, unsupported_operation
    };
    } // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
