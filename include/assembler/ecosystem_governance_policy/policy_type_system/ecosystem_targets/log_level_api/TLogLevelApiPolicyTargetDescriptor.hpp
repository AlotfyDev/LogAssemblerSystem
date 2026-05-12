#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"


namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TLogLevelApiPolicyTargetDescriptor.hpp

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
 *   TLogLevelApiPolicyTargetDescriptor describes one log_level_api target category as an ecosystem governance target. It stores identity, local target kind, coarse ecosystem target kind, scope path, and non-executing flags without owning or invoking the Log Level API.
 */

struct TLogLevelApiPolicyTargetDescriptor final
{
    std::uint64_t target_id{0};
    TLogLevelApiPolicyTargetKind local_kind{TLogLevelApiPolicyTargetKind::unknown};
    TPolicyTargetKind ecosystem_target_kind{TPolicyTargetKind::log_level_api_component};
    TPolicyScopePath scope_path{};
    std::string canonical_name{};
    std::string owning_domain{"log_level_api"};
    bool hot_path_sensitive{false};
    bool accepts_assignment{true};
    bool realization_deferred{true};

    [[nodiscard]] bool HasIdentity() const noexcept { return target_id != 0; }
    [[nodiscard]] bool HasName() const noexcept { return !canonical_name.empty(); }
    [[nodiscard]] bool IsKnownLocalKind() const noexcept { return IsKnownLogLevelApiPolicyTargetKind(local_kind); }
    [[nodiscard]] bool IsDescriptorOnly() const noexcept { return true; }

    [[nodiscard]] bool IsValid() const noexcept
    {
        return HasIdentity() &&
               HasName() &&
               IsKnownLocalKind() &&
               IsKnown(ecosystem_target_kind) &&
               scope_path.IsSpecified();
    }

    [[nodiscard]] static TLogLevelApiPolicyTargetDescriptor Make(
        std::uint64_t id,
        TLogLevelApiPolicyTargetKind kind,
        std::string name,
        TPolicyScope scope = TPolicyScope::component)
    {
        TLogLevelApiPolicyTargetDescriptor descriptor{};
        descriptor.target_id = id;
        descriptor.local_kind = kind;
        descriptor.canonical_name = std::move(name);
        descriptor.scope_path = TPolicyScopePath{scope, {"system", "log_level_api", descriptor.canonical_name}};
        descriptor.hot_path_sensitive = kind == TLogLevelApiPolicyTargetKind::api_facade ||
                                        kind == TLogLevelApiPolicyTargetKind::envelope_output_boundary;
        return descriptor;
    }
};


} // namespace assembler::ecosystem_governance::policy_type_system
