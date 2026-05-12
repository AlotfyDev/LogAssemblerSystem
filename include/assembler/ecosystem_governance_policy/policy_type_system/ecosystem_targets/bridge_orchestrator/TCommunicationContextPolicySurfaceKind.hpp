#pragma once

#include <cstdint>

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
 *   TCommunicationContextPolicySurfaceKind names the Communication Context
 *   policy-governable surface categories. It is local taxonomy only. It is not
 *   a Channel object, not a Binding object, not a Session object, not a Bridge,
 *   not a runtime endpoint, and not an invocation surface.
 */
enum class TCommunicationContextPolicySurfaceKind : std::uint8_t
{
    unknown = 0,
    channel_topology = 1,
    binding_declaration = 2,
    compatibility_evaluator = 3,
    session_lifecycle = 4,
    bridge_protocol_model = 5,
    bridge_core = 6,
    diagnostics = 7,
    optional_registry = 8,
    plugin_adapter_boundary = 9,
    outbound_port_boundary = 10,
    policy_assignment_boundary = 11,
    custom = 255
};

[[nodiscard]] constexpr bool IsKnownCommunicationContextPolicySurfaceKind(TCommunicationContextPolicySurfaceKind kind) noexcept
{
    return kind != TCommunicationContextPolicySurfaceKind::unknown;
}

[[nodiscard]] constexpr bool IsCommunicationLifecycleSurface(TCommunicationContextPolicySurfaceKind kind) noexcept
{
    return kind == TCommunicationContextPolicySurfaceKind::session_lifecycle ||
           kind == TCommunicationContextPolicySurfaceKind::bridge_protocol_model ||
           kind == TCommunicationContextPolicySurfaceKind::bridge_core;
}

[[nodiscard]] constexpr bool IsCommunicationBoundarySurface(TCommunicationContextPolicySurfaceKind kind) noexcept
{
    return kind == TCommunicationContextPolicySurfaceKind::plugin_adapter_boundary ||
           kind == TCommunicationContextPolicySurfaceKind::outbound_port_boundary ||
           kind == TCommunicationContextPolicySurfaceKind::policy_assignment_boundary;
}

[[nodiscard]] constexpr bool IsCommunicationGovernanceSurface(TCommunicationContextPolicySurfaceKind kind) noexcept
{
    return kind == TCommunicationContextPolicySurfaceKind::channel_topology ||
           kind == TCommunicationContextPolicySurfaceKind::binding_declaration ||
           kind == TCommunicationContextPolicySurfaceKind::compatibility_evaluator ||
           kind == TCommunicationContextPolicySurfaceKind::diagnostics ||
           kind == TCommunicationContextPolicySurfaceKind::optional_registry;
}

[[nodiscard]] constexpr bool IsReplacementSensitiveCommunicationSurface(TCommunicationContextPolicySurfaceKind kind) noexcept
{
    return IsCommunicationLifecycleSurface(kind) ||
           kind == TCommunicationContextPolicySurfaceKind::binding_declaration ||
           kind == TCommunicationContextPolicySurfaceKind::plugin_adapter_boundary ||
           kind == TCommunicationContextPolicySurfaceKind::outbound_port_boundary;
}

} // namespace assembler::ecosystem_governance::policy_type_system
