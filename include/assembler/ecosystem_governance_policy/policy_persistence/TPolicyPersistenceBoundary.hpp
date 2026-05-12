#pragma once

#include "assembler/ecosystem_governance/policy_persistence/TPolicyPersistenceBoundaryDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_persistence/TPolicyPersistenceBoundaryReport.hpp"
#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_persistence
{

/*
 * Wave: EG-POL-W30_Policy_Persistence_Boundary
 * Domain: ecosystem_governance / policy_persistence
 *
 * Architectural boundary:
 *   W30 opens Phase F — Production Hardening by introducing policy persistence
 *   boundary contracts. The wave defines how policy governance artifacts may be
 *   described for persistence, snapshotting, record reference, admission, and
 *   audit-facing retention without turning the policy registry into a database,
 *   without implementing storage engines, and without converting persistence
 *   into runtime execution.
 *
 *   This wave is explicitly non-executing and non-storage-implementing. It does
 *   not write files, open databases, serialize policy DSLs, mutate assignments,
 *   invoke target components, run a realizer, or persist telemetry. It only
 *   defines C++17 boundary vocabulary for future persistence adapters and
 *   compliance checks.
 *
 * Relationship to prior waves:
 *   - W01-W11 define the policy type system, aggregate, assignment, and registry basics.
 *   - W12-W17 add family/scope, target capabilities, compatibility, assignment lifecycle,
 *     source/publication, and registry versioning views.
 *   - W18-W24 add realization contract, readiness, plan, session, realizer interface,
 *     execution plan, and engine skeleton without production execution.
 *   - W25-W29 add ecosystem integration target surfaces and system-wide skeletons.
 *
 * Relationship to Phase A architecture:
 *   Phase A explicitly separated source, publication, registry visibility, assignment,
 *   realization, and execution. W30 preserves that separation by making persistence a
 *   boundary description rather than an authority, registry, realizer, service locator,
 *   or storage engine.
 *
 * Explicit non-responsibilities:
 *   This file does not implement persistent storage, database access, filesystem I/O,
 *   source parsing, serialization format, runtime scheduling, target invocation, target
 *   mutation, material circulation behavior, communication binding, add-on execution,
 *   telemetry export, or logging framework behavior.
 *
 * Current implementation posture:
 *   The code is a conservative header-only C++17 foundation. The opening documentation
 *   describes the full intended architectural responsibility while the code remains
 *   compact value carriers and inspection helpers for compile smoke validation.
 */

/*
 * File responsibility:
 *   The W30 facade for policy persistence boundary contracts. It groups a
 *   descriptor, last admission, snapshot reference, and report-building helper
 *   without owning storage and without performing any persistence operation.
 */
struct TPolicyPersistenceBoundary final
{
    TPolicyPersistenceBoundaryDescriptor descriptor{};
    TPolicyPersistenceAdmission last_admission{};
    TPolicyPersistenceSnapshotRef latest_snapshot{};

    TPolicyPersistenceBoundaryReport describe(std::string report_id = {}) const
    {
        TPolicyPersistenceBoundaryReport report{};
        report.report_id = std::move(report_id);
        report.descriptor = descriptor;
        report.admission = last_admission;
        report.snapshot = latest_snapshot;
        if (!descriptor.valid())
        {
            report.issues.push_back("invalid_persistence_boundary_descriptor");
        }
        return report;
    }
};

} // namespace assembler::ecosystem_governance::policy_persistence
