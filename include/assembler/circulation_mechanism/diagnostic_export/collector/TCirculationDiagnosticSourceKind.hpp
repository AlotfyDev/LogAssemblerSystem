#pragma once
    #include <cstdint>

    /*
        TCirculationDiagnosticSourceKind.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Responsibility:
            Classifies diagnostic source area.

        Explicit non-ownership:
            - Does not implement export sink runtime.
            - Does not execute recovery.
            - Does not mutate source systems.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

    enum class TCirculationDiagnosticSourceKind : std::uint8_t {
        unknown, core, pre_bridge, read_side, communication_binding, adapter_boundary, test
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
