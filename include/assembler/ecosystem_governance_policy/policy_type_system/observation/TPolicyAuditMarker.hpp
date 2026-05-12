#pragma once

#include <cstdint>
#include "TPolicyObservationId.hpp"
#include "TPolicyObservationKind.hpp"
#include "TPolicyTraceRef.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAuditMarker.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyAuditMarker is the small audit-facing marker that binds an observation identity, policy identity, observation kind, and optional trace reference into one reviewable marker.
 *
 * Why this file exists in W05:
 *   W05 needs a lightweight audit marker to support review and traceability without creating a full audit trail database or external logging system.
 *
 * Relationship to previous waves:
 *   - W01 supplies TPolicyId for the policy subject.
 *   - W04 lifecycle can later produce audit markers, but this marker is not lifecycle state.
 *
 * Relationship to future waves:
 *   - W06 realization binding may produce audit markers for mechanism-binding changes.
 *   - W07 policy graph may use audit markers inside observation/audit substructure.
 *   - W09 TPolicy may expose recent or selected audit markers.
 *
 * Explicit non-responsibilities:
 *   TPolicyAuditMarker is not an audit trail collection, not a logging record, not an evidence repository, not a lifecycle transition, and not a policy execution result.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

struct TPolicyAuditMarker final
{
    TPolicyObservationId observation_id{};
    TPolicyId policy_id{};
    TPolicyObservationKind kind{TPolicyObservationKind::unknown};
    TPolicyTraceRef trace{};

    constexpr TPolicyAuditMarker() noexcept = default;
    constexpr TPolicyAuditMarker(TPolicyObservationId oid, TPolicyId pid, TPolicyObservationKind k, TPolicyTraceRef tr = {}) noexcept
        : observation_id(oid), policy_id(pid), kind(k), trace(tr) {}

    [[nodiscard]] constexpr bool IsComplete() const noexcept
    {
        return observation_id.IsValid() && policy_id.IsValid() && IsKnown(kind);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
