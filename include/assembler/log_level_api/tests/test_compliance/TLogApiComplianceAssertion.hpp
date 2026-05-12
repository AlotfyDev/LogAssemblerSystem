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

#include "TLogApiComplianceAssertionId.hpp"
#include "TLogApiComplianceDimension.hpp"
#include "TLogApiComplianceSeverity.hpp"

namespace assembler::log_level_api::test_compliance {

struct TLogApiComplianceAssertion final {
    TLogApiComplianceAssertionId id{};
    TLogApiComplianceDimension dimension{TLogApiComplianceDimension::Unknown};
    TLogApiComplianceSeverity severity{TLogApiComplianceSeverity::Unknown};
    std::string assertion_name{};
    std::string statement{};
    bool mandatory{true};

    [[nodiscard]] bool IsDeclared() const noexcept {
        return id.IsValid()
            && dimension != TLogApiComplianceDimension::Unknown
            && severity != TLogApiComplianceSeverity::Unknown
            && !assertion_name.empty()
            && !statement.empty();
    }
};

} // namespace assembler::log_level_api::test_compliance
