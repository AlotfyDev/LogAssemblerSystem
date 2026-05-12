#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTargetCapabilityKind.hpp
 * Wave: EG-POL-W13_Target_Capability_Contracts
 * Domain: ecosystem_governance / policy_type_system / target_capability
 *
 * Architectural boundary:
 *   W13 implements the first target-capability contract layer derived from
 *   EG-POL-ARCH-002_Policy_Target_Kind_And_Capability_Model. It follows W12
 *   Policy Family And Scope and prepares W14 compatibility-matrix work. The
 *   wave is descriptive and non-executing: it describes target capabilities,
 *   capability sets, and compatibility reports without invoking targets or
 *   realizing policies.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and result vocabulary used by
 *     later policy layers.
 *   - W06 supplies TPolicyTargetKind and target-kind descriptors; W13 refines
 *     the capability side of that target model without changing W06's
 *     descriptor-only boundary.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not an executor.
 *   - W10 supplies non-executing assignment basics; W13 does not activate or
 *     run assignments.
 *   - W11 supplies registry basics; W13 does not become a registry.
 *   - W12 supplies family/scope descriptors that future compatibility waves
 *     will join with these capability descriptors.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-002 states that Target Kind is not Target Instance, Target
 *   Capability is not runtime execution, Capability Descriptor is not a C++
 *   method, and Realization Binding is not a realizer. This file preserves that
 *   doctrine. W13 provides the smallest C++ vocabulary required before the
 *   Policy Family Compatibility Matrix, assignment lifecycle implementation,
 *   realization contracts, runtime readiness, or TPolicyRealizer.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyRealizer, TPolicyExecutor, target
 *   invocation, target ownership, communication binding, material circulation
 *   behavior, add-on execution, telemetry, persistence, runtime scheduling, or
 *   policy execution.
 *
 * Current implementation posture:
 *   The current code is a conservative C++17 header-only foundation. The
 *   opening documentation describes the complete architectural responsibility,
 *   while the code intentionally remains a small set of value carriers and
 *   structural helpers.
 *
 * File responsibility:
 *   TPolicyTargetCapabilityKind enumerates the semantic categories of capabilities that a policy-consuming target kind may describe. It is classification vocabulary only; it is not a method table, invocation channel, interface, or target object.
 */
enum class TPolicyTargetCapabilityKind : std::uint8_t
{
    unknown = 0,

    accepts_policy_assignment = 1,
    reports_assignment_state = 2,
    supports_assignment_revocation = 3,
    supports_assignment_replacement = 4,
    supports_assignment_view = 5,

    reports_lifecycle_state = 10,
    supports_activation_gate = 11,
    supports_suspension_gate = 12,
    supports_retirement_gate = 13,
    supports_drain_state = 14,

    has_safe_replacement_point = 20,
    reports_replacement_eligibility = 21,
    supports_pending_replacement = 22,
    supports_replacement_rollback = 23,
    supports_replacement_observation = 24,

    supports_policy_realization_surface = 30,
    supports_readiness_check = 31,
    supports_realization_result = 32,
    supports_realization_failure_report = 33,
    supports_realization_trace = 34,

    supports_policy_observation_record = 40,
    supports_policy_audit_marker = 41,
    supports_diagnostic_view = 42,
    supports_evidence_ref = 43,
    supports_trace_ref = 44,

    declares_target_kind = 50,
    declares_capability_set = 51,
    supports_compatibility_evaluation = 52,
    supports_policy_family_filtering = 53,
    supports_incompatibility_report = 54,

    custom = 255
};

[[nodiscard]] constexpr bool IsKnownTargetCapabilityKind(TPolicyTargetCapabilityKind kind) noexcept
{
    return kind != TPolicyTargetCapabilityKind::unknown;
}

[[nodiscard]] constexpr bool IsRealizationRelatedCapability(TPolicyTargetCapabilityKind kind) noexcept
{
    return kind == TPolicyTargetCapabilityKind::supports_policy_realization_surface ||
           kind == TPolicyTargetCapabilityKind::supports_readiness_check ||
           kind == TPolicyTargetCapabilityKind::supports_realization_result ||
           kind == TPolicyTargetCapabilityKind::supports_realization_failure_report ||
           kind == TPolicyTargetCapabilityKind::supports_realization_trace;
}

[[nodiscard]] constexpr bool IsReplacementRelatedCapability(TPolicyTargetCapabilityKind kind) noexcept
{
    return kind == TPolicyTargetCapabilityKind::has_safe_replacement_point ||
           kind == TPolicyTargetCapabilityKind::reports_replacement_eligibility ||
           kind == TPolicyTargetCapabilityKind::supports_pending_replacement ||
           kind == TPolicyTargetCapabilityKind::supports_replacement_rollback ||
           kind == TPolicyTargetCapabilityKind::supports_replacement_observation;
}

} // namespace assembler::ecosystem_governance::policy_type_system
