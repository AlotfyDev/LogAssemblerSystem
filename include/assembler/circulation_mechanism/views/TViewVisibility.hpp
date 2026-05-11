#pragma once

    #include <cstdint>

    /*
        TViewVisibility.hpp

        Delivery:
            CME-VIEWS-PROD-W01 — Production Read-Only Projection Contract

        Current responsibility:
            Classifies the intended visibility of a view surface.

        Production capabilities:
            - Govern whether a view may cross component boundaries.
            - Govern whether a view is safe for boundary exposure.
            - Support anti-mutation and anti-leakage checks.

        Explicit non-ownership:
            - Does not expose mutable state.
            - Does not execute transitions.
            - Does not own diagnostics storage.
            - Does not prove report evidence.
    */

    namespace assembler {
namespace circulation_mechanism {


    enum class TViewVisibility : std::uint8_t
    {
        internal_only,
        approved_cross_component,
        boundary_safe,
        test_visible,
        diagnostic_visible
    };

    } // namespace circulation_mechanism
} // namespace assembler
