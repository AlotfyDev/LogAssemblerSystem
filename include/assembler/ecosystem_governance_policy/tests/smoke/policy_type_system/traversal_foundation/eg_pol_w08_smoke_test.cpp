#include <array>
#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/TPolicyTraversalFoundationView.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicySequenceChannelId first_id{1};
    TPolicySequenceChannelId second_id{2};
    TPolicySequenceChannel first{first_id, TPolicySequenceChannelKind::linear, TPolicyChannelSlotCardinality::Single(), TPolicyChannelReadiness::ready};
    TPolicySequenceChannel second{second_id, TPolicySequenceChannelKind::ring, TPolicyChannelSlotCardinality::Multi(3), TPolicyChannelReadiness::eligible};

    assert(first.IsValid());
    assert(first.IsLinear());
    assert(first.IsSingleSlot());
    assert(first.AllowsEntry());
    assert(first.CursorWithinSlots());

    assert(second.IsValid());
    assert(second.IsRing());
    assert(second.IsMultiSlot());
    assert(second.AllowsEntry());

    TPolicyRelation relation{TPolicyRelationId{10}, TPolicyRelationKind::precedence, true};
    assert(relation.IsValid());

    TPolicyTransition transition{TPolicyTransitionId{20}, first_id, relation.relation_id, second_id, TPolicyChannelReadiness::eligible};
    assert(transition.IsValid());
    assert(!transition.IsSelfTransition());
    assert(transition.AllowsEntry());

    std::array<TPolicySequenceChannel, 2> channels{first, second};
    std::array<TPolicyRelation, 1> relations{relation};
    std::array<TPolicyTransition, 1> transitions{transition};

    TPolicyTraversalFoundationView view{channels.data(), channels.size(), relations.data(), relations.size(), transitions.data(), transitions.size()};
    assert(view.HasChannels());
    assert(view.HasRelations());
    assert(view.HasTransitions());
    assert(view.IsNonEmpty());

    return 0;
}
