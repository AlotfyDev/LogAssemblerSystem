#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimePlanIssue.hpp

 * Wave: EG-POL-W20_Policy_Runtime_Plan
 * Domain: ecosystem_governance / policy_type_system / runtime_plan
 *
 * Architectural boundary:
 *   W20 implements the Policy Runtime Plan model that follows W18 Realization
 *   Contract Foundation and W19 Runtime Readiness Model. It is derived from
 *   EG-POL-ARCH-007_Realization_Contracts_And_Runtime_Readiness and guarded by
 *   EG-POL-ARCH-008_Compliance_And_Validation_Matrix. A runtime plan is a
 *   pre-execution, non-mutating plan artifact: it may describe ordered steps
 *   a future realizer could consume, but it is not TPolicyRealizer, not
 *   TPolicyExecutor, not target invocation, not runtime mutation, not scheduler
 *   behavior, not material circulation, not communication binding, and not
 *   add-on execution.
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
 *   - W19 supplies runtime admission, readiness gates, readiness issues, readiness reports, and readiness evaluators.
 *
 * Relationship to Phase A architecture:
 *   The architecture states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W20 sits after runtime-ready and before any realizer interface. It can
 *   express a plan for later realization consideration, but that plan remains
 *   descriptive. Passing readiness and creating a plan does not execute policy
 *   behavior and does not prove target mutation, downstream success, or external
 *   side effects.
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
 *   TPolicyRuntimePlanIssue records warnings or blockers discovered while
 *   building a runtime plan. Issues explain why a plan is clean, conditional,
 *   blocked, or forbidden. They are evidence carriers only and must not repair,
 *   roll back, execute, or mutate runtime behavior.
 */

enum class TPolicyRuntimePlanIssueKind : std::uint8_t
{
    unknown = 0,
    missing_readiness = 1,
    readiness_not_positive = 2,
    contract_missing = 3,
    request_missing = 4,
    trace_missing = 5,
    forbidden_realization_mode = 6,
    target_invocation_attempt = 7,
    direct_execution_attempt = 8,
    custom = 255
};

enum class TPolicyRuntimePlanIssueSeverity : std::uint8_t
{
    info = 0,
    warning = 1,
    blocking = 2,
    critical = 3,
    forbidden = 4
};

struct TPolicyRuntimePlanIssue final
{
    TPolicyRuntimePlanIssueKind kind{TPolicyRuntimePlanIssueKind::unknown};
    TPolicyRuntimePlanIssueSeverity severity{TPolicyRuntimePlanIssueSeverity::info};
    std::string message{};

    [[nodiscard]] bool IsBlocking() const noexcept
    {
        return severity == TPolicyRuntimePlanIssueSeverity::blocking ||
               severity == TPolicyRuntimePlanIssueSeverity::critical ||
               severity == TPolicyRuntimePlanIssueSeverity::forbidden;
    }

    [[nodiscard]] bool IsForbidden() const noexcept
    {
        return severity == TPolicyRuntimePlanIssueSeverity::forbidden ||
               kind == TPolicyRuntimePlanIssueKind::target_invocation_attempt ||
               kind == TPolicyRuntimePlanIssueKind::direct_execution_attempt;
    }

    [[nodiscard]] static TPolicyRuntimePlanIssue Warning(TPolicyRuntimePlanIssueKind kind, std::string message)
    {
        return TPolicyRuntimePlanIssue{kind, TPolicyRuntimePlanIssueSeverity::warning, std::move(message)};
    }

    [[nodiscard]] static TPolicyRuntimePlanIssue Blocking(TPolicyRuntimePlanIssueKind kind, std::string message)
    {
        return TPolicyRuntimePlanIssue{kind, TPolicyRuntimePlanIssueSeverity::blocking, std::move(message)};
    }

    [[nodiscard]] static TPolicyRuntimePlanIssue Forbidden(TPolicyRuntimePlanIssueKind kind, std::string message)
    {
        return TPolicyRuntimePlanIssue{kind, TPolicyRuntimePlanIssueSeverity::forbidden, std::move(message)};
    }
};

struct TPolicyRuntimePlanIssueSet final
{
    std::vector<TPolicyRuntimePlanIssue> issues{};

    void Add(TPolicyRuntimePlanIssue issue) { issues.push_back(std::move(issue)); }
    [[nodiscard]] bool Empty() const noexcept { return issues.empty(); }
    [[nodiscard]] std::size_t Count() const noexcept { return issues.size(); }
    [[nodiscard]] bool HasBlockingIssue() const noexcept
    {
        for (const auto& issue : issues) if (issue.IsBlocking()) return true;
        return false;
    }
    [[nodiscard]] bool HasForbiddenIssue() const noexcept
    {
        for (const auto& issue : issues) if (issue.IsForbidden()) return true;
        return false;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
