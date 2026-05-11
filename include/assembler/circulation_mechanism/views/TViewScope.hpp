#pragma once

    #include <cstdint>

    /*
        TViewScope.hpp

        Delivery:
            CME-VIEWS-PROD-W01 — Production Read-Only Projection Contract

        Current responsibility:
            Classifies the architectural scope where a view may be observed.

        Production capabilities:
            - Distinguish local, cross-component, boundary-facing, diagnostic, and test-only views.
            - Support validation rules for safe external/boundary exposure.
            - Prevent accidental exposure of local internals.

        Explicit non-ownership:
            - Does not expose mutable state.
            - Does not execute transitions.
            - Does not own diagnostics storage.
            - Does not prove report evidence.
    */

    namespace assembler {
namespace circulation_mechanism {


    enum class TViewScope : std::uint8_t
    {
        local_component,
        component_family,
        cross_component,
        boundary_facing,
        diagnostic_only,
        test_only
    };

    } // namespace circulation_mechanism
} // namespace assembler
