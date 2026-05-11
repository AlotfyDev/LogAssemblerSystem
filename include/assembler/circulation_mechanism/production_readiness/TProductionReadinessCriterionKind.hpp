#pragma once
    #include <cstdint>

    /*
        TProductionReadinessCriterionKind.hpp

        Delivery:
            CME-INTEGRATION-PROD-W04 — Production Readiness Gate

        Responsibility:
            Classifies production-readiness criteria.

        Explicit non-ownership:
            - Does not execute runtime circulation.
            - Does not mutate components.
            - Does not replace tests.
            - Does not certify external bridge/receiver/addon runtime.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TProductionReadinessCriterionKind : std::uint8_t {
        compile_all_aggregates, minimal_composition_flow, end_to_end_circulation_flow, anti_collapse_compliance, gap_closure_trace, boundary_contracts, read_side_profile_readiness, no_unmapped_required_gaps, manifest_and_evidence
    };
    } // namespace circulation_mechanism
} // namespace assembler
