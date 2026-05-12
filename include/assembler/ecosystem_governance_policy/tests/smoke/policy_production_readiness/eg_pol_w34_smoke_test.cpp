#include <cassert>
#include "assembler/ecosystem_governance/policy_production_readiness/TPolicyProductionReadinessGate.hpp"
#include "assembler/ecosystem_governance/policy_production_readiness/TPolicyProductionReadinessGateView.hpp"

using namespace assembler::ecosystem_governance::policy_production_readiness;

int main()
{
    TPolicyProductionReadinessGate gate;
    gate.id = TPolicyProductionReadinessGateId{"eg-pol-production-readiness-gate"};
    gate.title = "EG-POL Production Readiness Gate";
    gate.status = TPolicyProductionReadinessGateStatus::passed;
    gate.add_criterion(TPolicyProductionReadinessCriterion{"architecture_compliance", "Architecture compliance is accepted."});
    gate.criteria.front().satisfied = true;
    gate.covered_waves.push_back("W01-W33");
    gate.report.status = TPolicyProductionReadinessGateStatus::passed;

    assert(!gate.id.empty());
    assert(gate.criterion_count() == 1U);
    assert(!gate.has_missing_required_criteria());
    assert(gate.is_ready());

    gate.report.add_issue(TPolicyProductionReadinessIssue{"BLOCKER", "Blocking issue", TPolicyProductionReadinessSeverity::blocking});
    assert(gate.report.has_blockers());
    assert(!gate.is_ready());

    TPolicyProductionReadinessGateView view{gate.id, gate.status, gate.criterion_count(), gate.report.issue_count(), gate.report.has_blockers(), gate.has_missing_required_criteria()};
    assert(view.issue_count == 1U);
    assert(view.has_blockers);
    return 0;
}
