#pragma once

#include "assembler/ecosystem_governance/policy_type_system/policy_graph/nodes/TPolicyGraphNodeId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/sequence_channels/TPolicySequenceChannelId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyExitSurface.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: entry_exit
 *
 * Full architectural responsibility:
 *   TPolicyExitSurface describes a structural exit surface for a sequence channel. It may optionally point to a graph node that anchors exit, but it does not perform traversal movement.
 *
 * Why this file exists in W08:
 *   Every sequence channel must expose an exit surface so channel-to-channel transitions can be described without treating edges as arbitrary or semantically empty.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicySequenceChannel carries an exit surface. TPolicyTransition may originate from a channel whose exit surface is represented by this type.
 *
 * Relationship to future waves:
 *   Future traversal orchestration may define when exit is allowed and how it affects cursor state. W09 TPolicy may expose exit surfaces through views.
 *
 * Explicit non-responsibilities:
 *   TPolicyExitSurface is not a transition, not a relation, not an execution step, not an algorithmic exit procedure, and not a scheduler signal.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyExitSurface final
{
    TPolicySequenceChannelId channel_id{};
    TPolicyGraphNodeId anchor_node_id{};
    bool required{true};

    constexpr TPolicyExitSurface() noexcept = default;
    constexpr TPolicyExitSurface(TPolicySequenceChannelId channel, TPolicyGraphNodeId anchor = TPolicyGraphNodeId{}, bool is_required = true) noexcept
        : channel_id(channel), anchor_node_id(anchor), required(is_required) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return channel_id.IsValid(); }
    [[nodiscard]] constexpr bool HasAnchorNode() const noexcept { return anchor_node_id.IsValid(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
