#pragma once

/*
    LOGAPI-W30 — Production Readiness Gate

    Responsibility:
        Define production readiness criteria, evidence references, readiness
        issues, readiness reports, readiness views, and the final production
        readiness gate for the Log Level API domain.

    Boundary:
        This wave does not implement CI, deployment, runtime monitoring, logging
        backend, telemetry export, persistence, policy assignment, circulation
        engine, bridge orchestration, or receiver behavior.

    Doctrine:
        Production readiness is a gate over evidence and compliance.
        It does not make the system production by itself; it proves that required
        evidence is present and no blocking readiness issue remains.
*/

#include "TLogApiDefaultProductionReadinessCriteria.hpp"
#include "TLogApiProductionReadinessCriterion.hpp"
#include "TLogApiProductionReadinessCriterionKind.hpp"
#include "TLogApiProductionReadinessEvidenceKind.hpp"
#include "TLogApiProductionReadinessEvidenceRef.hpp"
#include "TLogApiProductionReadinessGate.hpp"
#include "TLogApiProductionReadinessGateId.hpp"
#include "TLogApiProductionReadinessGateView.hpp"
#include "TLogApiProductionReadinessIssue.hpp"
#include "TLogApiProductionReadinessReport.hpp"
#include "TLogApiProductionReadinessSeverity.hpp"
#include "TLogApiProductionReadinessStatus.hpp"
#include "TLogApiProductionReadinessSummary.hpp"
