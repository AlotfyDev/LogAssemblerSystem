#pragma once

namespace assembler::ecosystem_governance::policy_type_system::target_realization
{
/*
 * Wave: EG-POL-W36_Target_Realization_Map_And_Capability_Declaration
 * Domain: ecosystem_governance / policy_type_system / target_realization
 * File: TPolicyTargetRealizationCapabilityKind.hpp
 *
 * Architectural role:
 *   This header classifies target-side realization capabilities such as readiness probes, lifecycle gates, replacement gates, and audit markers. It does not define callable methods.
 *
 * Relationship to prior waves and ARCH-009:
 *   W35 delivers governance semantic bundles as DTOs. W36 starts the target-side half of ARCH-009 by describing what the target declares it can realize and how governance semantics are mapped to target-owned capabilities. It builds on W13 target capability contracts, W14 compatibility rules, W18 realization contracts, and W21-W24 realization skeletons, while staying before completed policy object creation and host assignment.
 *
 * Full intended picture:
 *   A policy-aware domain object will eventually declare capabilities, bind governance semantic parts to target realization mappings, and produce a target-side declaration report. Later waves will use these declarations to create a completed policy object, then assign it through a TPolicyObjectHost at a safe point.
 *
 * Explicit non-responsibilities:
 *   This file does not create a completed policy object, assign a policy to a host, switch policies at a safe point, invoke target behavior, mutate target state, or perform runtime execution. 
 */

enum class TPolicyTargetRealizationCapabilityKind
{
    unknown = 0,
    read_only_observation,
    controlled_configuration,
    lifecycle_gate,
    replacement_gate,
    readiness_probe,
    failure_report,
    audit_marker,
    trace_marker,
    forbidden_runtime_mutation
};

[[nodiscard]] constexpr bool may_mutate_target(TPolicyTargetRealizationCapabilityKind kind) noexcept
{
    return kind == TPolicyTargetRealizationCapabilityKind::controlled_configuration ||
           kind == TPolicyTargetRealizationCapabilityKind::lifecycle_gate ||
           kind == TPolicyTargetRealizationCapabilityKind::replacement_gate;
}
}
