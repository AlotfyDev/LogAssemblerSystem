#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySafePointId.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicySafePointId is the primitive identity token for a safe point inside
 *   the policy replacement model. A safe point is a structural replacement
 *   boundary or eligibility anchor in a policy object graph. It exists so that
 *   replacement decisions can refer to concrete replacement anchors without
 *   depending on the full TPolicy aggregate, policy graph, traversal layer, or
 *   runtime replacement engine.
 *
 * Why this file exists in W03:
 *   The Policy Object taxonomy makes safe replacement semantics foundational,
 *   and the graph-structure draft requires one or more Safe Point Nodes for a
 *   valid policy-object graph. W03 introduces the smallest identifier needed to
 *   name those anchors before lifecycle, observation, realization binding,
 *   policy graph, traversal foundation, or TPolicy aggregate exist.
 *
 * Relationship to other files in this wave:
 *   - TPolicySafePointKind classifies the safe point.
 *   - TPolicySafePoint carries this identifier and connects it to policy and
 *     optional clause identity.
 *   - TPolicyReplacementBoundary and TPolicyReplacementEligibility reference
 *     safe point identities when describing replacement discipline.
 *   - TPolicyReplacementPlan can name source and target safe points.
 *
 * Relationship to future waves:
 *   - W04 lifecycle may use safe point identities to describe lifecycle-safe
 *     replacement state.
 *   - W07 policy graph nodes may wrap safe point identities inside safe-point
 *     node structures.
 *   - W08 traversal foundation must not treat this identity as traversal
 *     cursor or channel identity.
 *   - W09 TPolicy will aggregate safe points rather than invent replacement
 *     identity directly.
 *
 * Explicit non-responsibilities:
 *   TPolicySafePointId is not a safe point object, not a lifecycle state, not a
 *   replacement algorithm, not a graph node by itself, and not a lock or
 *   synchronization primitive. It carries identity only.
 *
 * Current implementation note:
 *   W03 intentionally uses a small numeric value object. Later waves may add
 *   richer generation or graph-backed identity without changing this file's
 *   semantic role.
 */
struct TPolicySafePointId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicySafePointId() noexcept = default;
    explicit constexpr TPolicySafePointId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicySafePointId Invalid() noexcept { return TPolicySafePointId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicySafePointId lhs, TPolicySafePointId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicySafePointId lhs, TPolicySafePointId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicySafePointId lhs, TPolicySafePointId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
