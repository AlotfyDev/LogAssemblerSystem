#pragma once
    #include <cstdint>

    /*
        TCirculationDiagnosticExportStatus.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Responsibility:
            Classifies export boundary readiness.

        Explicit non-ownership:
            - Does not implement export sink runtime.
            - Does not execute recovery.
            - Does not mutate source systems.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

    enum class TCirculationDiagnosticExportStatus : std::uint8_t {
        undefined, declared, ready, blocked, deferred, failed
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
