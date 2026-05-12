#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionGuard.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyExecutionStep.hpp
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
 *   TPolicyExecutionStep describes one ordered, guarded step in a future realization execution plan. It is an execution-intent descriptor only: it may say inspect, prepare, bind-context, dry-run, submit-to-realizer, or report, but it must not perform target invocation or mutation.
 */
enum class TPolicyExecutionStepKind : std::uint8_t
{
    unknown = 0,
    inspect_session = 1,
    verify_contract = 2,
    verify_readiness = 3,
    verify_authority = 4,
    verify_runtime_plan = 5,
    prepare_realizer_submission = 6,
    dry_run_only = 7,
    produce_report = 8,
    forbidden_target_invocation = 9
};

struct TPolicyExecutionStep final
{
    std::uint64_t step_id{0};
    std::uint32_t order{0};
    TPolicyExecutionStepKind kind{TPolicyExecutionStepKind::unknown};
    bool required{true};
    TPolicyExecutionGuardSet guard_set{};
    std::string description{};

    [[nodiscard]] bool IsValid() const noexcept { return step_id != 0 && kind != TPolicyExecutionStepKind::unknown; }
    [[nodiscard]] bool IsForbidden() const noexcept { return kind == TPolicyExecutionStepKind::forbidden_target_invocation; }
    [[nodiscard]] bool GuardsSatisfied() const noexcept { return guard_set.AllRequiredSatisfied(); }
};

struct TPolicyExecutionStepSet final
{
    std::vector<TPolicyExecutionStep> steps{};

    void Add(TPolicyExecutionStep step) { steps.push_back(std::move(step)); }
    [[nodiscard]] bool Empty() const noexcept { return steps.empty(); }
    [[nodiscard]] bool AllRequiredSatisfied() const noexcept
    {
        return std::all_of(steps.begin(), steps.end(), [](const TPolicyExecutionStep& step) { return !step.required || (step.IsValid() && step.GuardsSatisfied() && !step.IsForbidden()); });
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
