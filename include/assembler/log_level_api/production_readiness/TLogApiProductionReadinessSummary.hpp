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

#include <cstddef>

#include "TLogApiProductionReadinessReport.hpp"

namespace assembler::log_level_api::production_readiness {

struct TLogApiProductionReadinessSummary final {
    std::size_t mandatory_count{0};
    std::size_t satisfied_mandatory_count{0};
    std::size_t optional_count{0};
    std::size_t blocking_issue_count{0};

    [[nodiscard]] static TLogApiProductionReadinessSummary From(const TLogApiProductionReadinessReport& report) noexcept {
        TLogApiProductionReadinessSummary summary{};

        for (const auto& criterion : report.criteria) {
            if (criterion.mandatory) {
                ++summary.mandatory_count;
                if (criterion.IsSatisfied()) ++summary.satisfied_mandatory_count;
            } else {
                ++summary.optional_count;
            }
        }

        for (const auto& issue : report.issues) {
            if (issue.blocking) ++summary.blocking_issue_count;
        }

        return summary;
    }
};

} // namespace assembler::log_level_api::production_readiness
