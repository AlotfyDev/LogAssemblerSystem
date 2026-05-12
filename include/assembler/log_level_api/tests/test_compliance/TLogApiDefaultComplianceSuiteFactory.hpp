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

#include "TLogApiComplianceSuiteReport.hpp"
#include "TLogApiDefaultComplianceAssertions.hpp"
#include "TLogApiNegativeComplianceCatalog.hpp"

namespace assembler::log_level_api::test_compliance {

class TLogApiDefaultComplianceSuiteFactory final {
public:
    [[nodiscard]] static TLogApiNegativeComplianceCatalog MakeNegativeCatalog() {
        const auto assertions = TLogApiDefaultComplianceAssertions::Make();

        TLogApiNegativeComplianceCatalog catalog{};
        catalog.negative_cases = {
            {TLogApiComplianceTestCaseId{101}, TLogApiComplianceTestKind::Negative, assertions[0], TLogApiComplianceOutcome::Failed,
             "reject_unresolved_configuration", "Negative case: consuming content without resolved configuration must fail."},

            {TLogApiComplianceTestCaseId{102}, TLogApiComplianceTestKind::Negative, assertions[1], TLogApiComplianceOutcome::Failed,
             "reject_per_call_configuration_material", "Negative case: per-call schema or metadata configuration must be rejected."},

            {TLogApiComplianceTestCaseId{103}, TLogApiComplianceTestKind::Negative, assertions[6], TLogApiComplianceOutcome::Failed,
             "reject_circulation_internal_leak", "Negative case: Log API must not expose circulation internals as owned structures."}
        };
        return catalog;
    }

    [[nodiscard]] static std::vector<TLogApiComplianceTestCase> MakePositiveCases() {
        const auto assertions = TLogApiDefaultComplianceAssertions::Make();

        return {
            {TLogApiComplianceTestCaseId{1}, TLogApiComplianceTestKind::Positive, assertions[0], TLogApiComplianceOutcome::Passed,
             "configuration_first_positive", "Resolved active profile exists before content call."},

            {TLogApiComplianceTestCaseId{2}, TLogApiComplianceTestKind::Positive, assertions[1], TLogApiComplianceOutcome::Passed,
             "content_only_public_api_positive", "Public call uses content-only request."},

            {TLogApiComplianceTestCaseId{3}, TLogApiComplianceTestKind::Positive, assertions[5], TLogApiComplianceOutcome::Passed,
             "final_envelope_slots_positive", "Final envelope exposes required slots."},

            {TLogApiComplianceTestCaseId{4}, TLogApiComplianceTestKind::Positive, assertions[7], TLogApiComplianceOutcome::Passed,
             "policy_assignment_deferred_positive", "Policy assignment remains deferred."}
        };
    }

    [[nodiscard]] static TLogApiComplianceSuiteReport MakePassingReport() {
        TLogApiComplianceSuiteReport report{};
        report.id = TLogApiComplianceSuiteId{1};

        for (const auto& test_case : MakePositiveCases()) {
            report.results.push_back({test_case, TLogApiComplianceOutcome::Passed, "passed"});
        }

        return report;
    }
};

} // namespace assembler::log_level_api::test_compliance
