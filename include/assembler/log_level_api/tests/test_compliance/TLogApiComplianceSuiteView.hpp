#pragma once

/*
    LOGAPI-W29 — Test Compliance Suite

    Responsibility:
        Define Log Level API compliance assertions, test case descriptors,
        compliance dimensions/outcomes/severity, negative compliance catalog,
        compliance suite report, and production-hardening test readiness views.

    Boundary:
        This wave defines test/compliance descriptors only.
        It does not implement CI, a test runner, logging backend, telemetry,
        persistence, recovery, policy assignment, circulation engine, bridge
        orchestration, or receiver behavior.

    Doctrine:
        Compliance proves boundary discipline:
        configure first, consume content only, no per-call config, no premature
        policy assignment, no circulation internals, no bridge orchestration.
*/

#include <string>

#include "TLogApiComplianceSuiteReport.hpp"

namespace assembler::log_level_api::test_compliance {

struct TLogApiComplianceSuiteView final {
    std::string suite_id{};
    std::size_t result_count{0};
    bool compliant{false};
    bool has_failure{false};

    [[nodiscard]] static TLogApiComplianceSuiteView From(const TLogApiComplianceSuiteReport& report) {
        TLogApiComplianceSuiteView view{};
        view.suite_id = report.id.ToString();
        view.result_count = report.Count();
        view.compliant = report.IsCompliant();
        view.has_failure = report.HasFailure();
        return view;
    }
};

} // namespace assembler::log_level_api::test_compliance
