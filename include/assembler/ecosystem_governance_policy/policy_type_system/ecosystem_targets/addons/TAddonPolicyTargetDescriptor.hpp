#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TAddonPolicyTargetDescriptor.hpp
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
 *   TAddonPolicyTargetDescriptor describes one add-on policy target in governance terms. It names a local add-on category, global policy target kind, and scope path without owning, locating, or invoking a concrete add-on adapter.
 */

struct TAddonPolicyTargetDescriptor final
{
    std::string target_id{};
    TAddonPolicyTargetKind local_kind{TAddonPolicyTargetKind::unknown};
    TPolicyTargetKind global_kind{TPolicyTargetKind::addon_adapter};
    TPolicyScopePath scope_path{};
    bool destination_facing{true};
    bool boundary_surface{false};
    bool failure_reporting_required{true};
    bool replacement_sensitive{false};
    bool realization_capable{true};
    bool observation_required{true};
    std::string note{};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return !target_id.empty() &&
               IsKnownAddonPolicyTargetKind(local_kind) &&
               IsKnown(global_kind) &&
               scope_path.IsSpecified();
    }

    [[nodiscard]] bool RequiresFailureReporting() const noexcept
    {
        return failure_reporting_required || RequiresAddonFailureReporting(local_kind);
    }

    [[nodiscard]] bool RequiresReplacementDiscipline() const noexcept
    {
        return replacement_sensitive || IsReplacementSensitiveAddonTarget(local_kind);
    }

    [[nodiscard]] static TAddonPolicyTargetDescriptor Make(
        std::string id,
        TAddonPolicyTargetKind kind,
        TPolicyScopePath scope,
        bool realization = true)
    {
        TAddonPolicyTargetDescriptor descriptor;
        descriptor.target_id = std::move(id);
        descriptor.local_kind = kind;
        descriptor.scope_path = std::move(scope);
        descriptor.realization_capable = realization;
        descriptor.destination_facing = IsDestinationFacingAddonTarget(kind);
        descriptor.boundary_surface = IsBoundaryAddonTarget(kind);
        descriptor.failure_reporting_required = RequiresAddonFailureReporting(kind);
        descriptor.replacement_sensitive = IsReplacementSensitiveAddonTarget(kind);
        return descriptor;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
