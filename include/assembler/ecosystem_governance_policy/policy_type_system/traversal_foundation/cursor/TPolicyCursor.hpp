#pragma once

#include <cstddef>
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/sequence_channels/TPolicySequenceChannelId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyCursor.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: cursor
 *
 * Full architectural responsibility:
 *   TPolicyCursor represents positional awareness inside a sequence channel. It records a channel identity, a zero-based slot position, and an optional cycle count for ring-aware future interpretation.
 *
 * Why this file exists in W08:
 *   Position/cursor awareness is a foundational seed because linear and ring channels differ in how continuation may later be interpreted. W08 records this vocabulary without defining runtime cursor advancement.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicySequenceChannel may expose cursor state. Slot cardinality constrains whether a cursor position is structurally plausible.
 *
 * Relationship to future waves:
 *   Future traversal orchestration may define cursor advancement, wrapping, and replay-safe semantics. W09 TPolicy can expose cursor views without executing traversal.
 *
 * Explicit non-responsibilities:
 *   TPolicyCursor is not an iterator over graph nodes, not a container cursor, not a scheduler tick, not a loop executor, and not a traversal algorithm.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyCursor final
{
    TPolicySequenceChannelId channel_id{};
    std::size_t position{0};
    std::size_t cycle_count{0};

    constexpr TPolicyCursor() noexcept = default;
    constexpr TPolicyCursor(TPolicySequenceChannelId channel, std::size_t pos, std::size_t cycles = 0) noexcept
        : channel_id(channel), position(pos), cycle_count(cycles) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return channel_id.IsValid(); }
    [[nodiscard]] constexpr bool IsAtStart() const noexcept { return position == 0; }
    [[nodiscard]] constexpr bool HasCycleAwareness() const noexcept { return cycle_count > 0; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
