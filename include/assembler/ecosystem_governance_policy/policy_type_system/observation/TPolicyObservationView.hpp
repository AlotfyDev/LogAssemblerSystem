#pragma once

#include "TPolicyObservationRecord.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyObservationView.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyObservationView is the read-only public-facing projection of an observation record. It allows later policy aggregates and graph views to expose observation status safely without leaking mutable audit trail internals.
 *
 * Why this file exists in W05:
 *   W05 separates observation records from their views so later public surfaces can avoid exposing mutable internals or storage details.
 *
 * Relationship to previous waves:
 *   - W01 identity primitives appear in the view as identifiers only.
 *   - W04 lifecycle state may be reflected indirectly through observation kind and note code, but the view does not own lifecycle.
 *
 * Relationship to future waves:
 *   - W07 graph views may include observation views.
 *   - W09 TPolicyView may expose observation views as part of the policy aggregate surface.
 *
 * Explicit non-responsibilities:
 *   TPolicyObservationView is not a mutable record, not an audit trail, not evidence storage, not telemetry output, not a persistence DTO, and not a lifecycle view.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

struct TPolicyObservationView final
{
    TPolicyObservationId observation_id{};
    TPolicyId policy_id{};
    TPolicyObservationKind kind{TPolicyObservationKind::unknown};
    bool evidence_present{false};
    bool trace_present{false};
    std::uint32_t note_code{0};

    constexpr TPolicyObservationView() noexcept = default;

    [[nodiscard]] static constexpr TPolicyObservationView From(const TPolicyObservationRecord& record) noexcept
    {
        return TPolicyObservationView{
            record.observation_id,
            record.policy_id,
            record.kind,
            record.HasEvidence(),
            record.HasTrace(),
            record.note_code};
    }

    [[nodiscard]] constexpr bool IsPresent() const noexcept
    {
        return observation_id.IsValid() && policy_id.IsValid() && IsKnown(kind);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
