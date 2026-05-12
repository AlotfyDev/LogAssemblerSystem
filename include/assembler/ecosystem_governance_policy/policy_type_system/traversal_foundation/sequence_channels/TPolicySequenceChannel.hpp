#pragma once

#include "TPolicySequenceChannelId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/TPolicyGraphId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/channel_kinds/TPolicySequenceChannelKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/cursor/TPolicyCursor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/entry_exit/TPolicyEntrySurface.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/entry_exit/TPolicyExitSurface.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/readiness/TPolicyChannelReadiness.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/slot_cardinality/TPolicyChannelSlotCardinality.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySequenceChannel.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: sequence_channels
 *
 * Full architectural responsibility:
 *   TPolicySequenceChannel is the smallest traversal-bearing structural unit in the policy traversal foundation. It combines channel identity, kind, slot cardinality, entry/exit surfaces, readiness, cursor awareness, and optional graph association without creating a traversal engine.
 *
 * Why this file exists in W08:
 *   W08 centers traversal foundation on Sequence Channels. This file is the core carrier that integrates the W08 vocabulary while preserving the rule that traversal is channel-governed and not unrestricted graph wandering.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   This file composes TPolicySequenceChannelId, TPolicySequenceChannelKind, TPolicyChannelSlotCardinality, TPolicyEntrySurface, TPolicyExitSurface, TPolicyChannelReadiness, and TPolicyCursor. Transitions reference it by id.
 *
 * Relationship to future waves:
 *   W09 TPolicy can aggregate or expose sequence channels through views. Future traversal orchestration can build over this carrier without changing its foundation role.
 *
 * Explicit non-responsibilities:
 *   TPolicySequenceChannel is not an arbitrary graph fragment, not a graph node container, not a traversal algorithm, not an orchestrator, not a scheduler, not a realizer, and not a runtime executor.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicySequenceChannel final
{
    TPolicySequenceChannelId channel_id{};
    TPolicyGraphId graph_id{};
    TPolicySequenceChannelKind kind{TPolicySequenceChannelKind::unknown};
    TPolicyChannelSlotCardinality slot_cardinality{};
    TPolicyEntrySurface entry_surface{};
    TPolicyExitSurface exit_surface{};
    TPolicyChannelReadiness readiness{TPolicyChannelReadiness::unknown};
    TPolicyCursor cursor{};

    constexpr TPolicySequenceChannel() noexcept = default;
    constexpr TPolicySequenceChannel(TPolicySequenceChannelId id,
                                     TPolicySequenceChannelKind k,
                                     TPolicyChannelSlotCardinality slots,
                                     TPolicyChannelReadiness r = TPolicyChannelReadiness::eligible) noexcept
        : channel_id(id),
          kind(k),
          slot_cardinality(slots),
          entry_surface(id),
          exit_surface(id),
          readiness(r),
          cursor(id, 0) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept
    {
        return channel_id.IsValid() && IsKnownPolicySequenceChannelKind(kind) && slot_cardinality.IsValid() && entry_surface.IsValid() && exit_surface.IsValid();
    }

    [[nodiscard]] constexpr bool IsLinear() const noexcept { return IsLinearPolicySequenceChannelKind(kind); }
    [[nodiscard]] constexpr bool IsRing() const noexcept { return IsRingPolicySequenceChannelKind(kind); }
    [[nodiscard]] constexpr bool IsSingleSlot() const noexcept { return slot_cardinality.IsSingleSlot(); }
    [[nodiscard]] constexpr bool IsMultiSlot() const noexcept { return slot_cardinality.IsMultiSlot(); }
    [[nodiscard]] constexpr bool AllowsEntry() const noexcept { return IsValid() && AllowsPolicyChannelEntry(readiness); }

    [[nodiscard]] constexpr bool CursorWithinSlots() const noexcept
    {
        return cursor.IsValid() && slot_cardinality.IsValid() && cursor.position < slot_cardinality.slot_count;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
