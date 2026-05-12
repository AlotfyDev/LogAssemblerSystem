#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyExecutionPlanStatus.hpp
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
 *   TPolicyExecutionPlanStatus names lifecycle states for a pre-execution plan: draft, planned, guard-ready, blocked, submitted-for-review, accepted-for-future-execution, cancelled, failed, or forbidden. These states never execute behavior by themselves.
 */
enum class TPolicyExecutionPlanStatus : std::uint8_t
{
    unknown = 0,
    draft = 1,
    planned = 2,
    guard_ready = 3,
    submitted_for_review = 4,
    accepted_for_future_execution = 5,
    blocked = 6,
    cancelled = 7,
    failed = 8,
    forbidden = 9
};

[[nodiscard]] constexpr bool IsPositive(TPolicyExecutionPlanStatus s) noexcept
{
    return s == TPolicyExecutionPlanStatus::planned || s == TPolicyExecutionPlanStatus::guard_ready || s == TPolicyExecutionPlanStatus::submitted_for_review || s == TPolicyExecutionPlanStatus::accepted_for_future_execution;
}

[[nodiscard]] constexpr bool IsBlocking(TPolicyExecutionPlanStatus s) noexcept
{
    return s == TPolicyExecutionPlanStatus::blocked || s == TPolicyExecutionPlanStatus::failed || s == TPolicyExecutionPlanStatus::forbidden;
}

} // namespace assembler::ecosystem_governance::policy_type_system
