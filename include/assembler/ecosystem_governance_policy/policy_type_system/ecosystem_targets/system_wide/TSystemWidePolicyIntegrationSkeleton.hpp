#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/system_wide/TSystemWidePolicyIntegrationIdSet.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/system_wide/TSystemWidePolicyIntegrationPlan.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/system_wide/TSystemWidePolicyIntegrationReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/system_wide/TSystemWidePolicyTargetSet.hpp"

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
 *   TSystemWidePolicyIntegrationSkeleton is the W29 facade for composing the
 *   major ecosystem policy-target slices with non-owning policy, registry,
 *   assignment, readiness, plan, and realizer references. It is the first
 *   system-wide integration skeleton, not a production runtime and not a
 *   policy execution engine.
 */
struct TSystemWidePolicyIntegrationSkeleton final
{
    TSystemWidePolicyIntegrationIdSet ids{};
    TSystemWidePolicyTargetSet targets{};
    TSystemWidePolicyIntegrationPlan plan{};
    std::string name{"system_wide_policy_integration_skeleton"};

    [[nodiscard]] bool IsStructurallyComplete() const noexcept
    {
        return ids.HasPolicyRegistryAndAssignment() &&
               ids.HasReadinessPathRefs() &&
               ids.HasRealizerRef() &&
               targets.HasAllCoreSlices() &&
               plan.IsStructurallyComplete();
    }

    [[nodiscard]] TSystemWidePolicyIntegrationReport Inspect() const
    {
        TSystemWidePolicyIntegrationReport report{};
        report.plan_steps = plan.steps.size();
        report.target_slices_present =
            (targets.log_level_api.IsStructurallyComplete() ? 1u : 0u) +
            (targets.material_circulation.IsStructurallyComplete() ? 1u : 0u) +
            (targets.communication_context.IsStructurallyComplete() ? 1u : 0u) +
            (targets.addons.IsStructurallyComplete() ? 1u : 0u);

        if (!ids.HasPolicyRegistryAndAssignment())
        {
            report.AddIssue({TSystemWidePolicyIntegrationIssueSeverity::blocking,
                             TSystemWidePolicyIntegrationIssueKind::missing_policy_refs,
                             "policy, registry, or assignment identity is missing"});
        }
        if (!ids.HasReadinessPathRefs())
        {
            report.AddIssue({TSystemWidePolicyIntegrationIssueSeverity::blocking,
                             TSystemWidePolicyIntegrationIssueKind::missing_readiness_or_plan_refs,
                             "realization contract or runtime plan identity is missing"});
        }
        if (!ids.HasRealizerRef())
        {
            report.AddIssue({TSystemWidePolicyIntegrationIssueSeverity::blocking,
                             TSystemWidePolicyIntegrationIssueKind::missing_realizer_refs,
                             "realizer identity is missing"});
        }
        if (!targets.HasAllCoreSlices())
        {
            report.AddIssue({TSystemWidePolicyIntegrationIssueSeverity::blocking,
                             TSystemWidePolicyIntegrationIssueKind::incomplete_system_wide_target_set,
                             "one or more ecosystem target slices are incomplete"});
        }
        if (!plan.IsStructurallyComplete())
        {
            report.AddIssue({TSystemWidePolicyIntegrationIssueSeverity::blocking,
                             TSystemWidePolicyIntegrationIssueKind::missing_readiness_or_plan_refs,
                             "system-wide integration plan is incomplete"});
        }
        report.summary = report.IsPositive()
            ? "system-wide policy integration skeleton is structurally ready"
            : "system-wide policy integration skeleton needs review";
        return report;
    }

    [[nodiscard]] static TSystemWidePolicyIntegrationSkeleton DefaultDemo()
    {
        TSystemWidePolicyIntegrationSkeleton skeleton{};
        skeleton.ids.policy_id.value = 2901;
        skeleton.ids.registry_entry_id.value = 2902;
        skeleton.ids.assignment_id.value = 2903;
        skeleton.ids.contract_id.value = 2904;
        skeleton.ids.runtime_plan_id.value = 2905;
        skeleton.ids.realizer_id.value = 2906;
        skeleton.targets = TSystemWidePolicyTargetSet::Default();
        skeleton.plan = TSystemWidePolicyIntegrationPlan::Default();
        return skeleton;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
