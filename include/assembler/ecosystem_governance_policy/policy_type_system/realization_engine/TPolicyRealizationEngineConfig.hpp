#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationEngineConfig.hpp
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
 *   TPolicyRealizationEngineConfig describes how an engine skeleton may be identified and constrained for inspection-only use. It is not a scheduler config, not a target-binding config, and not an execution runtime configuration.
 */
struct TPolicyRealizationEngineConfig final
{
    TPolicyRealizationEngineId engine_id{};
    std::uint64_t max_plan_steps{0};
    bool require_authority_evidence{true};
    bool require_trace{true};
    bool allow_forbidden_plans{false};
    std::string label{};

    [[nodiscard]] bool HasIdentity() const noexcept { return engine_id.IsValid(); }
    [[nodiscard]] bool HasStepBudget() const noexcept { return max_plan_steps != 0; }
    [[nodiscard]] bool IsUsableForInspection() const noexcept { return HasIdentity() && HasStepBudget(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
