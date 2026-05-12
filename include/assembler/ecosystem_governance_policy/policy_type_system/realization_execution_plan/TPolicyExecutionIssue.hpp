#pragma once

#include <cstdint>
#include <string>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyExecutionIssue.hpp
 * Wave: EG-POL-W23_PolicyRealizationExecutionPlan
 * Domain: ecosystem_governance / policy_type_system / realization_execution_plan
 *
 * Architectural boundary:
 *   W23 introduces the Policy Realization Execution Plan model after W22
 *   introduced PolicyRealizationSession. The execution plan is still a
 *   governed pre-execution artifact: it may decompose a realization session,
 *   runtime plan, readiness evidence, and realizer identity into guarded
 *   execution-intent steps for later inspection by a future executor/engine.
 *   It is not the executor, not target invocation, not target mutation, not a
 *   scheduler, not material circulation behavior, not communication binding,
 *   and not add-on execution.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and result vocabulary.
 *   - W06 supplies descriptor-only realization binding and target-kind language.
 *   - W09 supplies TPolicy as semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12/W13 supply family/scope and target capability foundations.
 *   - W14 supplies family-target compatibility reports.
 *   - W15 supplies assignment lifecycle and conflict vocabulary.
 *   - W16/W17 supply source/publication and registry-versioning views.
 *   - W18 supplies realization contract/context/request/failure/trace carriers.
 *   - W19 supplies runtime readiness gates and reports.
 *   - W20 supplies non-executing runtime plans.
 *   - W21 supplies the TPolicyRealizer interface and result vocabulary.
 *   - W22 supplies realization session lifecycle scope.
 *
 * Relationship to Phase A architecture:
 *   Phase A states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W23 adds one more pre-execution planning layer. An execution plan may be
 *   complete and guard-satisfied, but that means only that a future executor
 *   may inspect it. It must not claim execution, target mutation, downstream
 *   success, or external side effects.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyExecutor, a runtime execution engine,
 *   direct target invocation, target mutation, material circulation behavior,
 *   communication binding, add-on execution, source parsing, persistent
 *   registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete architectural responsibility while the
 *   implementation remains a compact foundation block for compile-smoke use.
 *
 * File responsibility:
 *   TPolicyExecutionIssue captures problems in constructing or reviewing a realization execution plan, such as missing session, missing runtime plan, guard failure, missing trace, missing authority, or forbidden execution attempt. It reports issues only; it never repairs or executes anything.
 */
enum class TPolicyExecutionIssueKind : std::uint8_t
{
    unknown = 0,
    missing_plan_id = 1,
    missing_session = 2,
    missing_runtime_plan = 3,
    missing_realizer = 4,
    missing_trace = 5,
    missing_authority = 6,
    guard_failed = 7,
    readiness_not_positive = 8,
    forbidden_target_invocation = 9
};

enum class TPolicyExecutionIssueSeverity : std::uint8_t
{
    info = 0,
    warning = 1,
    blocking = 2,
    critical = 3,
    forbidden = 4
};

struct TPolicyExecutionIssue final
{
    TPolicyExecutionIssueKind kind{TPolicyExecutionIssueKind::unknown};
    TPolicyExecutionIssueSeverity severity{TPolicyExecutionIssueSeverity::info};
    std::string message{};

    [[nodiscard]] bool IsBlocking() const noexcept { return severity == TPolicyExecutionIssueSeverity::blocking || severity == TPolicyExecutionIssueSeverity::critical || severity == TPolicyExecutionIssueSeverity::forbidden; }

    [[nodiscard]] static TPolicyExecutionIssue Blocking(TPolicyExecutionIssueKind k, std::string msg)
    {
        return TPolicyExecutionIssue{k, TPolicyExecutionIssueSeverity::blocking, std::move(msg)};
    }

    [[nodiscard]] static TPolicyExecutionIssue Forbidden(TPolicyExecutionIssueKind k, std::string msg)
    {
        return TPolicyExecutionIssue{k, TPolicyExecutionIssueSeverity::forbidden, std::move(msg)};
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
