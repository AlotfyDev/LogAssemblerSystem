#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyTargetDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilitySet.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TAddonPolicyTargetCapabilityProfile.hpp
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
 *   TAddonPolicyTargetCapabilityProfile groups the capability set required for one add-on target descriptor. It enables compatibility checks but does not expose adapter methods or execute add-on behavior.
 */

struct TAddonPolicyTargetCapabilityProfile final
{
    TAddonPolicyTargetDescriptor descriptor{};
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
        return IsValid() && SatisfiesRequiredCapabilities();
    }

    [[nodiscard]] static TAddonPolicyTargetCapabilityProfile MakeDefault(TAddonPolicyTargetDescriptor descriptor)
    {
        TAddonPolicyTargetCapabilityProfile profile;
        profile.descriptor = std::move(descriptor);
        const auto target = profile.descriptor.global_kind;
        auto add = [&](TPolicyTargetCapabilityKind kind) {
            TPolicyTargetCapabilityDescriptor item;
            item.kind = kind;
            item.target_kind = target;
            item.capability_id = TPolicyTargetCapabilityId{static_cast<TPolicyTargetCapabilityId::value_type>(kind) + 3000u};
            item.strength = TPolicyTargetCapabilityStrength::required;
            item.mutability = TPolicyTargetCapabilityMutability::read_only;
            item.canonical_name = "addon_policy_target_capability";
            profile.capabilities.Add(item);
            profile.required_capabilities.push_back(kind);
        };

        add(TPolicyTargetCapabilityKind::accepts_policy_assignment);
        add(TPolicyTargetCapabilityKind::reports_lifecycle_state);
        add(TPolicyTargetCapabilityKind::supports_readiness_check);
        add(TPolicyTargetCapabilityKind::supports_policy_observation_record);
        add(TPolicyTargetCapabilityKind::supports_diagnostic_view);
        add(TPolicyTargetCapabilityKind::declares_target_kind);
        add(TPolicyTargetCapabilityKind::declares_capability_set);
        add(TPolicyTargetCapabilityKind::supports_compatibility_evaluation);
        if (profile.descriptor.RequiresFailureReporting())
        {
            add(TPolicyTargetCapabilityKind::supports_realization_failure_report);
            add(TPolicyTargetCapabilityKind::supports_incompatibility_report);
        }
        if (profile.descriptor.RequiresReplacementDiscipline())
        {
            add(TPolicyTargetCapabilityKind::has_safe_replacement_point);
            add(TPolicyTargetCapabilityKind::reports_replacement_eligibility);
        }
        if (profile.descriptor.realization_capable)
        {
            add(TPolicyTargetCapabilityKind::supports_policy_realization_surface);
            add(TPolicyTargetCapabilityKind::supports_realization_result);
            add(TPolicyTargetCapabilityKind::supports_realization_trace);
        }
        return profile;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
