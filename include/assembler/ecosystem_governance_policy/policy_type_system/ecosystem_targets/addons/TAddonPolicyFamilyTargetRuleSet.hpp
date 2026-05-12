#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityMatrix.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationMode.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TAddonPolicyFamilyTargetRuleSet.hpp
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
 *   TAddonPolicyFamilyTargetRuleSet owns default policy-family-to-addon-target compatibility rules. It configures rule carriers only; it does not activate assignments, invoke add-ons, or run realization.
 */

struct TAddonPolicyFamilyTargetRuleSet final
{
    TPolicyFamilyCompatibilityMatrix matrix{};

    [[nodiscard]] bool IsEmpty() const noexcept
    {
        return matrix.rules.empty();
    }

    void Add(TPolicyFamilyCompatibilityRule rule)
    {
        matrix.AddRule(std::move(rule));
    }

    [[nodiscard]] static TPolicyFamilyCompatibilityRule MakeRule(
        std::string id,
        TPolicyFamilyKind family,
        bool replacement_required,
        bool realization_required)
    {
        TPolicyFamilyCompatibilityRule rule;
        rule.rule_id = std::move(id);
        rule.policy_family_kind = family;
        rule.target_kind = TPolicyTargetKind::addon_adapter;
        rule.allowed_scopes = {TPolicyScope::component, TPolicyScope::instance, TPolicyScope::boundary};
        rule.required_capabilities = {
            TPolicyTargetCapabilityKind::accepts_policy_assignment,
            TPolicyTargetCapabilityKind::reports_lifecycle_state,
            TPolicyTargetCapabilityKind::supports_readiness_check,
            TPolicyTargetCapabilityKind::supports_policy_observation_record,
            TPolicyTargetCapabilityKind::supports_diagnostic_view,
            TPolicyTargetCapabilityKind::declares_target_kind,
            TPolicyTargetCapabilityKind::declares_capability_set,
            TPolicyTargetCapabilityKind::supports_compatibility_evaluation,
            TPolicyTargetCapabilityKind::supports_realization_failure_report,
            TPolicyTargetCapabilityKind::supports_incompatibility_report
        };
        if (replacement_required)
        {
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::has_safe_replacement_point);
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::reports_replacement_eligibility);
        }
        if (realization_required)
        {
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_policy_realization_surface);
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_realization_result);
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_realization_trace);
        }
        rule.realization_mode = realization_required ?
            TPolicyRealizationMode::delegated_executor_path :
            TPolicyRealizationMode::descriptive_only;
        rule.lifecycle_required = true;
        rule.replacement_required = replacement_required;
        rule.observation_required = true;
        rule.authority_required = true;
        rule.registry_required = true;
        return rule;
    }

    [[nodiscard]] static TAddonPolicyFamilyTargetRuleSet Default()
    {
        TAddonPolicyFamilyTargetRuleSet set;
        set.Add(MakeRule("addon_family_to_addon_adapter", TPolicyFamilyKind::addon, false, true));
        set.Add(MakeRule("port_family_to_addon_adapter", TPolicyFamilyKind::port, true, true));
        set.Add(MakeRule("diagnostic_family_to_addon_adapter", TPolicyFamilyKind::diagnostic, false, false));
        set.Add(MakeRule("governance_family_to_addon_adapter", TPolicyFamilyKind::governance, false, false));
        set.Add(MakeRule("execution_readiness_family_to_addon_adapter", TPolicyFamilyKind::execution_readiness, true, true));
        return set;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
