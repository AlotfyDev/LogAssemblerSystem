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

namespace assembler::log_level_api::production_readiness {

struct TLogApiDefaultProductionReadinessCriteria final {
    [[nodiscard]] static TLogApiProductionReadinessEvidenceRef Evidence(
        TLogApiProductionReadinessEvidenceKind kind,
        const char* label,
        const char* ref
    ) {
        return {kind, label, ref};
    }

    [[nodiscard]] static std::vector<TLogApiProductionReadinessCriterion> MakeWithEvidence() {
        return {
            {TLogApiProductionReadinessCriterionKind::CompileSmoke, TLogApiProductionReadinessSeverity::Fatal,
             "compile_smoke", "All Log API wave smoke tests must compile.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::CompileCheck, "compile_check", "LOGAPI-W01..W29")}},

            {TLogApiProductionReadinessCriterionKind::ConfigurationFirst, TLogApiProductionReadinessSeverity::Fatal,
             "configuration_first", "Configuration must be resolved before hot-path content consumption.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::ComplianceReport, "compliance_assertion", "configuration_first")}},

            {TLogApiProductionReadinessCriterionKind::ContentOnlyPublicApi, TLogApiProductionReadinessSeverity::Fatal,
             "content_only_public_api", "Public API must not accept per-call schema/metadata/validator/timestamp/policy material.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::ComplianceReport, "compliance_assertion", "content_only_public_api")}},

            {TLogApiProductionReadinessCriterionKind::ParserCoverage, TLogApiProductionReadinessSeverity::Error,
             "parser_coverage", "Default JSON, C-style struct, and MT5 parser surfaces must exist.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::WaveManifest, "parser_waves", "LOGAPI-W13..W18")}},

            {TLogApiProductionReadinessCriterionKind::MetadataPreparedness, TLogApiProductionReadinessSeverity::Error,
             "metadata_preparedness", "Metadata profile registry and default field packs must be available.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::WaveManifest, "metadata_waves", "LOGAPI-W19..W20")}},

            {TLogApiProductionReadinessCriterionKind::TimestampPreparedness, TLogApiProductionReadinessSeverity::Error,
             "timestamp_preparedness", "Timestamp stabilizer, clock calibration, and optional policy-sensitive descriptors must be available.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::WaveManifest, "timestamp_waves", "LOGAPI-W05,W21,W22")}},

            {TLogApiProductionReadinessCriterionKind::EnvelopeReadiness, TLogApiProductionReadinessSeverity::Fatal,
             "envelope_readiness", "Final envelope shape and readiness/exposure views must be available.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::WaveManifest, "envelope_waves", "LOGAPI-W23..W24")}},

            {TLogApiProductionReadinessCriterionKind::CirculationHandoffContract, TLogApiProductionReadinessSeverity::Fatal,
             "circulation_handoff_contract", "Handoff contract and smoke skeleton must be available without owning circulation internals.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::WaveManifest, "circulation_waves", "LOGAPI-W25..W26")}},

            {TLogApiProductionReadinessCriterionKind::DiagnosticsModel, TLogApiProductionReadinessSeverity::Error,
             "diagnostics_model", "Diagnostics and failure model must classify Log API-owned failures.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::DiagnosticReport, "diagnostics_wave", "LOGAPI-W28")}},

            {TLogApiProductionReadinessCriterionKind::ComplianceSuite, TLogApiProductionReadinessSeverity::Fatal,
             "compliance_suite", "Compliance suite must pass readiness gate.", true,
             {Evidence(TLogApiProductionReadinessEvidenceKind::ComplianceReport, "compliance_suite", "LOGAPI-W29")}},

            {TLogApiProductionReadinessCriterionKind::PolicyDeferred, TLogApiProductionReadinessSeverity::Info,
             "policy_deferred", "Policy assignment remains deferred until governable behavior requires it.", false,
             {Evidence(TLogApiProductionReadinessEvidenceKind::DeferredDecisionRecord, "policy_deferred", "policy_assignment deferred")}}
        };
    }
};

} // namespace assembler::log_level_api::production_readiness
