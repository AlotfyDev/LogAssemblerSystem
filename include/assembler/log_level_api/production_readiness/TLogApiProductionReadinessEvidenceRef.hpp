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

#include "TLogApiProductionReadinessEvidenceKind.hpp"

namespace assembler::log_level_api::production_readiness {

struct TLogApiProductionReadinessEvidenceRef final {
    TLogApiProductionReadinessEvidenceKind kind{TLogApiProductionReadinessEvidenceKind::Unknown};
    std::string label{};
    std::string path_or_ref{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return kind != TLogApiProductionReadinessEvidenceKind::Unknown
            && !label.empty();
    }
};

} // namespace assembler::log_level_api::production_readiness
