#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TAddonPolicyTargetKind.hpp
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
 *   TAddonPolicyTargetKind names the add-on-local policy-governable target categories. It is local taxonomy only. It is not an adapter instance, callback pointer, receiver handle, or invocation surface.
 */

enum class TAddonPolicyTargetKind : std::uint8_t
{
    unknown = 0,
    database_adapter = 1,
    thin_c_abi_adapter = 2,
    open_telemetry_adapter = 3,
    file_sink_adapter = 4,
    diagnostic_sink_adapter = 5,
    foreign_runtime_adapter = 6,
    receiver_adapter = 7,
    projection_adapter = 8,
    policy_assignment_boundary = 9,
    custom = 255
};

[[nodiscard]] constexpr bool IsKnownAddonPolicyTargetKind(TAddonPolicyTargetKind kind) noexcept
{
    return kind != TAddonPolicyTargetKind::unknown;
}

[[nodiscard]] constexpr bool IsDestinationFacingAddonTarget(TAddonPolicyTargetKind kind) noexcept
{
    return kind == TAddonPolicyTargetKind::database_adapter ||
           kind == TAddonPolicyTargetKind::open_telemetry_adapter ||
           kind == TAddonPolicyTargetKind::file_sink_adapter ||
           kind == TAddonPolicyTargetKind::diagnostic_sink_adapter ||
           kind == TAddonPolicyTargetKind::foreign_runtime_adapter ||
           kind == TAddonPolicyTargetKind::receiver_adapter ||
           kind == TAddonPolicyTargetKind::projection_adapter;
}

[[nodiscard]] constexpr bool IsBoundaryAddonTarget(TAddonPolicyTargetKind kind) noexcept
{
    return kind == TAddonPolicyTargetKind::thin_c_abi_adapter ||
           kind == TAddonPolicyTargetKind::policy_assignment_boundary;
}

[[nodiscard]] constexpr bool RequiresAddonFailureReporting(TAddonPolicyTargetKind kind) noexcept
{
    return IsDestinationFacingAddonTarget(kind) || kind == TAddonPolicyTargetKind::thin_c_abi_adapter;
}

[[nodiscard]] constexpr bool IsReplacementSensitiveAddonTarget(TAddonPolicyTargetKind kind) noexcept
{
    return kind == TAddonPolicyTargetKind::thin_c_abi_adapter ||
           kind == TAddonPolicyTargetKind::foreign_runtime_adapter ||
           kind == TAddonPolicyTargetKind::receiver_adapter;
}

} // namespace assembler::ecosystem_governance::policy_type_system
