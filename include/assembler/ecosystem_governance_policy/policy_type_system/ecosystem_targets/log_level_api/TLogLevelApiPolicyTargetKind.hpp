#pragma once

#include <cstdint>


namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TLogLevelApiPolicyTargetKind.hpp

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
 *   TLogLevelApiPolicyTargetKind names the log_level_api-local target categories that may be described to ecosystem governance. It is not a pointer to a concrete API object and not a callable target surface.
 */

enum class TLogLevelApiPolicyTargetKind : std::uint8_t
{
    unknown = 0,
    api_facade = 1,
    content_validator = 2,
    metadata_injector = 3,
    timestamp_stabilizer = 4,
    envelope_assembler = 5,
    envelope_output_boundary = 6,
    policy_assignment_boundary = 7,
    custom = 255
};

[[nodiscard]] constexpr bool IsKnownLogLevelApiPolicyTargetKind(TLogLevelApiPolicyTargetKind kind) noexcept
{
    return kind != TLogLevelApiPolicyTargetKind::unknown;
}

[[nodiscard]] constexpr bool IsPreparationTarget(TLogLevelApiPolicyTargetKind kind) noexcept
{
    return kind == TLogLevelApiPolicyTargetKind::content_validator ||
           kind == TLogLevelApiPolicyTargetKind::metadata_injector ||
           kind == TLogLevelApiPolicyTargetKind::timestamp_stabilizer ||
           kind == TLogLevelApiPolicyTargetKind::envelope_assembler;
}

[[nodiscard]] constexpr bool IsBoundaryTarget(TLogLevelApiPolicyTargetKind kind) noexcept
{
    return kind == TLogLevelApiPolicyTargetKind::api_facade ||
           kind == TLogLevelApiPolicyTargetKind::envelope_output_boundary ||
           kind == TLogLevelApiPolicyTargetKind::policy_assignment_boundary;
}


} // namespace assembler::ecosystem_governance::policy_type_system
