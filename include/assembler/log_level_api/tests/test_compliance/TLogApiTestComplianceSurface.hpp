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

#include "TLogApiComplianceAssertion.hpp"
#include "TLogApiComplianceAssertionId.hpp"
#include "TLogApiComplianceDimension.hpp"
#include "TLogApiComplianceGate.hpp"
#include "TLogApiComplianceOutcome.hpp"
#include "TLogApiComplianceResultRecord.hpp"
#include "TLogApiComplianceSeverity.hpp"
#include "TLogApiComplianceSuiteId.hpp"
#include "TLogApiComplianceSuiteReport.hpp"
#include "TLogApiComplianceSuiteView.hpp"
#include "TLogApiComplianceTestCase.hpp"
#include "TLogApiComplianceTestCaseId.hpp"
#include "TLogApiComplianceTestKind.hpp"
#include "TLogApiDefaultComplianceAssertions.hpp"
#include "TLogApiDefaultComplianceSuiteFactory.hpp"
#include "TLogApiNegativeComplianceCatalog.hpp"
