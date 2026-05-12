#pragma once
    #include <cstdint>

    /*
        TCirculationProductionReadinessIssueKind.hpp

        Delivery:
            CME-PROD-HARDEN-W08 — Final Production Readiness Gate

        Responsibility:
            Classifies final readiness issues.

        Explicit non-ownership:
            - Does not execute runtime.
            - Does not deploy or persist reports by itself.
    */
    namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

    enum class TCirculationProductionReadinessIssueKind : std::uint8_t {
        none, missing_gate_id, missing_evidence, criterion_failed, canonicalization_failed, injection_surface_missing, build_ci_failed, benchmark_failed, concurrency_policy_failed, versioning_failed, gap_closure_incomplete, dependency_coverage_incomplete, manifest_incomplete
    };
    } // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler
