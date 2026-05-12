#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityMatrix.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationMode.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * Wave: EG-POL-W26_MaterialCirculation_Policy_Targets
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / material_circulation
 *
 * Architectural boundary:
 *   W26 continues Phase E -- Ecosystem Integration by introducing
 *   policy-target descriptors for the reusable Material Circulation domain.
 *   It maps ecosystem-governance policy vocabulary onto material-circulation
 *   target categories such as admission, slot lifecycle, container moderation,
 *   bundle coordination, waiting-list behavior, receiving/delivery rounds,
 *   reference precalculation, dispatcher behavior, and output-boundary handoff.
 *   The wave is integration-facing but remains descriptive: it does not
 *   implement material circulation mechanics, mutate slots, run round managers,
 *   dispatch payloads, activate assignments, bind communication surfaces, or
 *   realize policies.
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
 *   - W25 introduced the log_level_api policy-target slice; W26 mirrors that
 *     integration pattern for material_circulation.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-001 identifies material-circulation policy families such as
 *   material admission, slot lifecycle, waiting list, receiving round,
 *   delivery round, dispatcher, and reference precalculation policies.
 *   EG-POL-ARCH-002 identifies material-circulation target kinds and required
 *   target capabilities. EG-POL-ARCH-003 requires explicit compatibility
 *   between policy families, target kinds, target scopes, lifecycle,
 *   replacement, and observation expectations before assignment or realization.
 *   W26 creates a conservative C++ integration skeleton for that material
 *   circulation slice.
 *
 * Explicit non-responsibilities:
 *   This file does not implement material circulation runtime behavior, slot
 *   mutation, slots-container storage, waiting-list movement, round-manager
 *   algorithms, dispatcher execution, reference-precalculation algorithms,
 *   assignment activation, authority roles, source publication, registry
 *   persistence, realization contracts, runtime execution, TPolicyExecutor,
 *   direct target invocation, communication binding, add-on execution,
 *   telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete intended architectural responsibility
 *   while the code intentionally stays as compact value carriers and helpers
 *   for compile-smoke validation.
 */
/*
 * File responsibility:
 *   TMaterialCirculationPolicyFamilyTargetRuleSet owns the W26 default mapping
 *   from material-circulation policy families to material-circulation global
 *   target kinds and capability requirements. It does not activate
 *   assignments, run realizer sessions, or invoke material-circulation code.
 */
struct TMaterialCirculationPolicyFamilyTargetRuleSet final
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
        TPolicyTargetKind target,
        bool replacement_required,
        bool realization_required)
    {
        TPolicyFamilyCompatibilityRule rule;
        rule.rule_id = std::move(id);
        rule.policy_family_kind = family;
        rule.target_kind = target;
        rule.allowed_scopes = {TPolicyScope::component, TPolicyScope::instance, TPolicyScope::boundary};
        rule.required_capabilities = {
            TPolicyTargetCapabilityKind::accepts_policy_assignment,
            TPolicyTargetCapabilityKind::reports_lifecycle_state,
            TPolicyTargetCapabilityKind::supports_readiness_check,
            TPolicyTargetCapabilityKind::supports_diagnostic_view,
            TPolicyTargetCapabilityKind::declares_target_kind,
            TPolicyTargetCapabilityKind::declares_capability_set
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
        }
        rule.realization_mode = realization_required
            ? TPolicyRealizationMode::delegated_executor_path
            : TPolicyRealizationMode::descriptive_only;
        rule.lifecycle_required = true;
        rule.replacement_required = replacement_required;
        rule.observation_required = true;
        return rule;
    }

    [[nodiscard]] static TMaterialCirculationPolicyFamilyTargetRuleSet DefaultMaterialCirculationRules()
    {
        TMaterialCirculationPolicyFamilyTargetRuleSet set;
        const auto target = TPolicyTargetKind::material_circulation_component;
        set.Add(MakeRule("material_admission_to_material_component", TPolicyFamilyKind::admission, target, true, false));
        set.Add(MakeRule("runtime_coordination_to_material_component", TPolicyFamilyKind::runtime_coordination, target, true, true));
        set.Add(MakeRule("dispatch_to_material_component", TPolicyFamilyKind::dispatch, target, true, true));
        set.Add(MakeRule("replacement_to_material_component", TPolicyFamilyKind::replacement, target, true, false));
        set.Add(MakeRule("diagnostic_to_material_component", TPolicyFamilyKind::diagnostic, target, false, false));
        set.Add(MakeRule("execution_readiness_to_material_component", TPolicyFamilyKind::execution_readiness, target, true, true));
        return set;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
