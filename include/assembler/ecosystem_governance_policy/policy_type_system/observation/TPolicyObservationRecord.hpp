#pragma once

#include <cstdint>
#include "TPolicyObservationId.hpp"
#include "TPolicyObservationKind.hpp"
#include "TPolicyEvidenceRef.hpp"
#include "TPolicyTraceRef.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleState.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyObservationRecord.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyObservationRecord is the primary lightweight observation carrier. It records reviewable facts about policy-related activity while remaining separate from lifecycle state, policy execution, telemetry export, and registry persistence.
 *
 * Why this file exists in W05:
 *   The Policy Object model requires observation/audit capability. W05 implements that capability as compact records that can refer to policy identity, lifecycle state, evidence, and trace context without becoming the lifecycle layer or a logging framework.
 *
 * Relationship to previous waves:
 *   - W01 supplies TPolicyId for the observed policy subject.
 *   - W04 supplies TPolicyLifecycleState when an observation is lifecycle-related, while lifecycle state remains separately owned.
 *
 * Relationship to future waves:
 *   - W06 realization binding may create observation records for descriptive binding events.
 *   - W07 policy graph may include observation/audit-bearing nodes.
 *   - W09 TPolicy may aggregate or expose observation records through views.
 *
 * Explicit non-responsibilities:
 *   TPolicyObservationRecord is not TPolicy, not TPolicyLifecycleSnapshot, not telemetry, not database audit storage, not a runtime event, not an execution result, and not proof of target behavior.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

struct TPolicyObservationRecord final
{
    TPolicyObservationId observation_id{};
    TPolicyId policy_id{};
    TPolicyObservationKind kind{TPolicyObservationKind::unknown};
    TPolicyLifecycleState lifecycle_state{TPolicyLifecycleState::unknown};
    TPolicyEvidenceRef evidence{};
    TPolicyTraceRef trace{};
    std::uint32_t note_code{0};

    constexpr TPolicyObservationRecord() noexcept = default;

    constexpr TPolicyObservationRecord(
        TPolicyObservationId oid,
        TPolicyId pid,
        TPolicyObservationKind k,
        TPolicyLifecycleState state = TPolicyLifecycleState::unknown,
        TPolicyEvidenceRef ev = {},
        TPolicyTraceRef tr = {},
        std::uint32_t note = 0) noexcept
        : observation_id(oid), policy_id(pid), kind(k), lifecycle_state(state), evidence(ev), trace(tr), note_code(note) {}

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return observation_id.IsValid() && policy_id.IsValid() && IsKnown(kind);
    }

    [[nodiscard]] constexpr bool HasEvidence() const noexcept { return evidence.IsPresent(); }
    [[nodiscard]] constexpr bool HasTrace() const noexcept { return trace.IsPresent(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
