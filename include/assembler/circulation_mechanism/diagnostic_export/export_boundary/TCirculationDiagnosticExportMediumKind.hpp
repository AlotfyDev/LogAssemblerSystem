#pragma once
    #include <cstdint>

    /*
        TCirculationDiagnosticExportMediumKind.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Responsibility:
            Classifies diagnostic export medium contracts.

        Explicit non-ownership:
            - Does not implement export sink runtime.
            - Does not execute recovery.
            - Does not mutate source systems.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

    enum class TCirculationDiagnosticExportMediumKind : std::uint8_t {
        none, memory_snapshot, callback_sink, file_sink_contract, open_telemetry_contract, diagnostic_sink_contract, custom
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
