#pragma once

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyChannelReadiness.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: readiness
 *
 * Full architectural responsibility:
 *   TPolicyChannelReadiness classifies whether a sequence channel is currently structurally usable for traversal entry or progression. It is an admitted readiness seed, not a runtime scheduler.
 *
 * Why this file exists in W08:
 *   The traversal foundation must not assume every structurally existing channel is always eligible. W08 introduces readiness vocabulary so later orchestration can become gated without retrofitting the model.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicySequenceChannel may carry readiness. Transitions may consult readiness as data, but W08 does not execute the decision.
 *
 * Relationship to future waves:
 *   Future traversal orchestration may define activation rules for readiness. W09 TPolicy may expose readiness through a view.
 *
 * Explicit non-responsibilities:
 *   This enum is not lifecycle state, not policy status, not scheduler state, not replacement eligibility, not a concurrency primitive, and not a traversal algorithm.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
enum class TPolicyChannelReadiness
{
    unknown = 0,
    not_ready = 1,
    eligible = 2,
    ready = 3,
    blocked = 4,
    deferred = 5
};

[[nodiscard]] constexpr bool IsKnownPolicyChannelReadiness(TPolicyChannelReadiness readiness) noexcept
{
    return readiness != TPolicyChannelReadiness::unknown;
}

[[nodiscard]] constexpr bool AllowsPolicyChannelEntry(TPolicyChannelReadiness readiness) noexcept
{
    return readiness == TPolicyChannelReadiness::eligible || readiness == TPolicyChannelReadiness::ready;
}

[[nodiscard]] constexpr bool IsPolicyChannelBlocked(TPolicyChannelReadiness readiness) noexcept
{
    return readiness == TPolicyChannelReadiness::blocked || readiness == TPolicyChannelReadiness::deferred || readiness == TPolicyChannelReadiness::not_ready;
}

} // namespace assembler::ecosystem_governance::policy_type_system
