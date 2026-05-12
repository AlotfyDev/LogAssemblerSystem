#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyChannelSlotCardinality.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: slot_cardinality
 *
 * Full architectural responsibility:
 *   TPolicyChannelSlotCardinality describes the structural slot count of a sequence channel. It distinguishes single-slot and multi-slot channel constitution without promising runtime parallelism or execution concurrency.
 *
 * Why this file exists in W08:
 *   The traversal foundation admits both single-slot and multi-slot channels. Multi-slot support is required for future conjunction, split, merge, and composite forms, but W08 must not confuse multi-slot structure with parallel execution.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicySequenceChannel carries this value. Entry/exit surfaces, cursor awareness, and readiness may be interpreted with respect to the slot count, but this type owns only cardinality description.
 *
 * Relationship to future waves:
 *   Future orchestration can build richer semantics over this cardinality. W09 TPolicy can safely expose it as part of traversal foundation views.
 *
 * Explicit non-responsibilities:
 *   This type is not a container implementation, not a slot allocator, not a parallel runtime declaration, not a scheduler, and not a traversal algorithm.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyChannelSlotCardinality final
{
    using value_type = std::uint16_t;

    value_type slot_count{0};

    constexpr TPolicyChannelSlotCardinality() noexcept = default;
    explicit constexpr TPolicyChannelSlotCardinality(value_type count) noexcept : slot_count(count) {}

    [[nodiscard]] static constexpr TPolicyChannelSlotCardinality Single() noexcept { return TPolicyChannelSlotCardinality{1}; }
    [[nodiscard]] static constexpr TPolicyChannelSlotCardinality Multi(value_type count) noexcept { return TPolicyChannelSlotCardinality{count}; }

    [[nodiscard]] constexpr bool IsValid() const noexcept { return slot_count > 0; }
    [[nodiscard]] constexpr bool IsSingleSlot() const noexcept { return slot_count == 1; }
    [[nodiscard]] constexpr bool IsMultiSlot() const noexcept { return slot_count > 1; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
