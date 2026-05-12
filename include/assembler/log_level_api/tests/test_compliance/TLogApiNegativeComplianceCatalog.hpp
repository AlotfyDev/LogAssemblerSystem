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

#include <vector>

#include "TLogApiComplianceTestCase.hpp"

namespace assembler::log_level_api::test_compliance {

struct TLogApiNegativeComplianceCatalog final {
    std::vector<TLogApiComplianceTestCase> negative_cases{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (negative_cases.empty()) return false;
        for (const auto& test_case : negative_cases) {
            if (!test_case.IsDeclared()) return false;
            if (test_case.kind != TLogApiComplianceTestKind::Negative) return false;
        }
        return true;
    }
};

} // namespace assembler::log_level_api::test_compliance
