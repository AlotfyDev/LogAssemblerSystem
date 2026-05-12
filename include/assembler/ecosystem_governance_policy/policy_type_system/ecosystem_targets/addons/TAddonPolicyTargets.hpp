#pragma once

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyFamilyTargetRuleSet.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyTargetIntegrationReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyTargetRegistryView.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TAddonPolicyTargets.hpp
 * Wave: EG-POL-W28_Addon_Policy_Targets
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / addons
 *
 * Architectural boundary:
 *   W28 continues Phase E -- Ecosystem Integration by introducing policy-target
 *   descriptors for optional add-on adapters beyond Thin C ABI and other
 *   extension boundaries. It maps ecosystem-governance policy vocabulary onto
 *   add-on target categories such as database adapters, telemetry adapters,
 *   file-sink adapters, diagnostic sinks, foreign runtime adapters, Thin C ABI
 *   adapter boundaries, receiver adapters, and add-on assignment boundaries.
 *
 *   The wave is integration-facing but remains descriptive. It does not run an
 *   add-on, write to a database, export telemetry, call a foreign runtime,
 *   invoke a Thin C ABI callback, mutate receiver state, activate assignments,
 *   or realize policies. It describes the governance-facing target slice that
 *   later compatibility, assignment, authority, runtime readiness, and realizer
 *   layers may consume.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and scope vocabulary.
 *   - W06 supplies descriptor-only target-kind and realization-binding language.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12 supplies policy-family and scope profiles.
 *   - W13 supplies target-capability descriptors and capability sets.
 *   - W14 supplies family-target compatibility rule/report vocabulary.
 *   - W15 supplies assignment lifecycle/conflict vocabulary.
 *   - W16/W17 supply source/publication and registry-versioning views.
 *   - W18-W20 supply realization contract, runtime readiness, and runtime plan
 *     pre-execution artifacts.
 *   - W21-W24 supply realizer-facing, session, execution-plan, and engine
 *     skeleton layers without production execution.
 *   - W25 introduced the log_level_api policy-target slice.
 *   - W26 introduced the material_circulation policy-target slice.
 *   - W27 introduced the communication_context policy-surface slice.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-001 identifies add-on policy families such as database add-on,
 *   telemetry add-on, file sink, Thin C ABI passage, and foreign-runtime
 *   policies. EG-POL-ARCH-002 identifies add-on target kinds and capability
 *   requirements. EG-POL-ARCH-003 requires explicit compatibility before
 *   assignment or realization. W28 creates a conservative C++ integration
 *   skeleton for that add-on slice.
 *
 * Explicit non-responsibilities:
 *   This file does not implement add-on runtime behavior, database writes,
 *   telemetry export, file I/O, foreign-runtime calls, receiver retries, Thin C
 *   ABI invocation, assignment activation, authority roles, source publication,
 *   registry persistence, realization contracts, runtime execution,
 *   TPolicyExecutor, direct target invocation, material circulation behavior,
 *   communication binding, logging, or persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete intended architectural responsibility
 *   while the code intentionally stays as compact value carriers and helpers
 *   for compile-smoke validation.
 *
 * File responsibility:
 *   TAddonPolicyTargets is the W28 facade for describing add-on policy targets, their capability profiles, and their compatibility matrix rules. It can inspect and evaluate descriptors but does not assign, realize, invoke, or run add-ons.
 */

struct TAddonPolicyTargets final
{
    TAddonPolicyTargetRegistryView registry_view{};
    TAddonPolicyFamilyTargetRuleSet rule_set{};

    [[nodiscard]] bool IsStructurallyComplete() const noexcept
    {
        return registry_view.IsCompleteForCoreAddonTargets() && !rule_set.IsEmpty();
    }

    [[nodiscard]] TAddonPolicyTargetIntegrationReport Inspect() const
    {
        TAddonPolicyTargetIntegrationReport report{};
        report.described_targets = registry_view.targets.size();
        report.compatibility_rules = rule_set.matrix.rules.size();
        if (registry_view.targets.empty())
        {
            report.AddIssue(TAddonPolicyTargetIntegrationIssueSeverity::blocking,
                            TAddonPolicyTargetIntegrationIssueKind::missing_target,
                            "no add-on policy targets are described");
        }
        for (const auto& target : registry_view.targets)
        {
            if (!target.IsReadyForCompatibility())
            {
                report.AddIssue(TAddonPolicyTargetIntegrationIssueSeverity::blocking,
                                TAddonPolicyTargetIntegrationIssueKind::missing_capability_profile,
                                "add-on policy target capability profile is not ready");
            }
        }
        if (rule_set.matrix.rules.empty())
        {
            report.AddIssue(TAddonPolicyTargetIntegrationIssueSeverity::blocking,
                            TAddonPolicyTargetIntegrationIssueKind::missing_compatibility_rule,
                            "no add-on compatibility rules are available");
        }
        if (!registry_view.IsCompleteForCoreAddonTargets())
        {
            report.AddIssue(TAddonPolicyTargetIntegrationIssueSeverity::warning,
                            TAddonPolicyTargetIntegrationIssueKind::incomplete_registry_view,
                            "core add-on target registry view is incomplete");
        }
        return report;
    }

    [[nodiscard]] TPolicyFamilyCompatibilityReport Evaluate(
        const TPolicyFamilyProfile& family_profile,
        TAddonPolicyTargetKind local_target_kind) const
    {
        const auto* profile = registry_view.Find(local_target_kind);
        if (profile == nullptr)
        {
            return TPolicyFamilyCompatibilityReport::Incompatible(
                family_profile.kind,
                TPolicyTargetKind::addon_adapter,
                "add-on target capability profile is missing");
        }
        return rule_set.matrix.Evaluate(
            family_profile,
            profile->descriptor.global_kind,
            profile->descriptor.scope_path,
            profile->capabilities);
    }

    [[nodiscard]] static TAddonPolicyTargets Default()
    {
        TAddonPolicyTargets targets;
        targets.registry_view = TAddonPolicyTargetRegistryView::Default();
        targets.rule_set = TAddonPolicyFamilyTargetRuleSet::Default();
        return targets;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
