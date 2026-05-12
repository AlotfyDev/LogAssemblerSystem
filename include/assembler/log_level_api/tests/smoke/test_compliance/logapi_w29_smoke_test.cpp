#include <cassert>
#include <iostream>

#include "assembler/log_level_api/test_compliance/TLogApiTestComplianceSurface.hpp"

int main() {
    using namespace assembler::log_level_api::test_compliance;

    auto assertions = TLogApiDefaultComplianceAssertions::Make();
    assert(assertions.size() == 8);
    assert(assertions[0].IsDeclared());
    assert(assertions[0].dimension == TLogApiComplianceDimension::ConfigurationFirst);

    auto catalog = TLogApiDefaultComplianceSuiteFactory::MakeNegativeCatalog();
    assert(catalog.IsDeclared());
    assert(catalog.negative_cases.size() == 3);
    assert(catalog.negative_cases[0].expected_outcome == TLogApiComplianceOutcome::Failed);

    auto report = TLogApiDefaultComplianceSuiteFactory::MakePassingReport();
    assert(report.IsCompliant());
    assert(TLogApiComplianceGate::AllowsProductionReadiness(report));

    auto view = TLogApiComplianceSuiteView::From(report);
    assert(view.compliant);
    assert(view.result_count == 4);

    TLogApiComplianceSuiteReport failing{};
    failing.id = TLogApiComplianceSuiteId{2};
    auto positives = TLogApiDefaultComplianceSuiteFactory::MakePositiveCases();
    failing.results.push_back({positives[0], TLogApiComplianceOutcome::Failed, "failed"});
    assert(failing.HasFailure());
    assert(!TLogApiComplianceGate::AllowsProductionReadiness(failing));

    std::cout << "LOGAPI-W29 smoke test passed\\n";
    return 0;
}
