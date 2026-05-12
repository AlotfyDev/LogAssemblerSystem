#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySource.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicySource classifies the origin category from which a policy was
 *   supplied, derived, loaded, or declared. It supports provenance awareness
 *   without turning the policy type system into a policy registry, persistence
 *   layer, configuration loader, or external integration framework.
 *
 * Why this file exists in W01:
 *   The minimum identity semantics of a policy include source/provenance
 *   awareness. Source classification allows later audit, replacement, registry,
 *   and assignment decisions to distinguish default policies from configured,
 *   externally supplied, generated, or test policies.
 *
 * Relationship to other files:
 *   - TPolicyProvenance can carry more detailed origin trace data.
 *   - TPolicyVersion may be interpreted in relation to source kind.
 *   - TPolicyIssue may report missing or unsupported source classifications.
 *   - TPolicyResult may return source validation outcomes.
 *
 * Relationship to future waves:
 *   - Observation/audit records may include source kind.
 *   - Registry entries may store source descriptors.
 *   - Assignment checks may treat source kind as diagnostic or governance input.
 *
 * Explicit non-responsibilities:
 *   TPolicySource does not load policy files, query registries, parse JSON,
 *   read databases, connect to external services, or validate trust. It only
 *   records a source category.
 *
 * Current implementation note:
 *   W01 uses an enum to avoid introducing string ownership, allocators, or
 *   external catalog coupling at the primitive identity layer.
 */
enum class TPolicySource : std::uint8_t
{
    unspecified = 0,
    built_in = 1,
    configured = 2,
    policy_registry = 3,
    external_governance = 4,
    generated = 5,
    test = 6,
    custom = 255
};

[[nodiscard]] constexpr bool IsSpecified(TPolicySource source) noexcept
{
    return source != TPolicySource::unspecified;
}

} // namespace assembler::ecosystem_governance::policy_type_system
