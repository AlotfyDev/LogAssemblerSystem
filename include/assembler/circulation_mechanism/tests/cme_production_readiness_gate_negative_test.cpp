#include "assembler/circulation_mechanism/circulation_mechanism_production_readiness.hpp"

#include <array>

using namespace assembler::circulation_mechanism;

int main()
{
    constexpr TProductionReadinessEvidence missing_compile{
        TProductionReadinessCriterionKind::compile_all_aggregates,
        false,
        false,
        TProductionReadinessIssueKind::missing_evidence,
        TProductionReadinessSeverity::critical
    };

    constexpr std::array<TProductionReadinessCriterion, 1> criteria{
        TProductionReadinessCriterion{TProductionReadinessCriterionKind::compile_all_aggregates, true, missing_compile}
    };

    constexpr TProductionReadinessGate<criteria.size()> gate{
        TProductionReadinessGateId::from_raw(2),
        criteria
    };

    constexpr auto report = gate.evaluate();

    static_assert(report.is_valid(), "report valid");
    static_assert(!report.passed(), "gate must fail without evidence");
    static_assert(report.issue == TProductionReadinessIssueKind::missing_evidence, "missing evidence issue expected");
    static_assert(report.severity == TProductionReadinessSeverity::critical, "critical severity expected");

    return report.passed() ? 1 : 0;
}
