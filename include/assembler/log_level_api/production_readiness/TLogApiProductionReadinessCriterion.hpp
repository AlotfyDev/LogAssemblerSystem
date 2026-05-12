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
#include <vector>

#include "TLogApiProductionReadinessCriterionKind.hpp"
#include "TLogApiProductionReadinessEvidenceRef.hpp"
#include "TLogApiProductionReadinessSeverity.hpp"

namespace assembler::log_level_api::production_readiness {

struct TLogApiProductionReadinessCriterion final {
    TLogApiProductionReadinessCriterionKind kind{TLogApiProductionReadinessCriterionKind::Unknown};
    TLogApiProductionReadinessSeverity severity{TLogApiProductionReadinessSeverity::Unknown};
    std::string name{};
    std::string statement{};
    bool mandatory{true};
    std::vector<TLogApiProductionReadinessEvidenceRef> evidence{};

    [[nodiscard]] bool HasEvidence() const noexcept {
        for (const auto& item : evidence) {
            if (item.IsPresent()) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsDeclared() const noexcept {
        return kind != TLogApiProductionReadinessCriterionKind::Unknown
            && severity != TLogApiProductionReadinessSeverity::Unknown
            && !name.empty()
            && !statement.empty();
    }

    [[nodiscard]] bool IsSatisfied() const noexcept {
        if (!IsDeclared()) return false;
        if (!mandatory) return true;
        return HasEvidence();
    }
};

} // namespace assembler::log_level_api::production_readiness
