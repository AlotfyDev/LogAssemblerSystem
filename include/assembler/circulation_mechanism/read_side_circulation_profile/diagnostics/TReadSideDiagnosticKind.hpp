#pragma once
    #include <cstdint>

    /*
        TReadSideDiagnosticKind.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Responsibility:
            Classifies read-side diagnostic conditions.

        Explicit non-ownership:
            - Does not execute addon behavior.
            - Does not write persistence.
            - Does not export telemetry.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideDiagnosticKind : std::uint8_t {
        none, receiver_delay, retry_blocked, failed_dispatch_unresolved, backpressure_active, delayed_release_blocked, addon_boundary_mismatch, persistence_boundary_pending, telemetry_boundary_pending, diagnostic_sink_pending, unknown
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
