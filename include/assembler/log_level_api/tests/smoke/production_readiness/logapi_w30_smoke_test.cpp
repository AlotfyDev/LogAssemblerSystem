#include <cassert>
#include <iostream>

#include "assembler/log_level_api/production_readiness/TLogApiProductionReadinessSurface.hpp"

int main() {
    using namespace assembler::log_level_api::production_readiness;

    auto criteria = TLogApiDefaultProductionReadinessCriteria::MakeWithEvidence();
    assert(criteria.size() == 11);

    auto report = TLogApiProductionReadinessGate::Evaluate(TLogApiProductionReadinessGateId{1}, criteria);
    assert(report.IsReady());
    assert(report.status == TLogApiProductionReadinessStatus::Ready);

    auto view = TLogApiProductionReadinessGateView::From(report);
    assert(view.ready);
    assert(view.criterion_count == 11);
    assert(view.issue_count == 0);

    auto summary = TLogApiProductionReadinessSummary::From(report);
    assert(summary.mandatory_count == 10);
    assert(summary.satisfied_mandatory_count == 10);
    assert(summary.optional_count == 1);
    assert(summary.blocking_issue_count == 0);

    auto broken = criteria;
    broken[0].evidence.clear();

    auto blocked = TLogApiProductionReadinessGate::Evaluate(TLogApiProductionReadinessGateId{2}, broken);
    assert(!blocked.IsReady());
    assert(blocked.status == TLogApiProductionReadinessStatus::Blocked);
    assert(blocked.HasBlockingIssue());

    auto blocked_summary = TLogApiProductionReadinessSummary::From(blocked);
    assert(blocked_summary.blocking_issue_count == 1);

    std::cout << "LOGAPI-W30 smoke test passed\\n";
    return 0;
}
