#include "assembler/circulation_mechanism/circulation_mechanism_production_readiness.hpp"

#include <array>

using namespace assembler::circulation_mechanism;

constexpr TProductionReadinessEvidence pass(TProductionReadinessCriterionKind criterion)
{
    return TProductionReadinessEvidence{
        criterion,
        true,
        true,
        TProductionReadinessIssueKind::none,
        TProductionReadinessSeverity::info
    };
}

int main()
{
    constexpr std::array<TProductionReadinessCriterion, 9> criteria{
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::compile_all_aggregates, true, pass(TProductionReadinessCriterionKind::compile_all_aggregates)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::minimal_composition_flow, true, pass(TProductionReadinessCriterionKind::minimal_composition_flow)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::end_to_end_circulation_flow, true, pass(TProductionReadinessCriterionKind::end_to_end_circulation_flow)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::anti_collapse_compliance, true, pass(TProductionReadinessCriterionKind::anti_collapse_compliance)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::gap_closure_trace, true, pass(TProductionReadinessCriterionKind::gap_closure_trace)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::boundary_contracts, true, pass(TProductionReadinessCriterionKind::boundary_contracts)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::read_side_profile_readiness, true, pass(TProductionReadinessCriterionKind::read_side_profile_readiness)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::no_unmapped_required_gaps, true, pass(TProductionReadinessCriterionKind::no_unmapped_required_gaps)},
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::manifest_and_evidence, true, pass(TProductionReadinessCriterionKind::manifest_and_evidence)}
    };

    constexpr TProductionReadinessGate<criteria.size()> gate{
        TProductionReadinessGateId::from_raw(1),
        criteria
    };

    constexpr auto report = gate.evaluate();

    static_assert(report.is_valid(), "readiness report valid");
    static_assert(report.passed(), "all readiness criteria pass");
    static_assert(report.required_count == 9U, "all nine criteria required");
    static_assert(report.passed_required_count == 9U, "all nine criteria passed");

    return report.passed() ? 0 : 1;
}
