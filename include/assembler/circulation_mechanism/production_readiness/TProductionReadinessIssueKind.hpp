#pragma once
    #include <cstdint>

    /*
        TProductionReadinessIssueKind.hpp

        Delivery:
            CME-INTEGRATION-PROD-W04 — Production Readiness Gate

        Responsibility:
            Classifies production-readiness issue kinds.

        Explicit non-ownership:
            - Does not execute runtime circulation.
            - Does not mutate components.
            - Does not replace tests.
            - Does not certify external bridge/receiver/addon runtime.
    */

    namespace assembler {
namespace circulation_mechanism {

    enum class TProductionReadinessIssueKind : std::uint8_t {
        none, missing_gate_id, missing_evidence, compile_failed, test_failed, anti_collapse_failed, gap_closure_missing, boundary_contract_failed, unmapped_required_gap, deferred_required_item
    };
    } // namespace circulation_mechanism
} // namespace assembler
