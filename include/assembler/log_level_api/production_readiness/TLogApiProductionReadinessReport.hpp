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

#include <vector>

#include "TLogApiProductionReadinessCriterion.hpp"
#include "TLogApiProductionReadinessGateId.hpp"
#include "TLogApiProductionReadinessIssue.hpp"
#include "TLogApiProductionReadinessStatus.hpp"

namespace assembler::log_level_api::production_readiness {

struct TLogApiProductionReadinessReport final {
    TLogApiProductionReadinessGateId id{};
    TLogApiProductionReadinessStatus status{TLogApiProductionReadinessStatus::Unknown};
    std::vector<TLogApiProductionReadinessCriterion> criteria{};
    std::vector<TLogApiProductionReadinessIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool AllMandatoryCriteriaSatisfied() const noexcept {
        for (const auto& criterion : criteria) {
            if (criterion.mandatory && !criterion.IsSatisfied()) return false;
        }
        return !criteria.empty();
    }

    [[nodiscard]] bool IsReady() const noexcept {
        return id.IsValid()
            && status == TLogApiProductionReadinessStatus::Ready
            && AllMandatoryCriteriaSatisfied()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::production_readiness
