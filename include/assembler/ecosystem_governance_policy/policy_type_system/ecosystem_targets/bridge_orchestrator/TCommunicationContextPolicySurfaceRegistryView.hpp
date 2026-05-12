#pragma once

#include <algorithm>
#include <vector>
#include <initializer_list>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicySurfaceCapabilityProfile.hpp"

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
 *   TCommunicationContextPolicySurfaceRegistryView is an in-memory view of the
 *   W27 Communication Context policy-surface descriptors and capability
 *   profiles. It is not the policy registry, an ASCC registry, a service
 *   locator, target locator, endpoint registry, or persistence layer.
 */
struct TCommunicationContextPolicySurfaceRegistryView final
{
    std::vector<TCommunicationContextPolicySurfaceCapabilityProfile> surfaces{};

    void Add(TCommunicationContextPolicySurfaceCapabilityProfile profile)
    {
        if (!profile.descriptor.IsValid()) return;
        auto it = std::find_if(surfaces.begin(), surfaces.end(), [&](const auto& item) {
            return item.descriptor.surface_id == profile.descriptor.surface_id;
        });
        if (it == surfaces.end()) surfaces.push_back(std::move(profile));
        else *it = std::move(profile);
    }

    [[nodiscard]] const TCommunicationContextPolicySurfaceCapabilityProfile* Find(
        TCommunicationContextPolicySurfaceKind kind) const noexcept
    {
        auto it = std::find_if(surfaces.begin(), surfaces.end(), [&](const auto& item) {
            return item.descriptor.local_kind == kind;
        });
        return it == surfaces.end() ? nullptr : &(*it);
    }

    [[nodiscard]] bool Has(TCommunicationContextPolicySurfaceKind kind) const noexcept
    {
        return Find(kind) != nullptr;
    }

    [[nodiscard]] bool IsCompleteForCoreCommunicationSurfaces() const noexcept
    {
        return Has(TCommunicationContextPolicySurfaceKind::channel_topology) &&
               Has(TCommunicationContextPolicySurfaceKind::binding_declaration) &&
               Has(TCommunicationContextPolicySurfaceKind::compatibility_evaluator) &&
               Has(TCommunicationContextPolicySurfaceKind::session_lifecycle) &&
               Has(TCommunicationContextPolicySurfaceKind::bridge_protocol_model) &&
               Has(TCommunicationContextPolicySurfaceKind::bridge_core) &&
               Has(TCommunicationContextPolicySurfaceKind::diagnostics);
    }

    [[nodiscard]] static TCommunicationContextPolicySurfaceRegistryView Default()
    {
        TCommunicationContextPolicySurfaceRegistryView view;
        auto scope = [](std::initializer_list<const char*> values) {
            TPolicyScopePath path{TPolicyScope::component};
            for (const char* value : values) path.Push(value);
            return path;
        };
        auto add = [&](std::string id, TCommunicationContextPolicySurfaceKind kind, std::initializer_list<const char*> path, bool realization) {
            auto descriptor = TCommunicationContextPolicySurfaceDescriptor::Make(std::move(id), kind, scope(path), realization);
            view.Add(TCommunicationContextPolicySurfaceCapabilityProfile::MakeDefault(std::move(descriptor)));
        };
        add("comm_channel_topology", TCommunicationContextPolicySurfaceKind::channel_topology, {"system", "communication_context", "channels"}, false);
        add("comm_binding_declaration", TCommunicationContextPolicySurfaceKind::binding_declaration, {"system", "communication_context", "bindings"}, false);
        add("comm_compatibility_evaluator", TCommunicationContextPolicySurfaceKind::compatibility_evaluator, {"system", "communication_context", "compatibility"}, false);
        add("comm_session_lifecycle", TCommunicationContextPolicySurfaceKind::session_lifecycle, {"system", "communication_context", "sessions"}, false);
        add("comm_bridge_protocol", TCommunicationContextPolicySurfaceKind::bridge_protocol_model, {"system", "communication_context", "protocols"}, true);
        add("comm_bridge_core", TCommunicationContextPolicySurfaceKind::bridge_core, {"system", "communication_context", "bridge_core"}, true);
        add("comm_diagnostics", TCommunicationContextPolicySurfaceKind::diagnostics, {"system", "communication_context", "diagnostics"}, false);
        add("comm_optional_registry", TCommunicationContextPolicySurfaceKind::optional_registry, {"system", "communication_context", "registries"}, false);
        add("comm_plugin_adapter_boundary", TCommunicationContextPolicySurfaceKind::plugin_adapter_boundary, {"system", "communication_context", "plugin_adapter_boundary"}, true);
        add("comm_outbound_port_boundary", TCommunicationContextPolicySurfaceKind::outbound_port_boundary, {"system", "communication_context", "outbound_port_boundary"}, true);
        return view;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
