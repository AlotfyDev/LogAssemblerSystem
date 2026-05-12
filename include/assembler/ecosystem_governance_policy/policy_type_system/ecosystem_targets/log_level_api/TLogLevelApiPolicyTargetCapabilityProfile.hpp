#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyTargetDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilitySet.hpp"


namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TLogLevelApiPolicyTargetCapabilityProfile.hpp

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
 *   TLogLevelApiPolicyTargetCapabilityProfile groups target-capability descriptors for a log_level_api target. It can build conservative default capability sets used by compatibility rules, but it does not expose or call Log Level API methods.
 */

struct TLogLevelApiPolicyTargetCapabilityProfile final
{
    TLogLevelApiPolicyTargetDescriptor target{};
    TPolicyTargetCapabilitySet capabilities{};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return target.IsValid() && !capabilities.IsEmpty();
    }

    [[nodiscard]] bool Supports(TPolicyTargetCapabilityKind kind) const noexcept
    {
        return capabilities.Contains(kind);
    }

    void AddCapability(
        TPolicyTargetCapabilityId id,
        TPolicyTargetCapabilityKind kind,
        TPolicyTargetCapabilityStrength strength,
        TPolicyTargetCapabilityMutability mutability,
        std::string name,
        std::string notes = {})
    {
        TPolicyTargetCapabilityDescriptor descriptor{};
        descriptor.capability_id = id;
        descriptor.kind = kind;
        descriptor.target_kind = target.ecosystem_target_kind;
        descriptor.strength = strength;
        descriptor.mutability = mutability;
        descriptor.canonical_name = std::move(name);
        descriptor.notes = std::move(notes);
        capabilities.Add(std::move(descriptor));
    }

    [[nodiscard]] static TLogLevelApiPolicyTargetCapabilityProfile DefaultFor(TLogLevelApiPolicyTargetDescriptor descriptor)
    {
        TLogLevelApiPolicyTargetCapabilityProfile profile{};
        profile.target = std::move(descriptor);
        const auto base = profile.target.target_id * 100;
        profile.AddCapability(TPolicyTargetCapabilityId{base + 1}, TPolicyTargetCapabilityKind::accepts_policy_assignment,
                              TPolicyTargetCapabilityStrength::required, TPolicyTargetCapabilityMutability::read_only,
                              "accepts_policy_assignment", "log_level_api target may accept assignment descriptors");
        profile.AddCapability(TPolicyTargetCapabilityId{base + 2}, TPolicyTargetCapabilityKind::supports_readiness_check,
                              TPolicyTargetCapabilityStrength::required, TPolicyTargetCapabilityMutability::read_only,
                              "supports_readiness_check", "target can be checked before future realization");
        profile.AddCapability(TPolicyTargetCapabilityId{base + 3}, TPolicyTargetCapabilityKind::reports_lifecycle_state,
                              TPolicyTargetCapabilityStrength::recommended, TPolicyTargetCapabilityMutability::read_only,
                              "reports_lifecycle_state", "target can report lifecycle-sensitive governance state");
        profile.AddCapability(TPolicyTargetCapabilityId{base + 4}, TPolicyTargetCapabilityKind::supports_policy_observation_record,
                              TPolicyTargetCapabilityStrength::recommended, TPolicyTargetCapabilityMutability::read_only,
                              "supports_policy_observation_record", "target may provide policy observation evidence");
        profile.AddCapability(TPolicyTargetCapabilityId{base + 5}, TPolicyTargetCapabilityKind::declares_target_kind,
                              TPolicyTargetCapabilityStrength::required, TPolicyTargetCapabilityMutability::read_only,
                              "declares_target_kind", "target describes its ecosystem target-kind classification");
        profile.AddCapability(TPolicyTargetCapabilityId{base + 6}, TPolicyTargetCapabilityKind::declares_capability_set,
                              TPolicyTargetCapabilityStrength::required, TPolicyTargetCapabilityMutability::read_only,
                              "declares_capability_set", "target exposes capability descriptors for compatibility checks");
        if (profile.target.local_kind == TLogLevelApiPolicyTargetKind::envelope_output_boundary)
        {
            profile.AddCapability(TPolicyTargetCapabilityId{base + 7}, TPolicyTargetCapabilityKind::supports_incompatibility_report,
                                  TPolicyTargetCapabilityStrength::recommended, TPolicyTargetCapabilityMutability::read_only,
                                  "supports_incompatibility_report", "boundary can report why output is not policy-compatible");
        }
        return profile;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system
