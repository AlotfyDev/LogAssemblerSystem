#pragma once
    #include <cstdint>

    /*
        TReadSideIntegrationIssueKind.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Responsibility:
            Classifies read-side integration issues.

        Explicit non-ownership:
            - Does not execute addon behavior.
            - Does not write persistence.
            - Does not export telemetry.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideIntegrationIssueKind : std::uint8_t {
        none, missing_addon_boundary, addon_not_ready, unsupported_receiver_lifecycle, persistence_boundary_missing, telemetry_boundary_missing, diagnostic_sink_missing, boundary_mismatch, diagnostic_issue_present
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
