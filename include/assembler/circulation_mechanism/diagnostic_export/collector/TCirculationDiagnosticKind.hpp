#pragma once
    #include <cstdint>

    /*
        TCirculationDiagnosticKind.hpp

        Delivery:
            CME-PROD-HARDEN-W03 — Unified Diagnostics Collector And Export Boundary

        Responsibility:
            Classifies unified circulation diagnostic kind.

        Explicit non-ownership:
            - Does not implement export sink runtime.
            - Does not execute recovery.
            - Does not mutate source systems.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

    enum class TCirculationDiagnosticKind : std::uint8_t {
        none, invariant_violation, configuration_issue, runtime_lifecycle_issue, boundary_issue, reference_issue, safe_point_issue, capacity_issue, read_side_issue, adapter_issue, anti_collapse_violation
    };
    } // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
