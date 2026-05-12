#pragma once

#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/system_wide/TSystemWidePolicyIntegrationPlanStep.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * Wave: EG-POL-W29_System_Wide_Policy_Integration_Skeleton
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / system_wide
 *
 * Architectural boundary:
 *   W29 closes the first Phase E ecosystem-integration slice by introducing a
 *   system-wide policy integration skeleton. It composes the descriptive
 *   target surfaces introduced in W25, W26, W27, and W28 and names the
 *   governance path from published policy metadata, assignment identity,
 *   target descriptors, runtime-readiness evidence, runtime plan, and
 *   realizer-facing identity into one inspectable integration artifact.
 *
 *   This wave is explicitly non-executing. It does not activate assignments,
 *   invoke a realizer, run an engine, mutate targets, bind communication
 *   participants, move material through material circulation, call add-ons, or
 *   persist registry records. It only checks whether the major ecosystem
 *   target slices are present and represented in a conservative, boundary-safe
 *   C++17 form.
 *
 * Relationship to prior waves:
 *   - W01-W11 define the base policy type system, aggregate, assignment, and
 *     registry basics.
 *   - W12-W17 add family/scope, target capabilities, compatibility, assignment
 *     lifecycle, source/publication, and registry versioning views.
 *   - W18-W20 add realization contract, runtime readiness, and runtime plan
 *     pre-execution artifacts.
 *   - W21-W24 add realizer interface, realization session, execution-plan, and
 *     realization-engine skeleton layers without production runtime execution.
 *   - W25-W28 add the log_level_api, material_circulation,
 *     communication_context, and add-on ecosystem target slices.
 *
 * Relationship to Phase A architecture:
 *   Phase A required a system-wide policy-to-target matrix and compliance gate
 *   before any realizer/runtime path. W29 is not that final compliance engine;
 *   it is a concrete integration skeleton that proves the major descriptive
 *   surfaces can be composed without collapsing publication into assignment,
 *   assignment into realization, realization into execution, target kind into
 *   target instance, or registry lookup into service location.
 *
 * Explicit non-responsibilities:
 *   This file does not implement runtime execution, target invocation, target
 *   mutation, policy assignment activation, persistent registry storage,
 *   source parsing, communication binding, material circulation runtime
 *   behavior, add-on execution, telemetry export, logging, or database
 *   persistence.
 *
 * Current implementation posture:
 *   The code is a conservative header-only C++17 foundation. The opening
 *   documentation describes the complete architectural responsibility while
 *   the code remains compact value carriers and inspection helpers for compile
 *   smoke validation.
 */

/*
 * File responsibility:
 *   TSystemWidePolicyIntegrationPlan is a non-executing checklist for the
 *   system-wide policy integration skeleton. It describes the intended order of
 *   governance inspection; it is not a scheduler and not an execution plan for
 *   a live target.
 */
struct TSystemWidePolicyIntegrationPlan final
{
    std::vector<TSystemWidePolicyIntegrationPlanStep> steps{};

    [[nodiscard]] bool IsEmpty() const noexcept { return steps.empty(); }

    [[nodiscard]] bool IsStructurallyComplete() const noexcept
    {
        if (steps.size() < 6) return false;
        for (const auto& step : steps)
        {
            if (!step.IsKnown()) return false;
        }
        return true;
    }

    [[nodiscard]] static TSystemWidePolicyIntegrationPlan Default()
    {
        TSystemWidePolicyIntegrationPlan plan{};
        plan.steps = {
            {TSystemWidePolicyIntegrationPlanStepKind::locate_published_policy, "locate a registry-visible published policy descriptor"},
            {TSystemWidePolicyIntegrationPlanStepKind::inspect_assignment, "inspect a non-executing assignment relation"},
            {TSystemWidePolicyIntegrationPlanStepKind::resolve_target_slice, "resolve the descriptive ecosystem target slice"},
            {TSystemWidePolicyIntegrationPlanStepKind::inspect_runtime_readiness, "inspect runtime readiness evidence"},
            {TSystemWidePolicyIntegrationPlanStepKind::inspect_runtime_plan, "inspect a pre-execution runtime plan"},
            {TSystemWidePolicyIntegrationPlanStepKind::inspect_realizer_surface, "inspect the realizer-facing interface surface"},
            {TSystemWidePolicyIntegrationPlanStepKind::produce_integration_report, "produce a non-executing integration report"}
        };
        return plan;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
