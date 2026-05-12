#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyObservationKind.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyObservationKind classifies why an observation record exists without converting observation into telemetry, logging, lifecycle state, replacement execution, or target invocation.
 *
 * Why this file exists in W05:
 *   W05 needs a small controlled vocabulary for observation/audit records so evidence can be categorized without importing external logging or monitoring systems.
 *
 * Relationship to previous waves:
 *   - W01 identity primitives can be correlated with an observation kind.
 *   - W03 replacement may map to replacement-requested or replacement-committed observation kinds.
 *   - W04 lifecycle transitions may map to lifecycle-related observation kinds, while remaining distinct from lifecycle state.
 *
 * Relationship to future waves:
 *   - W06 realization binding may use realization_binding_note without executing a mechanism.
 *   - W07 graph observation/audit nodes may point to observation kinds.
 *   - W09 TPolicy may expose observation summaries derived from these kinds.
 *
 * Explicit non-responsibilities:
 *   TPolicyObservationKind is not TPolicyLifecycleState, not TPolicyStatus, not telemetry severity, not diagnostic severity, not an execution result, and not an audit storage schema.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

enum class TPolicyObservationKind : std::uint8_t
{
    unknown = 0,
    activation = 1,
    suspension = 2,
    retirement = 3,
    lifecycle_transition = 4,
    replacement_requested = 5,
    replacement_committed = 6,
    clause_evaluation_note = 7,
    applicability_note = 8,
    realization_binding_note = 9,
    evidence_link = 10,
    provenance_note = 11,
    operational_review = 12,
    authority_boundary_note = 13
};

[[nodiscard]] constexpr bool IsKnown(TPolicyObservationKind kind) noexcept
{
    return kind != TPolicyObservationKind::unknown;
}

[[nodiscard]] constexpr bool IsLifecycleRelated(TPolicyObservationKind kind) noexcept
{
    return kind == TPolicyObservationKind::activation ||
           kind == TPolicyObservationKind::suspension ||
           kind == TPolicyObservationKind::retirement ||
           kind == TPolicyObservationKind::lifecycle_transition;
}

[[nodiscard]] constexpr bool IsReplacementRelated(TPolicyObservationKind kind) noexcept
{
    return kind == TPolicyObservationKind::replacement_requested ||
           kind == TPolicyObservationKind::replacement_committed;
}

} // namespace assembler::ecosystem_governance::policy_type_system
