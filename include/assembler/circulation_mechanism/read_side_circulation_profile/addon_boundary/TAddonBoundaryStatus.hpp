#pragma once
    #include <cstdint>

    /*
        TAddonBoundaryStatus.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Responsibility:
            Defines addon boundary readiness state.

        Explicit non-ownership:
            - Does not execute addon behavior.
            - Does not write persistence.
            - Does not export telemetry.
            - Does not invoke bridge or receiver.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

    enum class TAddonBoundaryStatus : std::uint8_t {
        undefined, declared, ready, blocked, mismatch, deferred, closed
    };
    } // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
