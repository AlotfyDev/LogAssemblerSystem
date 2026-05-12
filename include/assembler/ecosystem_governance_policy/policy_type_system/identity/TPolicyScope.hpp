#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyScope.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyScope describes the intended governance boundary of a policy. It is
 *   part of identity because a policy is not fully recognizable by id, family,
 *   and version alone; it must also be understood in relation to the kind of
 *   system boundary or component context it is meant to govern.
 *
 * Why this file exists in W01:
 *   The Policy Object taxonomy names scope awareness as part of minimum policy
 *   identity. Scope helps later waves prevent category collapse, such as using
 *   a dispatcher policy as a slot lifecycle policy, or applying a circulation
 *   policy to a target family for which it was not intended.
 *
 * Relationship to other files:
 *   - TPolicyFamilyId identifies the semantic family.
 *   - TPolicyScope identifies the intended authority boundary.
 *   - TPolicySource and TPolicyProvenance can explain where a scoped policy
 *     came from.
 *   - TPolicyStatus may mark a scope as unspecified or custom.
 *
 * Relationship to future waves:
 *   - Clause validation may depend on scope.
 *   - Replacement eligibility may require scope compatibility.
 *   - Realization binding may compare scope with target-kind descriptors.
 *   - Assignment may require scope compatibility with the assigned consumer.
 *
 * Explicit non-responsibilities:
 *   TPolicyScope is not an applicability engine, not a runtime target instance,
 *   not a communication binding, and not a material circulation component id.
 *   It only describes the policy's intended governance scope.
 *
 * Current implementation note:
 *   W01 provides a conservative enum. Later waves may add scoped identifiers,
 *   hierarchical scope descriptors, or domain-specific scope maps.
 */
enum class TPolicyScope : std::uint8_t
{
    unspecified = 0,
    global_governance = 1,
    domain = 2,
    component = 3,
    mechanism = 4,
    instance = 5,
    boundary = 6,
    custom = 255
};

[[nodiscard]] constexpr bool IsSpecified(TPolicyScope scope) noexcept
{
    return scope != TPolicyScope::unspecified;
}

} // namespace assembler::ecosystem_governance::policy_type_system
