#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicySurfaceDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilitySet.hpp"

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
 *   TCommunicationContextPolicySurfaceCapabilityProfile binds a Communication
 *   Context policy-surface descriptor to a declared capability set. It is a
 *   compatibility input and not a method surface, live ASCC object, endpoint
 *   handle, bridge stepper, or runtime invocation path.
 */
struct TCommunicationContextPolicySurfaceCapabilityProfile final
{
    TCommunicationContextPolicySurfaceDescriptor descriptor{};
    TPolicyTargetCapabilitySet capabilities{};
    std::vector<TPolicyTargetCapabilityKind> required_capabilities{};
    std::string note{};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return descriptor.IsValid() && !capabilities.IsEmpty();
    }

    [[nodiscard]] bool SatisfiesRequiredCapabilities() const noexcept
    {
        return capabilities.Satisfies(required_capabilities);
    }

    [[nodiscard]] bool IsReadyForCompatibility() const noexcept
    {
        return IsValid() && SatisfiesRequiredCapabilities() && descriptor.endpoint_neutral;
    }

    [[nodiscard]] static TCommunicationContextPolicySurfaceCapabilityProfile MakeDefault(
        TCommunicationContextPolicySurfaceDescriptor descriptor)
    {
        TCommunicationContextPolicySurfaceCapabilityProfile profile;
        profile.descriptor = std::move(descriptor);
        const auto target = profile.descriptor.global_kind;
        auto add = [&](TPolicyTargetCapabilityKind kind) {
            TPolicyTargetCapabilityDescriptor capability;
            capability.kind = kind;
            capability.target_kind = target;
            capability.capability_id = TPolicyTargetCapabilityId{static_cast<TPolicyTargetCapabilityId::value_type>(kind) + 2000u};
            capability.strength = TPolicyTargetCapabilityStrength::required;
            capability.mutability = TPolicyTargetCapabilityMutability::read_only;
            capability.canonical_name = "communication_context_capability";
            profile.capabilities.Add(capability);
            profile.required_capabilities.push_back(kind);
        };
        add(TPolicyTargetCapabilityKind::accepts_policy_assignment);
        add(TPolicyTargetCapabilityKind::reports_lifecycle_state);
        add(TPolicyTargetCapabilityKind::supports_readiness_check);
        add(TPolicyTargetCapabilityKind::supports_diagnostic_view);
        add(TPolicyTargetCapabilityKind::declares_target_kind);
        add(TPolicyTargetCapabilityKind::declares_capability_set);
        add(TPolicyTargetCapabilityKind::supports_compatibility_evaluation);
        add(TPolicyTargetCapabilityKind::supports_incompatibility_report);
        if (profile.descriptor.RequiresReplacementDiscipline())
        {
            add(TPolicyTargetCapabilityKind::has_safe_replacement_point);
            add(TPolicyTargetCapabilityKind::reports_replacement_eligibility);
            add(TPolicyTargetCapabilityKind::supports_replacement_observation);
        }
        if (profile.descriptor.realization_capable)
        {
            add(TPolicyTargetCapabilityKind::supports_policy_realization_surface);
            add(TPolicyTargetCapabilityKind::supports_realization_result);
            add(TPolicyTargetCapabilityKind::supports_realization_failure_report);
            add(TPolicyTargetCapabilityKind::supports_realization_trace);
        }
        return profile;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
