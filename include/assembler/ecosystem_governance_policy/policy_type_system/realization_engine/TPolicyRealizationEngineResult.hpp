#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationTrace.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionPlanId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationEngineResult.hpp
 * Wave: EG-POL-W24_PolicyRealizationEngine_Skeleton
 * Domain: ecosystem_governance / policy_type_system / realization_engine
 *
 * Architectural boundary:
 *   W24 introduces the Policy Realization Engine Skeleton after W23 introduced
 *   the guarded Policy Realization Execution Plan. This wave is deliberately
 *   named "engine skeleton" rather than "executor": it may coordinate, inspect,
 *   gate, and report on pre-execution realization artifacts, but it must not
 *   execute policies, invoke targets, mutate target state, schedule runtime
 *   work, perform material circulation, bind communication endpoints, run add-ons,
 *   parse sources, persist registry data, or emit telemetry/logging output.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and result vocabulary.
 *   - W06 supplies descriptor-only realization binding and target-kind language.
 *   - W09 supplies TPolicy as semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12/W13 supply family/scope and target-capability foundations.
 *   - W14 supplies family-target compatibility reports.
 *   - W15 supplies assignment lifecycle and conflict vocabulary.
 *   - W16/W17 supply publication and registry-versioning views.
 *   - W18 supplies realization contracts, contexts, requests, failures, and traces.
 *   - W19 supplies runtime readiness gates and reports.
 *   - W20 supplies non-executing runtime plans.
 *   - W21 supplies the TPolicyRealizer interface and result vocabulary.
 *   - W22 supplies realization session lifecycle scope.
 *   - W23 supplies guarded realization execution-plan artifacts.
 *
 * Relationship to Phase A architecture:
 *   Phase A states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W24 can inspect a complete execution plan and can produce an engine result,
 *   but that result is only governance evidence for a later executor/engine wave.
 *   It must not claim target mutation, downstream success, external side effects,
 *   persistence, telemetry, or actual execution.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyExecutor, a production runtime execution
 *   engine, direct target invocation, target mutation, material circulation
 *   behavior, communication binding, add-on execution, source parsing, persistent
 *   registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete architectural responsibility while the
 *   implementation remains a compact foundation block for compile-smoke use.
 *
 * File responsibility:
 *   TPolicyRealizationEngineResult records the output of engine-skeleton plan inspection. It can say a plan was accepted for future execution review, rejected, deferred, blocked, or forbidden. It never claims policy execution, target mutation, downstream success, or external side effects.
 */
enum class TPolicyRealizationEngineResultKind : std::uint8_t
{
    unknown = 0,
    accepted_for_engine_review = 1,
    rejected = 2,
    deferred = 3,
    blocked = 4,
    forbidden = 5,
    failed = 6
};

[[nodiscard]] constexpr bool IsPositive(TPolicyRealizationEngineResultKind k) noexcept
{
    return k == TPolicyRealizationEngineResultKind::accepted_for_engine_review;
}

[[nodiscard]] constexpr bool IsBlocking(TPolicyRealizationEngineResultKind k) noexcept
{
    return k == TPolicyRealizationEngineResultKind::rejected ||
           k == TPolicyRealizationEngineResultKind::blocked ||
           k == TPolicyRealizationEngineResultKind::forbidden ||
           k == TPolicyRealizationEngineResultKind::failed;
}

struct TPolicyRealizationEngineResult final
{
    TPolicyRealizationEngineResultKind kind{TPolicyRealizationEngineResultKind::unknown};
    TPolicyExecutionPlanId plan_id{};
    TPolicyRealizationEngineStatus engine_status{TPolicyRealizationEngineStatus::unknown};
    TPolicyRealizationTrace trace{};
    std::vector<TPolicyRealizationEngineIssue> issues{};
    std::string recommendation{};

    [[nodiscard]] bool IsPositive() const noexcept { return policy_type_system::IsPositive(kind); }
    [[nodiscard]] bool HasBlockingIssue() const noexcept
    {
        return policy_type_system::IsBlocking(kind) ||
               std::any_of(issues.begin(), issues.end(), [](const TPolicyRealizationEngineIssue& issue) { return issue.IsBlocking(); });
    }
    [[nodiscard]] bool MayProceedToFutureExecutor() const noexcept { return IsPositive() && !HasBlockingIssue(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
