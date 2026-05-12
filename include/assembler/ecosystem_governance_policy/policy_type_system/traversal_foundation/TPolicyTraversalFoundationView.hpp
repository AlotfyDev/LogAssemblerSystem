#pragma once

#include <cstddef>
#include "sequence_channels/TPolicySequenceChannel.hpp"
#include "relations/TPolicyRelation.hpp"
#include "transitions/TPolicyTransition.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTraversalFoundationView.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: root
 *
 * Full architectural responsibility:
 *   TPolicyTraversalFoundationView is a read-only aggregate view over channels, relations, and transitions. It allows future TPolicy views and diagnostics to expose traversal foundation structure without giving ownership or execution authority.
 *
 * Why this file exists in W08:
 *   W08 needs a safe view type that can present the traversal vocabulary as data after sequence channels, relations, and transitions are defined. This view closes W08 without introducing a traversal engine.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   The view references arrays of TPolicySequenceChannel, TPolicyRelation, and TPolicyTransition. It does not own them and does not mutate them.
 *
 * Relationship to future waves:
 *   W09 TPolicy aggregate may expose this view as part of a complete policy object. Future orchestration may consume similar views but must define execution separately.
 *
 * Explicit non-responsibilities:
 *   TPolicyTraversalFoundationView is not a traversal runtime, not an orchestrator, not a scheduler, not an owner of channels, and not a graph traversal algorithm.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyTraversalFoundationView final
{
    const TPolicySequenceChannel* channels{nullptr};
    std::size_t channel_count{0};
    const TPolicyRelation* relations{nullptr};
    std::size_t relation_count{0};
    const TPolicyTransition* transitions{nullptr};
    std::size_t transition_count{0};

    constexpr TPolicyTraversalFoundationView() noexcept = default;
    constexpr TPolicyTraversalFoundationView(const TPolicySequenceChannel* ch,
                                             std::size_t ch_count,
                                             const TPolicyRelation* rel,
                                             std::size_t rel_count,
                                             const TPolicyTransition* trans,
                                             std::size_t trans_count) noexcept
        : channels(ch), channel_count(ch_count), relations(rel), relation_count(rel_count), transitions(trans), transition_count(trans_count) {}

    [[nodiscard]] constexpr bool HasChannels() const noexcept { return channels != nullptr && channel_count > 0; }
    [[nodiscard]] constexpr bool HasRelations() const noexcept { return relations != nullptr && relation_count > 0; }
    [[nodiscard]] constexpr bool HasTransitions() const noexcept { return transitions != nullptr && transition_count > 0; }
    [[nodiscard]] constexpr bool IsNonEmpty() const noexcept { return HasChannels() || HasRelations() || HasTransitions(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
