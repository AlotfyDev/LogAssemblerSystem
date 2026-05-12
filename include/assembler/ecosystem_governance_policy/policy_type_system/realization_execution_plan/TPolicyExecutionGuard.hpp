#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyExecutionGuard.hpp
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
 *   TPolicyExecutionGuard represents a pre-execution guard attached to a step or plan. Guards can describe authority, readiness, trace, contract, session, compatibility, or target-capability requirements. They are descriptive checks and never call target methods.
 */
enum class TPolicyExecutionGuardKind : std::uint8_t
{
    unknown = 0,
    contract_guard = 1,
    session_guard = 2,
    runtime_plan_guard = 3,
    readiness_guard = 4,
    authority_guard = 5,
    trace_guard = 6,
    realizer_guard = 7,
    capability_guard = 8,
    no_direct_target_invocation_guard = 9
};

struct TPolicyExecutionGuard final
{
    TPolicyExecutionGuardKind kind{TPolicyExecutionGuardKind::unknown};
    bool required{true};
    bool satisfied{false};
    std::string note{};

    [[nodiscard]] bool IsSatisfied() const noexcept { return !required || satisfied; }
};

struct TPolicyExecutionGuardSet final
{
    std::vector<TPolicyExecutionGuard> guards{};

    void Add(TPolicyExecutionGuard guard) { guards.push_back(std::move(guard)); }
    [[nodiscard]] bool AllRequiredSatisfied() const noexcept
    {
        return std::all_of(guards.begin(), guards.end(), [](const TPolicyExecutionGuard& g) { return g.IsSatisfied(); });
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
