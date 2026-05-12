#include "assembler/circulation_mechanism/circulation_mechanism_final_readiness.hpp"

#include <array>

using namespace assembler::circulation_mechanism::final_readiness;

constexpr TCirculationProductionReadinessEvidenceRef pass(TCirculationProductionReadinessCriterionKind kind)
{
    return TCirculationProductionReadinessEvidenceRef{
        kind,
        true,
        true,
        TCirculationProductionReadinessIssueKind::none,
        TCirculationProductionReadinessSeverity::info
    };
}

int main()
{
    constexpr std::array<TCirculationProductionReadinessCriterion, 12> criteria{
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::canonical_domain_consolidation, true, pass(TCirculationProductionReadinessCriterionKind::canonical_domain_consolidation)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::prebridge_injection_ready, true, pass(TCirculationProductionReadinessCriterionKind::prebridge_injection_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::readside_injection_ready, true, pass(TCirculationProductionReadinessCriterionKind::readside_injection_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::build_ci_ready, true, pass(TCirculationProductionReadinessCriterionKind::build_ci_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::diagnostics_export_ready, true, pass(TCirculationProductionReadinessCriterionKind::diagnostics_export_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::performance_stress_baseline_ready, true, pass(TCirculationProductionReadinessCriterionKind::performance_stress_baseline_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::concurrency_policy_ready, true, pass(TCirculationProductionReadinessCriterionKind::concurrency_policy_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::versioning_compatibility_ready, true, pass(TCirculationProductionReadinessCriterionKind::versioning_compatibility_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::gap_closure_complete, true, pass(TCirculationProductionReadinessCriterionKind::gap_closure_complete)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::dependency_coverage_complete, true, pass(TCirculationProductionReadinessCriterionKind::dependency_coverage_complete)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::examples_ready, true, pass(TCirculationProductionReadinessCriterionKind::examples_ready)},
        TCirculationProductionReadinessCriterion{TCirculationProductionReadinessCriterionKind::manifest_evidence_complete, true, pass(TCirculationProductionReadinessCriterionKind::manifest_evidence_complete)}
    };

    constexpr TCirculationProductionReadinessGate<criteria.size()> gate{
        TCirculationProductionReadinessGateId::from_raw(1),
        TCirculationProductionReadinessReportId::from_raw(2),
        criteria
    };

    constexpr auto report = gate.evaluate();

    static_assert(report.is_valid(), "report valid");
    static_assert(report.passed(), "all required criteria pass");
    static_assert(report.required_count == 12U, "all criteria required");
    static_assert(report.passed_required_count == 12U, "all criteria passed");

    constexpr TCirculationProductionReadinessGateView view{report};
    static_assert(view.ready(), "gate view ready");

    return 0;
}
