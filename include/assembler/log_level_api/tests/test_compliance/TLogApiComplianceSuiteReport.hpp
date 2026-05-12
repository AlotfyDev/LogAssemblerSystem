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

#include "TLogApiComplianceResultRecord.hpp"
#include "TLogApiComplianceSuiteId.hpp"

namespace assembler::log_level_api::test_compliance {

struct TLogApiComplianceSuiteReport final {
    TLogApiComplianceSuiteId id{};
    std::vector<TLogApiComplianceResultRecord> results{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return id.IsValid();
    }

    [[nodiscard]] std::size_t Count() const noexcept {
        return results.size();
    }

    [[nodiscard]] bool HasFailure() const noexcept {
        for (const auto& result : results) {
            if (!result.PassedExpectation()) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsCompliant() const noexcept {
        return IsPresent() && !results.empty() && !HasFailure();
    }
};

} // namespace assembler::log_level_api::test_compliance
