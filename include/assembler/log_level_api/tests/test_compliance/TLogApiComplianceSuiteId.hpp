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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::test_compliance {

struct TLogApiComplianceSuiteId final {
    std::uint64_t value{0};

    constexpr TLogApiComplianceSuiteId() = default;
    constexpr explicit TLogApiComplianceSuiteId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-compliance-suite-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::test_compliance
