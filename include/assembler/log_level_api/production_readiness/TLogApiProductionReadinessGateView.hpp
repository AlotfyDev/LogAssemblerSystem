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

#include <string>

#include "TLogApiProductionReadinessReport.hpp"

namespace assembler::log_level_api::production_readiness {

struct TLogApiProductionReadinessGateView final {
    std::string gate_id{};
    std::size_t criterion_count{0};
    std::size_t issue_count{0};
    bool ready{false};
    bool has_blocking_issue{false};

    [[nodiscard]] static TLogApiProductionReadinessGateView From(const TLogApiProductionReadinessReport& report) {
        TLogApiProductionReadinessGateView view{};
        view.gate_id = report.id.ToString();
        view.criterion_count = report.criteria.size();
        view.issue_count = report.issues.size();
        view.ready = report.IsReady();
        view.has_blocking_issue = report.HasBlockingIssue();
        return view;
    }
};

} // namespace assembler::log_level_api::production_readiness
