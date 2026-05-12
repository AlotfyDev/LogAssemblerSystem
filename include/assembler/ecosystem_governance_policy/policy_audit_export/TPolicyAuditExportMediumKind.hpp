#pragma once

namespace assembler::ecosystem_governance::policy_audit_export
{

/*
 * Wave: EG-POL-W31_Policy_Audit_Export_Boundary
 * Domain: ecosystem_governance / policy_audit_export
 *
 * Architectural boundary:
 *   W31 continues Phase F — Production Hardening by introducing policy audit
 *   export boundary contracts. The wave defines how policy governance evidence,
 *   audit markers, trace references, compliance reports, realization reports,
 *   and registry/publication snapshots may be described for export to an external
 *   audit sink without implementing the export sink itself.
 *
 *   This wave is explicitly non-executing and non-exporting. It does not open
 *   files, send telemetry, write databases, serialize audit streams, mutate policy
 *   state, activate assignments, invoke targets, or run a realizer. It only
 *   defines C++17 boundary vocabulary for future audit export adapters, compliance
 *   review, and production hardening checks.
 *
 * Relationship to prior waves:
 *   - W01-W11 define the policy object, lifecycle, observation/audit carriers,
 *     assignment basics, and registry basics.
 *   - W12-W17 add family/scope, target capabilities, compatibility, assignment
 *     lifecycle, source/publication, and registry versioning views.
 *   - W18-W24 add realization contracts, readiness, runtime plans, realizer-facing
 *     interfaces, sessions, execution plans, and engine skeletons without target
 *     invocation or production execution.
 *   - W25-W29 define ecosystem integration target surfaces and system-wide skeletons.
 *   - W30 defines the persistence boundary as a description, not storage.
 *
 * Relationship to Phase A architecture:
 *   Phase A requires observation, authority, publication, registry, assignment,
 *   compatibility, realization, and runtime readiness to remain traceable and
 *   non-collapsed. W31 preserves that separation by making audit export a boundary
 *   description rather than a telemetry exporter, logging framework, database audit
 *   schema, service locator, persistence engine, or runtime authority.
 *
 * Explicit non-responsibilities:
 *   This file does not implement an audit sink, logging backend, OpenTelemetry
 *   exporter, database persistence, filesystem I/O, network transport, source
 *   parsing, runtime scheduling, target invocation, target mutation, material
 *   circulation behavior, communication binding, add-on execution, or telemetry
 *   pipeline behavior.
 *
 * Current implementation posture:
 *   The code is a conservative header-only C++17 foundation. The opening
 *   documentation describes the full intended architectural responsibility while
 *   the code remains compact value carriers and inspection helpers for compile
 *   smoke validation.
 */

/*
 * File responsibility:
 *   Describes the intended audit export medium at a semantic level. The enum is
 *   intentionally descriptive and does not perform export or bind to a backend.
 */
enum class TPolicyAuditExportMediumKind
{
    unspecified,
    in_memory_review,
    file_boundary,
    database_boundary,
    telemetry_boundary,
    diagnostic_boundary,
    foreign_runtime_boundary,
    custom_boundary
};

inline const char* to_string(TPolicyAuditExportMediumKind kind) noexcept
{
    switch (kind)
    {
    case TPolicyAuditExportMediumKind::in_memory_review: return "in_memory_review";
    case TPolicyAuditExportMediumKind::file_boundary: return "file_boundary";
    case TPolicyAuditExportMediumKind::database_boundary: return "database_boundary";
    case TPolicyAuditExportMediumKind::telemetry_boundary: return "telemetry_boundary";
    case TPolicyAuditExportMediumKind::diagnostic_boundary: return "diagnostic_boundary";
    case TPolicyAuditExportMediumKind::foreign_runtime_boundary: return "foreign_runtime_boundary";
    case TPolicyAuditExportMediumKind::custom_boundary: return "custom_boundary";
    case TPolicyAuditExportMediumKind::unspecified:
    default: return "unspecified";
    }
}


} // namespace assembler::ecosystem_governance::policy_audit_export
