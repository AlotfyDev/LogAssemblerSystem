#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyStatus.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyStatus provides the primitive status vocabulary used by the policy
 *   type system at the identity layer. It is intentionally not the full policy
 *   lifecycle model. Lifecycle will be defined later in its own wave.
 *
 * Why this file exists in W01:
 *   Primitive identity operations need a small status vocabulary for validation,
 *   construction, and result reporting. Without this file, early identity
 *   values would need ad hoc booleans or generic integers, which would weaken
 *   traceability and diagnostics.
 *
 * Relationship to other files:
 *   - TPolicyIssue uses status-like classification for identity-layer problems.
 *   - TPolicyResult returns a status for primitive operations.
 *   - Identity primitives can be checked and reported consistently using this
 *     status vocabulary.
 *
 * Relationship to future waves:
 *   - W04 lifecycle states must remain distinct from TPolicyStatus.
 *   - W09 TPolicy may expose both primitive status and lifecycle state, but
 *     they must not collapse into one concept.
 *
 * Explicit non-responsibilities:
 *   TPolicyStatus is not policy lifecycle, not active/suspended/retired state,
 *   not replacement state, not assignment state, not registry state, and not
 *   execution outcome. It is a primitive status vocabulary only.
 */
enum class TPolicyStatus : std::uint8_t
{
    unknown = 0,
    valid = 1,
    invalid = 2,
    incomplete = 3,
    unsupported = 4,
    conflict = 5
};

[[nodiscard]] constexpr bool IsSuccess(TPolicyStatus status) noexcept
{
    return status == TPolicyStatus::valid;
}

} // namespace assembler::ecosystem_governance::policy_type_system
