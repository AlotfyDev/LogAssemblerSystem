#pragma once

#include "assembler/ecosystem_governance/policy_audit_export/TPolicyAuditExportAdmission.hpp"
#include "assembler/ecosystem_governance/policy_audit_export/TPolicyAuditExportBoundaryDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_audit_export/TPolicyAuditExportBoundaryReport.hpp"
#include "assembler/ecosystem_governance/policy_audit_export/TPolicyAuditExportRecordRef.hpp"
#include "assembler/ecosystem_governance/policy_audit_export/TPolicyAuditExportSnapshotRef.hpp"
#include <string>
#include <utility>
#include <vector>

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
 *   Facade for audit export boundary contracts. It groups descriptor, admitted
 *   records, admitted snapshots, and report-building helpers without exporting
 *   anything and without owning any external sink.
 */
struct TPolicyAuditExportBoundary final
{
    TPolicyAuditExportBoundaryDescriptor descriptor{};
    TPolicyAuditExportAdmission last_admission{};
    std::vector<TPolicyAuditExportRecordRef> records{};
    std::vector<TPolicyAuditExportSnapshotRef> snapshots{};

    TPolicyAuditExportAdmission admit_record(const TPolicyAuditExportRecordRef& record) const
    {
        if (!descriptor.valid())
        {
            return TPolicyAuditExportAdmission::reject("invalid_audit_export_boundary_descriptor");
        }
        if (descriptor.requires_record_reference && !record.valid())
        {
            return TPolicyAuditExportAdmission::reject("missing_audit_export_record_reference");
        }
        return TPolicyAuditExportAdmission::accept("record_admitted_to_audit_export_boundary");
    }

    TPolicyAuditExportBoundaryReport describe(std::string report_id = {}) const
    {
        TPolicyAuditExportBoundaryReport report{};
        report.report_id = std::move(report_id);
        report.descriptor = descriptor;
        report.admission = last_admission;
        report.records = records;
        report.snapshots = snapshots;
        if (!descriptor.valid())
        {
            report.issues.push_back("invalid_audit_export_boundary_descriptor");
        }
        return report;
    }
};


} // namespace assembler::ecosystem_governance::policy_audit_export
