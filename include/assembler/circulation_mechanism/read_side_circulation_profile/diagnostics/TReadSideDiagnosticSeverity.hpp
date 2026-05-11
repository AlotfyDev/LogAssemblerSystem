#pragma once
    #include <cstdint>

    /*
        TReadSideDiagnosticSeverity.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Responsibility:
            Defines read-side diagnostic severity.

        Explicit non-ownership:
            - Does not execute addon behavior.
            - Does not write persistence.
            - Does not export telemetry.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideDiagnosticSeverity : std::uint8_t {
        trace, info, warning, error, critical, fatal
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
