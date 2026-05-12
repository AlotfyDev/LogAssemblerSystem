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

namespace assembler::log_level_api::production_readiness {

enum class TLogApiProductionReadinessCriterionKind {
    Unknown = 0,
    CompileSmoke,
    ConfigurationFirst,
    ContentOnlyPublicApi,
    ParserCoverage,
    MetadataPreparedness,
    TimestampPreparedness,
    EnvelopeReadiness,
    CirculationHandoffContract,
    DiagnosticsModel,
    ComplianceSuite,
    PolicyDeferred
};

} // namespace assembler::log_level_api::production_readiness
