#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySequenceChannelId.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: sequence_channels
 *
 * Full architectural responsibility:
 *   TPolicySequenceChannelId is the primitive identity token for a policy traversal sequence channel. It allows entry/exit surfaces, transitions, cursors, readiness records, and traversal views to refer to a channel without depending on a future traversal engine or policy aggregate.
 *
 * Why this file exists in W08:
 *   The traversal foundations define Sequence Channel as the smallest traversal-bearing unit. A stable channel id is needed before channel kinds, slot cardinality, entry/exit surfaces, transitions, relations, readiness, cursors, and traversal views can be connected safely.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicySequenceChannel uses this id as its identity. Entry/exit surfaces, transitions, readiness, and cursor types all refer to sequence channels through this id rather than owning full channel objects.
 *
 * Relationship to future waves:
 *   W09 TPolicy may expose traversal foundation views that include channel ids. Future traversal orchestration may use this id, but this file itself will remain a primitive identity carrier.
 *
 * Explicit non-responsibilities:
 *   TPolicySequenceChannelId is not a graph node id, not a traversal state, not a channel container, not a traversal algorithm, not a scheduler key, and not a runtime execution handle.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicySequenceChannelId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicySequenceChannelId() noexcept = default;
    explicit constexpr TPolicySequenceChannelId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicySequenceChannelId Invalid() noexcept { return TPolicySequenceChannelId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicySequenceChannelId lhs, TPolicySequenceChannelId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicySequenceChannelId lhs, TPolicySequenceChannelId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicySequenceChannelId lhs, TPolicySequenceChannelId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
