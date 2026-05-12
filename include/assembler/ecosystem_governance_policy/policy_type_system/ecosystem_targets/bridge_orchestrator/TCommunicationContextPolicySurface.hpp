#pragma once

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicyFamilySurfaceRuleSet.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicySurfaceIntegrationReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicySurfaceRegistryView.hpp"

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
 *   TCommunicationContextPolicySurface is the W27 facade for describing
 *   Communication Context policy-governable surfaces, their capability
 *   profiles, and their compatibility matrix rules. It can inspect and
 *   evaluate descriptors but does not assign, realize, invoke, bind, or execute
 *   communication behavior.
 */
struct TCommunicationContextPolicySurface final
{
    TCommunicationContextPolicySurfaceRegistryView registry_view{};
    TCommunicationContextPolicyFamilySurfaceRuleSet rule_set{};

    [[nodiscard]] bool IsStructurallyComplete() const noexcept
    {
        return registry_view.IsCompleteForCoreCommunicationSurfaces() && !rule_set.IsEmpty();
    }

    [[nodiscard]] TCommunicationContextPolicySurfaceIntegrationReport Inspect() const
    {
        TCommunicationContextPolicySurfaceIntegrationReport report;
        report.described_surfaces = registry_view.surfaces.size();
        report.capability_profiles = registry_view.surfaces.size();
        report.compatibility_rules = rule_set.matrix.rules.size();
        for (const auto& surface : registry_view.surfaces)
        {
            if (!surface.descriptor.IsValid())
            {
                report.AddIssue(TCommunicationContextPolicySurfaceIntegrationIssueSeverity::blocking,
                                TCommunicationContextPolicySurfaceIntegrationIssueKind::missing_surface,
                                "invalid communication_context policy surface descriptor");
            }
            if (!surface.SatisfiesRequiredCapabilities())
            {
                report.AddIssue(TCommunicationContextPolicySurfaceIntegrationIssueSeverity::blocking,
                                TCommunicationContextPolicySurfaceIntegrationIssueKind::missing_capability_profile,
                                "communication_context capability profile does not satisfy required capabilities");
            }
            if (!surface.descriptor.endpoint_neutral)
            {
                report.AddIssue(TCommunicationContextPolicySurfaceIntegrationIssueSeverity::critical,
                                TCommunicationContextPolicySurfaceIntegrationIssueKind::non_endpoint_neutral_surface,
                                "communication_context policy surface must remain endpoint-neutral");
            }
        }
        if (!registry_view.IsCompleteForCoreCommunicationSurfaces())
        {
            report.AddIssue(TCommunicationContextPolicySurfaceIntegrationIssueSeverity::blocking,
                            TCommunicationContextPolicySurfaceIntegrationIssueKind::incomplete_registry_view,
                            "communication_context surface registry view is incomplete for core surfaces");
        }
        if (rule_set.matrix.rules.empty())
        {
            report.AddIssue(TCommunicationContextPolicySurfaceIntegrationIssueSeverity::blocking,
                            TCommunicationContextPolicySurfaceIntegrationIssueKind::missing_compatibility_rule,
                            "no communication_context policy compatibility rules are available");
        }
        report.summary = report.IsPositive()
            ? "communication_context policy surface descriptors are structurally ready"
            : "communication_context policy surface descriptors need review";
        return report;
    }

    [[nodiscard]] TPolicyFamilyCompatibilityReport Evaluate(
        const TPolicyFamilyProfile& family_profile,
        TCommunicationContextPolicySurfaceKind local_surface_kind) const
    {
        const auto* profile = registry_view.Find(local_surface_kind);
        if (profile == nullptr)
        {
            return TPolicyFamilyCompatibilityReport::Incompatible(
                family_profile.kind,
                TPolicyTargetKind::communication_boundary_surface,
                "communication_context surface descriptor or capability profile is missing");
        }
        return rule_set.matrix.Evaluate(
            family_profile,
            profile->descriptor.global_kind,
            profile->descriptor.scope_path,
            profile->capabilities);
    }

    [[nodiscard]] static TCommunicationContextPolicySurface Default()
    {
        TCommunicationContextPolicySurface surface;
        surface.registry_view = TCommunicationContextPolicySurfaceRegistryView::Default();
        surface.rule_set = TCommunicationContextPolicyFamilySurfaceRuleSet::DefaultCommunicationContextRules();
        return surface;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
