#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyId.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyId is the primitive identity token for a concrete policy object.
 *   It exists so that later policy layers can refer to a policy without
 *   depending on the full TPolicy aggregate, policy graph, assignment record,
 *   registry entry, realization binding, or traversal foundation.
 *
 * Why this file exists in W01:
 *   The Policy Object taxonomy requires every policy object to carry identity
 *   semantics. Identity supports traceability, replacement discipline,
 *   governance linkage, and auditability. This file provides the smallest
 *   stable identity building block needed before clauses, safe points,
 *   lifecycle, realization binding, graph structure, traversal types,
 *   TPolicy aggregate, assignment, or registry can be introduced.
 *
 * Relationship to other files in this wave:
 *   - TPolicyFamilyId identifies the semantic family of policies to which a
 *     policy belongs.
 *   - TPolicyVersion describes version identity and ordering hints.
 *   - TPolicyScope describes the authority or applicability boundary of a
 *     policy.
 *   - TPolicySource and TPolicyProvenance describe origin and trace context.
 *   - TPolicyStatus, TPolicyIssue, and TPolicyResult provide primitive status
 *     and result carriers for identity-layer operations.
 *
 * Relationship to future waves:
 *   - W02 clauses may reference TPolicyId for ownership and diagnostics.
 *   - W03 replacement structures may use TPolicyId to identify replacement
 *     subjects.
 *   - W04 lifecycle snapshots may be keyed by TPolicyId.
 *   - W05 observation records may include TPolicyId for auditability.
 *   - W06 realization binding may reference TPolicyId but must not execute it.
 *   - W07 graph root nodes may carry or point to TPolicyId.
 *   - W09 TPolicy will compose this primitive rather than replace it.
 *
 * Explicit non-responsibilities:
 *   TPolicyId is not a policy object, not a policy graph node, not a registry
 *   entry, not an assignment, not a realization mechanism, and not a target
 *   object reference. It carries identity only.
 *
 * Current implementation note:
 *   W01 intentionally uses a small numeric value object. Later waves may add
 *   richer generation, namespace, or source-backed identity forms without
 *   changing the semantic role of this file.
 */
struct TPolicyId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyId() noexcept = default;
    explicit constexpr TPolicyId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyId Invalid() noexcept { return TPolicyId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyId lhs, TPolicyId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyId lhs, TPolicyId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyId lhs, TPolicyId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
