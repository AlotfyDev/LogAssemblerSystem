#pragma once
    #include <cstdint>

    /*
        TReadSideIntegrationDecisionKind.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Responsibility:
            Classifies integration readiness decision.

        Explicit non-ownership:
            - Does not execute addon behavior.
            - Does not write persistence.
            - Does not export telemetry.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TReadSideIntegrationDecisionKind : std::uint8_t {
        ready, blocked, deferred, diagnostic_only, requires_manual_review
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
