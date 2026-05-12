#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityMatrix.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * Wave: EG-POL-W27_CommunicationContext_Policy_Surface
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / communication_context
 *
 * Architectural boundary:
 *   W27 continues Phase E -- Ecosystem Integration by introducing the policy
 *   surface for the Communication Context domain. It maps ecosystem-governance
 *   policy vocabulary onto communication-context target/surface categories such
 *   as channel topology, binding declarations, compatibility evaluation,
 *   session lifecycle, bridge protocol model, bridge-core orchestration,
 *   endpoint-neutral diagnostics, optional bounded registries, plugin-adapter
 *   boundary surfaces, and outbound port boundary surfaces.
 *
 *   The wave is integration-facing but remains descriptive. It does not run
 *   bridge steps, open sessions, evaluate live endpoints, invoke adapters or
 *   ports, mutate channels, bind real communication participants, schedule
 *   protocol execution, or realize policies. It describes the governance-facing
 *   target surface that later compatibility, assignment, authority, runtime
 *   readiness, and realizer layers may consume.
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
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-001 identifies communication policy families: channel, binding,
 *   compatibility, session, protocol, bridge-core, and diagnostic policies.
 *   EG-POL-ARCH-002 identifies communication target kinds and required target
 *   capabilities. EG-POL-ARCH-003 requires explicit compatibility between
 *   policy families, target kinds, target scopes, lifecycle, replacement, and
 *   observation expectations before assignment or realization. W27 creates a
 *   conservative C++ integration skeleton for the communication_context slice.
 *
 * Explicit non-responsibilities:
 *   This file does not implement Communication Context runtime behavior,
 *   Channel mutation, Binding creation, compatibility execution against live
 *   endpoints, Session opening, BridgeProtocol execution, BridgeCore stepping,
 *   PluginAdapter invocation, Port invocation, endpoint ownership, assignment
 *   activation, authority roles, source publication, registry persistence,
 *   realization contracts, runtime execution, TPolicyExecutor, direct target
 *   invocation, material circulation behavior, add-on execution, telemetry,
 *   logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete intended architectural responsibility
 *   while the code intentionally stays as compact value carriers and helpers
 *   for compile-smoke validation.
 */

/*
 * File responsibility:
 *   TCommunicationContextPolicyFamilySurfaceRuleSet owns the W27 default
 *   mapping from communication policy families to communication-boundary
 *   target kinds and capability requirements. It does not activate assignments,
 *   open sessions, evaluate live compatibility, run bridge protocols, or invoke
 *   adapters/ports.
 */
struct TCommunicationContextPolicyFamilySurfaceRuleSet final
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
        bool realization_required,
        bool registry_required = false)
    {
        TPolicyFamilyCompatibilityRule rule;
        rule.rule_id = std::move(id);
        rule.policy_family_kind = family;
        rule.target_kind = TPolicyTargetKind::communication_boundary_surface;
        rule.allowed_scopes = {TPolicyScope::domain, TPolicyScope::component, TPolicyScope::boundary, TPolicyScope::instance};
        rule.required_capabilities = {
            TPolicyTargetCapabilityKind::accepts_policy_assignment,
            TPolicyTargetCapabilityKind::reports_lifecycle_state,
            TPolicyTargetCapabilityKind::supports_readiness_check,
            TPolicyTargetCapabilityKind::supports_diagnostic_view,
            TPolicyTargetCapabilityKind::declares_target_kind,
            TPolicyTargetCapabilityKind::declares_capability_set,
            TPolicyTargetCapabilityKind::supports_compatibility_evaluation,
            TPolicyTargetCapabilityKind::supports_incompatibility_report
        };
        if (replacement_required)
        {
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::has_safe_replacement_point);
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::reports_replacement_eligibility);
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_replacement_observation);
        }
        if (realization_required)
        {
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_policy_realization_surface);
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_realization_result);
            rule.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_realization_trace);
        }
        rule.realization_mode = realization_required
            ? TPolicyRealizationMode::delegated_executor_path
            : TPolicyRealizationMode::descriptive_only;
        rule.lifecycle_required = true;
        rule.replacement_required = replacement_required;
        rule.observation_required = true;
        rule.authority_required = false;
        rule.registry_required = registry_required;
        return rule;
    }

    [[nodiscard]] static TCommunicationContextPolicyFamilySurfaceRuleSet DefaultCommunicationContextRules()
    {
        TCommunicationContextPolicyFamilySurfaceRuleSet set;
        set.Add(MakeRule("channel_policy_to_communication_surface", TPolicyFamilyKind::communication, true, false));
        set.Add(MakeRule("protocol_policy_to_communication_surface", TPolicyFamilyKind::runtime_coordination, true, true));
        set.Add(MakeRule("diagnostic_policy_to_communication_surface", TPolicyFamilyKind::diagnostic, false, false));
        set.Add(MakeRule("governance_policy_to_communication_surface", TPolicyFamilyKind::governance, false, false, true));
        set.Add(MakeRule("execution_readiness_to_communication_surface", TPolicyFamilyKind::execution_readiness, true, true));
        return set;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
