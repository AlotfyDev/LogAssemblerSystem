#pragma once

#include "TPolicyTransitionId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/readiness/TPolicyChannelReadiness.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/relations/TPolicyRelationId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/sequence_channels/TPolicySequenceChannelId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTransition.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: transitions
 *
 * Full architectural responsibility:
 *   TPolicyTransition describes relation-mediated movement from a source sequence channel to a target sequence channel. It preserves the transition/relation distinction and carries readiness as data only.
 *
 * Why this file exists in W08:
 *   The traversal foundation treats branching minimally as transition from one sequence channel to another, mediated by relation-bearing semantics. W08 introduces the transition carrier without executing traversal.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicyTransition references TPolicySequenceChannelId for source/target and TPolicyRelationId for semantic mediation. TPolicyTraversalFoundationView may expose transition arrays.
 *
 * Relationship to future waves:
 *   Future orchestration may attach path composition, branch selection, merge synchronization, or replacement-time discipline to transitions.
 *
 * Explicit non-responsibilities:
 *   TPolicyTransition is not a structural graph edge, not a traversal instruction, not an engine step, not a scheduler action, and not an invocation of realization machinery.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyTransition final
{
    TPolicyTransitionId transition_id{};
    TPolicySequenceChannelId source_channel_id{};
    TPolicyRelationId relation_id{};
    TPolicySequenceChannelId target_channel_id{};
    TPolicyChannelReadiness readiness{TPolicyChannelReadiness::unknown};

    constexpr TPolicyTransition() noexcept = default;
    constexpr TPolicyTransition(TPolicyTransitionId id,
                                TPolicySequenceChannelId source,
                                TPolicyRelationId relation,
                                TPolicySequenceChannelId target,
                                TPolicyChannelReadiness r = TPolicyChannelReadiness::eligible) noexcept
        : transition_id(id), source_channel_id(source), relation_id(relation), target_channel_id(target), readiness(r) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept
    {
        return transition_id.IsValid() && source_channel_id.IsValid() && relation_id.IsValid() && target_channel_id.IsValid();
    }

    [[nodiscard]] constexpr bool IsSelfTransition() const noexcept
    {
        return source_channel_id.IsValid() && source_channel_id == target_channel_id;
    }

    [[nodiscard]] constexpr bool AllowsEntry() const noexcept
    {
        return IsValid() && AllowsPolicyChannelEntry(readiness);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
