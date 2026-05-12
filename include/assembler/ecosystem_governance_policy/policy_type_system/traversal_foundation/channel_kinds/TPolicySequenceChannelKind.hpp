#pragma once

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySequenceChannelKind.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: channel_kinds
 *
 * Full architectural responsibility:
 *   TPolicySequenceChannelKind classifies the constitutional traversal shape of a sequence channel. It distinguishes linear and ring sequence channels without defining how a runtime algorithm progresses through them.
 *
 * Why this file exists in W08:
 *   W08 must preserve the distinction between non-cyclic linear constitution and cyclic ring constitution as foundational traversal vocabulary. The distinction is structural and semantic, not an execution loop.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicySequenceChannel carries this kind. Cursor logic may later interpret position differently for linear and ring channels, but this enum does not perform that interpretation.
 *
 * Relationship to future waves:
 *   Future traversal orchestration may use channel kind to decide legal path behavior. W09 TPolicy may expose the kind through safe views.
 *
 * Explicit non-responsibilities:
 *   This enum is not a runtime traversal state, not a graph edge kind, not a scheduling mode, not a loop executor, and not a branch-selection algorithm.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
enum class TPolicySequenceChannelKind
{
    unknown = 0,
    linear = 1,
    ring = 2
};

[[nodiscard]] constexpr bool IsKnownPolicySequenceChannelKind(TPolicySequenceChannelKind kind) noexcept
{
    return kind != TPolicySequenceChannelKind::unknown;
}

[[nodiscard]] constexpr bool IsLinearPolicySequenceChannelKind(TPolicySequenceChannelKind kind) noexcept
{
    return kind == TPolicySequenceChannelKind::linear;
}

[[nodiscard]] constexpr bool IsRingPolicySequenceChannelKind(TPolicySequenceChannelKind kind) noexcept
{
    return kind == TPolicySequenceChannelKind::ring;
}

} // namespace assembler::ecosystem_governance::policy_type_system
