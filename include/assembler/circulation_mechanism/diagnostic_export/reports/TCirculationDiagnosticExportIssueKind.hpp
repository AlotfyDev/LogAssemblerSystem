#pragma once
    #include <cstdint>

    /*
        TCirculationDiagnosticExportIssueKind.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Responsibility:
            Classifies diagnostic export boundary issues.

        Explicit non-ownership:
            - Does not implement export sink runtime.
            - Does not execute recovery.
            - Does not mutate source systems.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

    enum class TCirculationDiagnosticExportIssueKind : std::uint8_t {
        none, collector_invalid, boundary_invalid, boundary_not_ready, medium_not_supported, snapshot_empty, export_runtime_missing, anti_recovery_violation
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
