#pragma once
    #include <cstdint>

    /*
        TCirculationDiagnosticSeverity.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Responsibility:
            Classifies diagnostic severity.

        Explicit non-ownership:
            - Does not implement export sink runtime.
            - Does not execute recovery.
            - Does not mutate source systems.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

    enum class TCirculationDiagnosticSeverity : std::uint8_t {
        trace, info, warning, error, critical, fatal
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
