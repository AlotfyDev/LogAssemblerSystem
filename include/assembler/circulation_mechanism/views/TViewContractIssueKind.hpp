#pragma once

    #include <cstdint>

    /*
        TViewContractIssueKind.hpp

        Delivery:
            CME-VIEWS-PROD-W01 — Production Read-Only Projection Contract

        Current responsibility:
            Classifies issues found while validating a view descriptor.

        Production capabilities:
            - Provide validation issue vocabulary.
            - Support view readiness checks without depending on Reports component.
            - Support anti-mutation compliance tests.

        Explicit non-ownership:
            - Does not expose mutable state.
            - Does not execute transitions.
            - Does not own diagnostics storage.
            - Does not prove report evidence.
    */

    namespace assembler {
namespace circulation_mechanism {


    enum class TViewContractIssueKind : std::uint8_t
    {
        none,
        invalid_id,
        scope_visibility_mismatch,
        boundary_not_safe,
        mutation_not_allowed,
        stability_mismatch,
        unknown
    };

    } // namespace circulation_mechanism
} // namespace assembler
