#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyObservationId.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyObservationId is the primitive identity token for observation records produced around a policy object. It lets audit, trace, and evidence structures refer to one observation without depending on TPolicy, graph traversal, assignment, registry, or telemetry infrastructure.
 *
 * Why this file exists in W05:
 *   Observation/audit semantics are mandatory structurally in the Policy Object model, but they must remain separate from lifecycle state. W05 starts by giving observation records their own identity token.
 *
 * Relationship to previous waves:
 *   - W01 provides TPolicyId; observation identifiers may be correlated with policy identifiers without replacing them.
 *   - W02 clauses may later be observed, but this file does not inspect clause content.
 *   - W03 replacement structures may later emit observations, but this file does not decide replacement eligibility.
 *   - W04 lifecycle structures may later be observed, but observation identity is not lifecycle state.
 *
 * Relationship to future waves:
 *   - W06 realization binding may emit realization-related observations, but this identifier remains mechanism-neutral.
 *   - W07 policy graph may include observation/audit nodes that refer to observation identifiers.
 *   - W09 TPolicy may aggregate observation views, not become an audit log implementation.
 *
 * Explicit non-responsibilities:
 *   TPolicyObservationId is not TPolicyId, not a lifecycle marker, not an audit trail, not telemetry identity, not a database key, and not a runtime event bus topic.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

struct TPolicyObservationId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyObservationId() noexcept = default;
    explicit constexpr TPolicyObservationId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyObservationId Invalid() noexcept { return TPolicyObservationId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyObservationId lhs, TPolicyObservationId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyObservationId lhs, TPolicyObservationId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyObservationId lhs, TPolicyObservationId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
