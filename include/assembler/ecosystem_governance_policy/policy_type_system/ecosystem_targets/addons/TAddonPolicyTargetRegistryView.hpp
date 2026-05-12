#pragma once

#include <algorithm>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyTargetCapabilityProfile.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TAddonPolicyTargetRegistryView.hpp
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
 *   TAddonPolicyTargetRegistryView is an in-memory view of W28 add-on target descriptors and capability profiles. It is not the policy registry, add-on registry, service locator, target locator, or persistence layer.
 */

struct TAddonPolicyTargetRegistryView final
{
    std::vector<TAddonPolicyTargetCapabilityProfile> targets{};

    void Add(TAddonPolicyTargetCapabilityProfile profile)
    {
        if (!profile.descriptor.IsValid()) return;
        auto it = std::find_if(targets.begin(), targets.end(), [&](const auto& item) {
            return item.descriptor.target_id == profile.descriptor.target_id;
        });
        if (it == targets.end()) targets.push_back(std::move(profile));
        else *it = std::move(profile);
    }

    [[nodiscard]] const TAddonPolicyTargetCapabilityProfile* Find(TAddonPolicyTargetKind kind) const noexcept
    {
        auto it = std::find_if(targets.begin(), targets.end(), [&](const auto& item) {
            return item.descriptor.local_kind == kind;
        });
        return it == targets.end() ? nullptr : &(*it);
    }

    [[nodiscard]] bool Has(TAddonPolicyTargetKind kind) const noexcept
    {
        return Find(kind) != nullptr;
    }

    [[nodiscard]] bool IsCompleteForCoreAddonTargets() const noexcept
    {
        return Has(TAddonPolicyTargetKind::database_adapter) &&
               Has(TAddonPolicyTargetKind::thin_c_abi_adapter) &&
               Has(TAddonPolicyTargetKind::open_telemetry_adapter) &&
               Has(TAddonPolicyTargetKind::file_sink_adapter) &&
               Has(TAddonPolicyTargetKind::diagnostic_sink_adapter) &&
               Has(TAddonPolicyTargetKind::foreign_runtime_adapter);
    }

    [[nodiscard]] static TAddonPolicyTargetRegistryView Default()
    {
        TAddonPolicyTargetRegistryView view;
        auto scope = [](std::initializer_list<const char*> values) {
            TPolicyScopePath path{TPolicyScope::component};
            for (const char* value : values) path.Push(value);
            return path;
        };
        auto add = [&](std::string id, TAddonPolicyTargetKind kind, std::initializer_list<const char*> path, bool realization) {
            auto descriptor = TAddonPolicyTargetDescriptor::Make(std::move(id), kind, scope(path), realization);
            view.Add(TAddonPolicyTargetCapabilityProfile::MakeDefault(std::move(descriptor)));
        };
        add("addon_database_adapter", TAddonPolicyTargetKind::database_adapter, {"system", "addons", "database_adapter"}, true);
        add("addon_thin_c_abi_adapter", TAddonPolicyTargetKind::thin_c_abi_adapter, {"system", "addons", "thin_c_abi_adapter"}, true);
        add("addon_open_telemetry_adapter", TAddonPolicyTargetKind::open_telemetry_adapter, {"system", "addons", "open_telemetry_adapter"}, true);
        add("addon_file_sink_adapter", TAddonPolicyTargetKind::file_sink_adapter, {"system", "addons", "file_sink_adapter"}, true);
        add("addon_diagnostic_sink_adapter", TAddonPolicyTargetKind::diagnostic_sink_adapter, {"system", "addons", "diagnostic_sink_adapter"}, false);
        add("addon_foreign_runtime_adapter", TAddonPolicyTargetKind::foreign_runtime_adapter, {"system", "addons", "foreign_runtime_adapter"}, true);
        add("addon_receiver_adapter", TAddonPolicyTargetKind::receiver_adapter, {"system", "addons", "receiver_adapter"}, true);
        add("addon_projection_adapter", TAddonPolicyTargetKind::projection_adapter, {"system", "addons", "projection_adapter"}, true);
        add("addon_policy_assignment_boundary", TAddonPolicyTargetKind::policy_assignment_boundary, {"system", "addons", "policy_assignment_boundary"}, false);
        return view;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
