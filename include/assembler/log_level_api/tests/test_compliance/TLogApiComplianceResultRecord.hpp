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

#include "TLogApiComplianceOutcome.hpp"
#include "TLogApiComplianceTestCase.hpp"

namespace assembler::log_level_api::test_compliance {

struct TLogApiComplianceResultRecord final {
    TLogApiComplianceTestCase test_case{};
    TLogApiComplianceOutcome actual_outcome{TLogApiComplianceOutcome::Unknown};
    std::string message{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return test_case.IsDeclared()
            && actual_outcome != TLogApiComplianceOutcome::Unknown;
    }

    [[nodiscard]] bool PassedExpectation() const noexcept {
        return IsPresent() && actual_outcome == test_case.expected_outcome;
    }
};

} // namespace assembler::log_level_api::test_compliance
