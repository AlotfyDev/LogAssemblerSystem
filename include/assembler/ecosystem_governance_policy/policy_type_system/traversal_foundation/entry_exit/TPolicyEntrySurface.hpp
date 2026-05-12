#pragma once

#include "assembler/ecosystem_governance/policy_type_system/policy_graph/nodes/TPolicyGraphNodeId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/sequence_channels/TPolicySequenceChannelId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyEntrySurface.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: entry_exit
 *
 * Full architectural responsibility:
 *   TPolicyEntrySurface describes a structural entry surface for a sequence channel. It may optionally point to a policy graph node that anchors entry, but it does not execute entry.
 *
 * Why this file exists in W08:
 *   Every sequence channel must have meaningful entry and exit surfaces so transitions between channels are not semantically underdefined. W08 introduces the entry surface as data, not as an activation algorithm.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicySequenceChannel carries an entry surface. TPolicyTransition may target a channel whose entry surface is represented by this type.
 *
 * Relationship to future waves:
 *   Future traversal orchestration may define activation permission, timing, and cursor effects for entry. W09 TPolicy may expose entry surfaces safely.
 *
 * Explicit non-responsibilities:
 *   TPolicyEntrySurface is not a function call, not an activation rule, not a permission engine, not a graph traversal instruction, and not a runtime entry procedure.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyEntrySurface final
{
    TPolicySequenceChannelId channel_id{};
    TPolicyGraphNodeId anchor_node_id{};
    bool required{true};

    constexpr TPolicyEntrySurface() noexcept = default;
    constexpr TPolicyEntrySurface(TPolicySequenceChannelId channel, TPolicyGraphNodeId anchor = TPolicyGraphNodeId{}, bool is_required = true) noexcept
        : channel_id(channel), anchor_node_id(anchor), required(is_required) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return channel_id.IsValid(); }
    [[nodiscard]] constexpr bool HasAnchorNode() const noexcept { return anchor_node_id.IsValid(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
