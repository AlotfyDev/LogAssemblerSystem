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

#include "TLogApiProductionReadinessReport.hpp"

namespace assembler::log_level_api::production_readiness {

class TLogApiProductionReadinessGate final {
public:
    [[nodiscard]] static TLogApiProductionReadinessReport Evaluate(
        TLogApiProductionReadinessGateId id,
        const std::vector<TLogApiProductionReadinessCriterion>& criteria
    ) {
        TLogApiProductionReadinessReport report{};
        report.id = id;
        report.criteria = criteria;
        report.status = TLogApiProductionReadinessStatus::Evaluating;

        for (const auto& criterion : report.criteria) {
            if (!criterion.IsDeclared()) {
                report.issues.push_back({
                    "LOGAPI_PROD_CRITERION_NOT_DECLARED",
                    "A production readiness criterion is not declared.",
                    TLogApiProductionReadinessSeverity::Fatal,
                    true
                });
                continue;
            }

            if (criterion.mandatory && !criterion.IsSatisfied()) {
                report.issues.push_back({
                    "LOGAPI_PROD_CRITERION_MISSING_EVIDENCE",
                    "A mandatory production readiness criterion is missing evidence.",
                    criterion.severity,
                    true
                });
            }
        }

        report.status = report.HasBlockingIssue()
            ? TLogApiProductionReadinessStatus::Blocked
            : TLogApiProductionReadinessStatus::Ready;

        return report;
    }
};

} // namespace assembler::log_level_api::production_readiness
