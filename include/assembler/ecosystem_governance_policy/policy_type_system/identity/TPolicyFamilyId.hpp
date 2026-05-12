#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyId.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyFamilyId identifies the semantic family to which a policy belongs.
 *   A family groups policies that share a governing concern, such as dispatch,
 *   slot lifecycle, circulation moderation, replacement, traversal, or another
 *   future policy family. It is intentionally not the same as a concrete
 *   policy id.
 *
 * Why this file exists in W01:
 *   Policy identity is not only instance identity. The taxonomy requires family
 *   recognition as part of minimum identity semantics. Family recognition lets
 *   later waves validate that a clause set, safe-point structure, lifecycle
 *   shape, realization binding, or target-kind expectation belongs to the
 *   correct kind of policy.
 *
 * Relationship to other files:
 *   - TPolicyId identifies a policy instance or concrete policy object.
 *   - TPolicyVersion versions a member of a family.
 *   - TPolicyScope defines where the family member is intended to govern.
 *   - TPolicySource and TPolicyProvenance describe where the family member came
 *     from and how it is traceable.
 *
 * Relationship to future waves:
 *   - Clause families may use TPolicyFamilyId to restrict allowed clause kinds.
 *   - Replacement rules may vary by family.
 *   - Lifecycle richness may vary by family.
 *   - Realization binding may validate family-to-mechanism compatibility.
 *   - Registry lookup keys may include family identity.
 *
 * Explicit non-responsibilities:
 *   TPolicyFamilyId is not a type-erased policy object, not a C++ class family,
 *   not a runtime executor category, and not a registry namespace by itself.
 *   It is only a semantic family token.
 *
 * Current implementation note:
 *   W01 keeps this as a numeric token. Rich naming, string labels, or external
 *   catalog linkage can be layered later without changing the primitive role.
 */
struct TPolicyFamilyId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyFamilyId() noexcept = default;
    explicit constexpr TPolicyFamilyId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyFamilyId Invalid() noexcept { return TPolicyFamilyId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyFamilyId lhs, TPolicyFamilyId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyFamilyId lhs, TPolicyFamilyId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyFamilyId lhs, TPolicyFamilyId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
