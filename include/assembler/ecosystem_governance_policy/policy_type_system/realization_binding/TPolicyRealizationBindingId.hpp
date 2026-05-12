#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationBindingId.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyRealizationBindingId is the primitive identity token for a descriptive
 *   realization binding. A realization binding connects a policy object to the
 *   realization mechanism family that may later enact that policy, while keeping
 *   the policy object separate from the mechanism and from the external target.
 *
 * Why this file exists in W06:
 *   The policy object taxonomy requires execution-policy families to carry
 *   realization-mechanism binding semantics. W06 introduces the identity layer
 *   for that binding without introducing a realizer, executor, callback, or
 *   target-owned object. The ID is needed before descriptors, views, graph nodes,
 *   and the later TPolicy aggregate can safely reference a binding.
 *
 * Relationship to previous waves:
 *   - W01 provides policy identity primitives that identify the policy subject.
 *   - W02 provides clauses whose content may later be realized by a mechanism.
 *   - W03 provides replacement discipline that may constrain binding changes.
 *   - W04 provides lifecycle state that may condition whether a binding is valid.
 *   - W05 provides observation/audit carriers that may record binding evidence.
 *
 * Relationship to other files in this wave:
 *   - TPolicyRealizationBinding uses this ID as its stable binding identity.
 *   - TPolicyRealizationDescriptor and TPolicyRealizationBindingView expose it
 *     without owning target execution.
 *
 * Relationship to future waves:
 *   - W07 policy graph may represent realization-binding structure as graph
 *     nodes anchored by this ID.
 *   - W09 TPolicy may aggregate or expose realization binding information.
 *   - W10 assignment may link a policy assignment to a binding descriptor.
 *
 * Explicit non-responsibilities:
 *   This ID is not a realization mechanism, not a target reference, not an
 *   executor handle, not a callback token, not a communication binding, and not
 *   proof that policy realization occurred.
 *
 * Current implementation note:
 *   W06 intentionally keeps binding identity as a compact numeric value object.
 *   Future waves may add richer namespacing or provenance without changing the
 *   semantic role of this file.
 */
struct TPolicyRealizationBindingId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyRealizationBindingId() noexcept = default;
    explicit constexpr TPolicyRealizationBindingId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyRealizationBindingId Invalid() noexcept { return TPolicyRealizationBindingId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyRealizationBindingId lhs, TPolicyRealizationBindingId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyRealizationBindingId lhs, TPolicyRealizationBindingId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyRealizationBindingId lhs, TPolicyRealizationBindingId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
