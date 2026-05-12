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

#include "TLogApiComplianceAssertion.hpp"
#include "TLogApiComplianceOutcome.hpp"
#include "TLogApiComplianceTestCaseId.hpp"
#include "TLogApiComplianceTestKind.hpp"

namespace assembler::log_level_api::test_compliance {

struct TLogApiComplianceTestCase final {
    TLogApiComplianceTestCaseId id{};
    TLogApiComplianceTestKind kind{TLogApiComplianceTestKind::Unknown};
    TLogApiComplianceAssertion assertion{};
    TLogApiComplianceOutcome expected_outcome{TLogApiComplianceOutcome::Unknown};
    std::string test_name{};
    std::string note{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return id.IsValid()
            && kind != TLogApiComplianceTestKind::Unknown
            && assertion.IsDeclared()
            && expected_outcome != TLogApiComplianceOutcome::Unknown
            && !test_name.empty();
    }
};

} // namespace assembler::log_level_api::test_compliance
