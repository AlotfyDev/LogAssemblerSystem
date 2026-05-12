#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicySurfaceKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"

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
 *   TCommunicationContextPolicySurfaceDescriptor describes one Communication
 *   Context surface as a policy-governable target descriptor. It bridges the
 *   communication-context-local surface taxonomy to the global target-kind
 *   vocabulary without owning a concrete channel, binding, session, bridge, or
 *   endpoint object and without invoking behavior.
 */
struct TCommunicationContextPolicySurfaceDescriptor final
{
    std::string surface_id{};
    TCommunicationContextPolicySurfaceKind local_kind{TCommunicationContextPolicySurfaceKind::unknown};
    TPolicyTargetKind global_kind{TPolicyTargetKind::communication_boundary_surface};
    TPolicyScopePath scope_path{};
    bool endpoint_neutral{true};
    bool lifecycle_sensitive{false};
    bool replacement_sensitive{false};
    bool observation_required{true};
    bool realization_capable{false};
    std::string note{};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return !surface_id.empty() &&
               IsKnownCommunicationContextPolicySurfaceKind(local_kind) &&
               IsKnown(global_kind) &&
               scope_path.IsSpecified();
    }

    [[nodiscard]] bool IsDescriptorOnly() const noexcept
    {
        return IsValid() && endpoint_neutral;
    }

    [[nodiscard]] bool RequiresReplacementDiscipline() const noexcept
    {
        return replacement_sensitive || IsReplacementSensitiveCommunicationSurface(local_kind);
    }

    [[nodiscard]] bool IsLifecycleSurface() const noexcept
    {
        return lifecycle_sensitive || IsCommunicationLifecycleSurface(local_kind);
    }

    [[nodiscard]] static TCommunicationContextPolicySurfaceDescriptor Make(
        std::string id,
        TCommunicationContextPolicySurfaceKind kind,
        TPolicyScopePath scope,
        bool realization = false)
    {
        TCommunicationContextPolicySurfaceDescriptor descriptor;
        descriptor.surface_id = std::move(id);
        descriptor.local_kind = kind;
        descriptor.scope_path = std::move(scope);
        descriptor.realization_capable = realization;
        descriptor.lifecycle_sensitive = IsCommunicationLifecycleSurface(kind);
        descriptor.replacement_sensitive = IsReplacementSensitiveCommunicationSurface(kind);
        descriptor.endpoint_neutral = true;
        return descriptor;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
