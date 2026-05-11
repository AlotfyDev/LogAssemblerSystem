#pragma once

    #include <cstdint>

    /*
        TViewStability.hpp

        Delivery:
            CME-VIEWS-PROD-W01 — Production Read-Only Projection Contract

        Current responsibility:
            Classifies the expected stability/lifetime semantics of a view.

        Production capabilities:
            - Describe whether a view is a snapshot or live read-only projection.
            - Support generation/round/profile scoped validation.
            - Support future stale-view diagnostics.

        Explicit non-ownership:
            - Does not expose mutable state.
            - Does not execute transitions.
            - Does not own diagnostics storage.
            - Does not prove report evidence.
    */

    namespace assembler {
namespace circulation_mechanism {


    enum class TViewStability : std::uint8_t
    {
        snapshot,
        live_readonly,
        round_scoped,
        profile_scoped,
        generation_scoped,
        diagnostic_snapshot
    };

    } // namespace circulation_mechanism
} // namespace assembler
