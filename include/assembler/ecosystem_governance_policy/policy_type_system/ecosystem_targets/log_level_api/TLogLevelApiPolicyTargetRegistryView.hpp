#pragma once

#include <algorithm>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyTargetCapabilityProfile.hpp"


namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TLogLevelApiPolicyTargetRegistryView.hpp

 * Wave: EG-POL-W25_LogLevelApi_Policy_Targets
 * Domain: ecosystem_governance / policy_type_system / ecosystem_targets / log_level_api
 *
 * Architectural boundary:
 *   W25 opens Phase E -- Ecosystem Integration by introducing policy-target
 *   descriptors for the Log Level API preparation domain. The wave maps
 *   governance-level policy vocabulary onto log-level API target categories
 *   such as validation, metadata injection, timestamp stabilization, envelope
 *   assembly, and API-facade admission. It is integration-facing but remains
 *   descriptive: it does not implement the Log Level API, validate content,
 *   inject metadata, stabilize timestamps, assemble envelopes, bind
 *   communication surfaces, assign policies, or realize policies.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and scope vocabulary.
 *   - W06 supplies descriptor-only target-kind language.
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
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-001 identifies preparation policy families such as validation,
 *   metadata injection, timestamp stabilization, and envelope assembly.
 *   EG-POL-ARCH-002 identifies preparation targets such as validator,
 *   metadata injector, timestamp stabilizer, envelope assembler, and API facade.
 *   EG-POL-ARCH-003 requires explicit compatibility between families and target
 *   capabilities before assignment or realization. W25 creates a conservative
 *   C++ integration skeleton for that log_level_api slice.
 *
 * Explicit non-responsibilities:
 *   This file does not implement log_level_api runtime behavior, content
 *   validation, envelope filling, metadata mutation, timestamp algorithms,
 *   policy assignment activation, authority roles, source publication,
 *   registry persistence, realization contracts, runtime execution,
 *   TPolicyExecutor, direct target invocation, material circulation,
 *   communication binding, add-on execution, telemetry, logging, or database
 *   persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete intended architectural responsibility
 *   while the code intentionally stays as compact value carriers and helpers
 *   for compile-smoke validation.
 * File responsibility:
 *   TLogLevelApiPolicyTargetRegistryView is a bounded in-memory view of log_level_api policy target descriptors and their capability profiles. It is not the global policy registry, not a target locator, and not a runtime handle to Log Level API components.
 */

struct TLogLevelApiPolicyTargetRegistryView final
{
    std::vector<TLogLevelApiPolicyTargetDescriptor> targets{};
    std::vector<TLogLevelApiPolicyTargetCapabilityProfile> profiles{};

    void AddTarget(TLogLevelApiPolicyTargetDescriptor descriptor)
    {
        if (!descriptor.IsValid()) return;
        auto existing = std::find_if(targets.begin(), targets.end(), [&](const auto& current) {
            return current.target_id == descriptor.target_id;
        });
        if (existing == targets.end()) targets.push_back(descriptor);
        else *existing = descriptor;

        auto profile_existing = std::find_if(profiles.begin(), profiles.end(), [&](const auto& current) {
            return current.target.target_id == descriptor.target_id;
        });
        auto profile = TLogLevelApiPolicyTargetCapabilityProfile::DefaultFor(std::move(descriptor));
        if (profile_existing == profiles.end()) profiles.push_back(std::move(profile));
        else *profile_existing = std::move(profile);
    }

    [[nodiscard]] const TLogLevelApiPolicyTargetDescriptor* Find(TLogLevelApiPolicyTargetKind kind) const noexcept
    {
        auto it = std::find_if(targets.begin(), targets.end(), [&](const auto& target) { return target.local_kind == kind; });
        return it == targets.end() ? nullptr : &(*it);
    }

    [[nodiscard]] const TLogLevelApiPolicyTargetCapabilityProfile* FindProfile(TLogLevelApiPolicyTargetKind kind) const noexcept
    {
        auto it = std::find_if(profiles.begin(), profiles.end(), [&](const auto& profile) { return profile.target.local_kind == kind; });
        return it == profiles.end() ? nullptr : &(*it);
    }

    [[nodiscard]] bool Has(TLogLevelApiPolicyTargetKind kind) const noexcept { return Find(kind) != nullptr; }
    [[nodiscard]] bool IsCompleteForDefaultPreparationTargets() const noexcept
    {
        return Has(TLogLevelApiPolicyTargetKind::api_facade) &&
               Has(TLogLevelApiPolicyTargetKind::content_validator) &&
               Has(TLogLevelApiPolicyTargetKind::metadata_injector) &&
               Has(TLogLevelApiPolicyTargetKind::timestamp_stabilizer) &&
               Has(TLogLevelApiPolicyTargetKind::envelope_assembler) &&
               Has(TLogLevelApiPolicyTargetKind::envelope_output_boundary);
    }

    [[nodiscard]] static TLogLevelApiPolicyTargetRegistryView Default()
    {
        TLogLevelApiPolicyTargetRegistryView view{};
        view.AddTarget(TLogLevelApiPolicyTargetDescriptor::Make(2501, TLogLevelApiPolicyTargetKind::api_facade, "api_facade", TPolicyScope::boundary));
        view.AddTarget(TLogLevelApiPolicyTargetDescriptor::Make(2502, TLogLevelApiPolicyTargetKind::content_validator, "validator"));
        view.AddTarget(TLogLevelApiPolicyTargetDescriptor::Make(2503, TLogLevelApiPolicyTargetKind::metadata_injector, "metadata_injector"));
        view.AddTarget(TLogLevelApiPolicyTargetDescriptor::Make(2504, TLogLevelApiPolicyTargetKind::timestamp_stabilizer, "timestamp_stabilizer"));
        view.AddTarget(TLogLevelApiPolicyTargetDescriptor::Make(2505, TLogLevelApiPolicyTargetKind::envelope_assembler, "envelope_assembler"));
        view.AddTarget(TLogLevelApiPolicyTargetDescriptor::Make(2506, TLogLevelApiPolicyTargetKind::envelope_output_boundary, "envelope_output_boundary", TPolicyScope::boundary));
        return view;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system
