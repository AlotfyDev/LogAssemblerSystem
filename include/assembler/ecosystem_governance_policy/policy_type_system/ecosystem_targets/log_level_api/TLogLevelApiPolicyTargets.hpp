#pragma once

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyFamilyTargetRuleSet.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyTargetIntegrationReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyTargetRegistryView.hpp"


namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TLogLevelApiPolicyTargets.hpp

 * Wave: EG-POL-W25_LogLevelApi_Policy_Targets
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / log_level_api
 *
 * Architectural boundary:
 *   W25 opens Phase E -- Ecosystem Integration by introducing policy-target
 *   descriptors for the Log Level API preparation domain. The wave maps
 *   governance-level policy vocabulary onto log-level API target categories
 *   such as validation, metadata injection, timestamp stabilization, envelope
 *   assembly, and API-facade admission. It is integration-facing but remains
 *   descriptive: it does not implement the Log Level API, validate content,
 *   inject metadata, stabilize timestamps, assemble envelopes, bind
 *   communication surfaces, assign policies, or realize policies.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and scope vocabulary.
 *   - W06 supplies descriptor-only target-kind language.
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
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-001 identifies preparation policy families such as validation,
 *   metadata injection, timestamp stabilization, and envelope assembly.
 *   EG-POL-ARCH-002 identifies preparation targets such as validator,
 *   metadata injector, timestamp stabilizer, envelope assembler, and API facade.
 *   EG-POL-ARCH-003 requires explicit compatibility between families and target
 *   capabilities before assignment or realization. W25 creates a conservative
 *   C++ integration skeleton for that log_level_api slice.
 *
 * Explicit non-responsibilities:
 *   This file does not implement log_level_api runtime behavior, content
 *   validation, envelope filling, metadata mutation, timestamp algorithms,
 *   policy assignment activation, authority roles, source publication,
 *   registry persistence, realization contracts, runtime execution,
 *   TPolicyExecutor, direct target invocation, material circulation,
 *   communication binding, add-on execution, telemetry, logging, or database
 *   persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete intended architectural responsibility
 *   while the code intentionally stays as compact value carriers and helpers
 *   for compile-smoke validation.
 * File responsibility:
 *   TLogLevelApiPolicyTargets is the W25 facade for describing log_level_api policy targets, their capability profiles, and their compatibility matrix rules. It can inspect and evaluate descriptors but does not assign, realize, or invoke policies or targets.
 */

struct TLogLevelApiPolicyTargets final
{
    TLogLevelApiPolicyTargetRegistryView registry_view{};
    TLogLevelApiPolicyFamilyTargetRuleSet rule_set{};

    [[nodiscard]] bool IsStructurallyComplete() const noexcept
    {
        return registry_view.IsCompleteForDefaultPreparationTargets() && !rule_set.IsEmpty();
    }

    [[nodiscard]] TLogLevelApiPolicyTargetIntegrationReport Inspect() const
    {
        TLogLevelApiPolicyTargetIntegrationReport report{};
        report.target_count = registry_view.targets.size();
        report.profile_count = registry_view.profiles.size();
        report.compatibility_rule_count = rule_set.matrix.rules.size();
        for (const auto& target : registry_view.targets)
        {
            if (target.IsValid()) ++report.valid_target_count;
            else report.AddIssue({TLogLevelApiPolicyTargetIntegrationIssueKind::invalid_target_descriptor,
                                  TLogLevelApiPolicyTargetIntegrationIssueSeverity::blocking,
                                  "invalid log_level_api policy target descriptor"});
        }
        if (registry_view.targets.empty())
        {
            report.AddIssue({TLogLevelApiPolicyTargetIntegrationIssueKind::missing_target_descriptor,
                              TLogLevelApiPolicyTargetIntegrationIssueSeverity::blocking,
                              "no log_level_api policy targets are described"});
        }
        if (registry_view.profiles.size() != registry_view.targets.size())
        {
            report.AddIssue({TLogLevelApiPolicyTargetIntegrationIssueKind::missing_capability_profile,
                              TLogLevelApiPolicyTargetIntegrationIssueSeverity::blocking,
                              "capability profile count does not match target descriptor count"});
        }
        if (rule_set.matrix.rules.empty())
        {
            report.AddIssue({TLogLevelApiPolicyTargetIntegrationIssueKind::missing_compatibility_rules,
                              TLogLevelApiPolicyTargetIntegrationIssueSeverity::blocking,
                              "no log_level_api compatibility rules are available"});
        }
        report.summary = report.Passed() ? "log_level_api policy target descriptors are structurally ready" :
                                           "log_level_api policy target descriptors need review";
        return report;
    }

    [[nodiscard]] TPolicyFamilyCompatibilityReport Evaluate(
        const TPolicyFamilyProfile& family_profile,
        TLogLevelApiPolicyTargetKind local_target_kind) const
    {
        const auto* target = registry_view.Find(local_target_kind);
        const auto* profile = registry_view.FindProfile(local_target_kind);
        if (target == nullptr || profile == nullptr)
        {
            return TPolicyFamilyCompatibilityReport::Incompatible(
                family_profile.kind,
                TPolicyTargetKind::log_level_api_component,
                "log_level_api target descriptor or capability profile is missing");
        }
        return rule_set.matrix.Evaluate(family_profile, target->ecosystem_target_kind, target->scope_path, profile->capabilities);
    }

    [[nodiscard]] static TLogLevelApiPolicyTargets Default()
    {
        TLogLevelApiPolicyTargets targets{};
        targets.registry_view = TLogLevelApiPolicyTargetRegistryView::Default();
        targets.rule_set = TLogLevelApiPolicyFamilyTargetRuleSet::Default();
        return targets;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system
