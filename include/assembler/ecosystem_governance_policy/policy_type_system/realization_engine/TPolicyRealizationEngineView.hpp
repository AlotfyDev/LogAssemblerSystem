#pragma once

#include <cstdint>

#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationEngineView.hpp
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
 *   TPolicyRealizationEngineView is the read-only projection of the engine skeleton state. It exposes identity, status, step budget, inspection counters, and trace/evidence presence. It is not a mutable handle and does not grant execution authority.
 */
struct TPolicyRealizationEngineView final
{
    TPolicyRealizationEngineId engine_id{};
    TPolicyRealizationEngineStatus status{TPolicyRealizationEngineStatus::unknown};
    std::uint64_t max_plan_steps{0};
    std::uint64_t inspected_plan_count{0};
    bool has_authority_evidence_requirement{true};
    bool has_trace_requirement{true};

    [[nodiscard]] bool IsInspectable() const noexcept
    {
        return engine_id.IsValid() && policy_type_system::IsPositive(status) && max_plan_steps != 0;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
