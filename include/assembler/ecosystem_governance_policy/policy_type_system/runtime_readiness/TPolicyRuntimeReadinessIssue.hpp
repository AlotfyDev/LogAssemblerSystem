#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimeReadinessIssue.hpp

 * Wave: EG-POL-W19_Runtime_Readiness_Model
 * Domain: ecosystem_governance / policy_type_system / runtime_readiness
 *
 * Architectural boundary:
 *   W19 implements the Runtime Readiness Model that follows W18 Realization
 *   Contract Foundation. It is derived from EG-POL-ARCH-007_Realization_Contracts_And_Runtime_Readiness
 *   and guarded by EG-POL-ARCH-008_Compliance_And_Validation_Matrix. Runtime
 *   readiness is a pre-execution gate: it determines whether a policy assignment
 *   and target context are sufficiently prepared for later realization planning
 *   or controlled realizer invocation. It is not runtime execution, not target
 *   invocation, not target mutation, not material circulation, not communication
 *   binding, and not add-on execution.
 *
 * Relationship to prior waves:
 *   - W01 supplies policy identity, family, version, scope, source, issue, and result vocabulary.
 *   - W06 supplies target-kind and realization-binding descriptors while preserving descriptor-only semantics.
 *   - W09 supplies TPolicy as semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12 supplies policy-family and scope foundations.
 *   - W13 supplies target-capability contracts.
 *   - W14 supplies family-target compatibility reports.
 *   - W15 supplies assignment lifecycle and conflict states.
 *   - W16 and W17 supply policy source/publication and registry-versioning views.
 *   - W18 supplies realization contracts, realization contexts, requests, preconditions, failures, and traces.
 *
 * Relationship to Phase A architecture:
 *   The architecture states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W19 implements the runtime-ready portion of that chain. A positive readiness
 *   report allows later realization planning to be considered; it does not perform
 *   realization. A readiness evaluator consumes descriptive artifacts and reports
 *   readiness status without invoking targets or changing runtime state.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyRealizer, TPolicyExecutor, runtime
 *   execution engine, target invocation, target mutation, material circulation
 *   behavior, communication binding, add-on execution, source parsing,
 *   persistent registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation describes the complete architectural responsibility, while
 *   the implementation intentionally remains a compact set of value carriers
 *   and structural helpers.
 * File responsibility:
 *   TPolicyRuntimeReadinessIssue classifies readiness problems detected during
 *   pre-execution evaluation: missing policy validity, inactive assignment,
 *   failed compatibility, missing capabilities, missing authority, conflict,
 *   unsafe replacement, invalid publication, contract mismatch, quarantine, or
 *   forbidden target invocation. It reports issue severity without repairing or
 *   executing anything.
 */

enum class TPolicyRuntimeReadinessIssueKind : std::uint8_t
{
    unknown = 0,
    policy_invalid = 1,
    policy_lifecycle_invalid = 2,
    publication_invalid = 3,
    assignment_not_eligible = 4,
    compatibility_not_positive = 5,
    target_kind_unknown = 6,
    missing_required_capability = 7,
    authority_missing = 8,
    conflict_blocking = 9,
    replacement_unsafe = 10,
    observation_missing = 11,
    trace_missing = 12,
    runtime_environment_not_ready = 13,
    quarantined = 14,
    contract_missing = 15,
    contract_mismatch = 16,
    forbidden_realization = 17,
    target_invocation_forbidden = 18,
    custom = 255
};

enum class TPolicyRuntimeReadinessIssueSeverity : std::uint8_t
{
    unknown = 0,
    info = 1,
    notice = 2,
    warning = 3,
    blocking = 4,
    critical = 5,
    forbidden = 6
};

struct TPolicyRuntimeReadinessIssue final
{
    TPolicyRuntimeReadinessIssueKind kind{TPolicyRuntimeReadinessIssueKind::unknown};
    TPolicyRuntimeReadinessIssueSeverity severity{TPolicyRuntimeReadinessIssueSeverity::unknown};
    std::string message{};

    [[nodiscard]] bool IsKnown() const noexcept { return kind != TPolicyRuntimeReadinessIssueKind::unknown; }
    [[nodiscard]] bool IsBlocking() const noexcept
    {
        return severity == TPolicyRuntimeReadinessIssueSeverity::blocking ||
               severity == TPolicyRuntimeReadinessIssueSeverity::critical ||
               severity == TPolicyRuntimeReadinessIssueSeverity::forbidden;
    }
    [[nodiscard]] bool IsForbidden() const noexcept { return severity == TPolicyRuntimeReadinessIssueSeverity::forbidden; }

    [[nodiscard]] static TPolicyRuntimeReadinessIssue Blocking(TPolicyRuntimeReadinessIssueKind kind, std::string message)
    {
        return TPolicyRuntimeReadinessIssue{kind, TPolicyRuntimeReadinessIssueSeverity::blocking, std::move(message)};
    }

    [[nodiscard]] static TPolicyRuntimeReadinessIssue Warning(TPolicyRuntimeReadinessIssueKind kind, std::string message)
    {
        return TPolicyRuntimeReadinessIssue{kind, TPolicyRuntimeReadinessIssueSeverity::warning, std::move(message)};
    }
};

struct TPolicyRuntimeReadinessIssueSet final
{
    std::vector<TPolicyRuntimeReadinessIssue> issues{};

    void Add(TPolicyRuntimeReadinessIssue issue) { if (issue.IsKnown()) issues.push_back(std::move(issue)); }
    [[nodiscard]] bool Empty() const noexcept { return issues.empty(); }
    [[nodiscard]] std::size_t Count() const noexcept { return issues.size(); }
    [[nodiscard]] bool HasBlockingIssue() const noexcept
    {
        for (const auto& issue : issues) { if (issue.IsBlocking()) return true; }
        return false;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system
