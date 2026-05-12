#include <cassert>
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicy.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyBuildRequest request{TPolicyId{1001}, TPolicyFamilyId{77}, TPolicyVersion{1, 0, 0}, TPolicyScope::component};
    TPolicy policy = TPolicy::FromRequest(request);

    assert(policy.PolicyId() == TPolicyId{1001});
    assert(policy.FamilyId() == TPolicyFamilyId{77});
    assert(policy.HasMinimumIdentity());

    const TPolicyClause clause{TPolicyClauseId{1}, TPolicyId{1001}, TPolicyClauseKind::directive, TPolicyClauseRole::primary, 0, 42};
    assert(policy.AddClause(clause));
    assert(policy.HasUsableClauses());

    TPolicyReplacementPlan plan{1, TPolicyId{1001}, TPolicyId{1002}, TPolicySafePointId{1}, TPolicyReplacementEligibility::eligible, 11};
    policy.SetReplacementPlan(plan);
    assert(policy.HasReplacementStructure());

    policy.SetLifecycleSnapshot(TPolicyLifecycleSnapshot{TPolicyLifecycleMarker{TPolicyId{1001}, TPolicyLifecycleState::active, 1}});
    assert(policy.HasLifecycleStructure());

    policy.AddAuditMarker(TPolicyAuditMarker{TPolicyObservationId{1}, TPolicyId{1001}, TPolicyObservationKind::activation});
    assert(policy.HasObservationStructure());

    TPolicyMechanismDescriptor mechanism{10, 1, TPolicyRealizationMode::descriptive_only};
    TPolicyTargetKindDescriptor target{TPolicyTargetKind::dispatcher, 99, 7};
    TPolicyRealizationDescriptor descriptor{TPolicyRealizationBindingId{5}, mechanism, target};
    TPolicyRealizationBinding binding{TPolicyId{1001}, TPolicyFamilyId{77}, descriptor, TPolicyLifecycleState::active, TPolicyReplacementEligibility::eligible};
    policy.SetRealizationBinding(binding);
    assert(policy.HasRealizationBinding());

    TPolicyGraph graph{TPolicyGraphId{1001}};
    const TPolicyGraphNodeId root{1};
    const TPolicyGraphNodeId identity{2};
    const TPolicyGraphNodeId clauseNode{3};
    const TPolicyGraphNodeId safePoint{4};
    const TPolicyGraphNodeId lifecycle{5};
    const TPolicyGraphNodeId realization{6};
    const TPolicyGraphNodeId observation{7};

    assert(graph.AddNode(TPolicyGraphNode{TPolicyGraphId{1001}, root, TPolicyGraphNodeKind::policy_root, TPolicyId{1001}}));
    assert(graph.AddNode(TPolicyGraphNode{TPolicyGraphId{1001}, identity, TPolicyGraphNodeKind::identity_structure, TPolicyId{1001}}));
    assert(graph.AddNode(TPolicyGraphNode{TPolicyGraphId{1001}, clauseNode, TPolicyGraphNodeKind::clause, TPolicyId{1001}}));
    assert(graph.AddNode(TPolicyGraphNode{TPolicyGraphId{1001}, safePoint, TPolicyGraphNodeKind::safe_point, TPolicyId{1001}}));
    assert(graph.AddNode(TPolicyGraphNode{TPolicyGraphId{1001}, lifecycle, TPolicyGraphNodeKind::lifecycle_state, TPolicyId{1001}}));
    assert(graph.AddNode(TPolicyGraphNode{TPolicyGraphId{1001}, realization, TPolicyGraphNodeKind::realization_binding, TPolicyId{1001}}));
    assert(graph.AddNode(TPolicyGraphNode{TPolicyGraphId{1001}, observation, TPolicyGraphNodeKind::observation_audit, TPolicyId{1001}}));

    assert(graph.AddEdge(TPolicyGraphEdge{TPolicyGraphId{1001}, TPolicyGraphEdgeId{1}, TPolicyGraphEdgeKind::root_to_identity, root, identity}));
    assert(graph.AddEdge(TPolicyGraphEdge{TPolicyGraphId{1001}, TPolicyGraphEdgeId{2}, TPolicyGraphEdgeKind::root_to_clause, root, clauseNode}));
    assert(graph.AddEdge(TPolicyGraphEdge{TPolicyGraphId{1001}, TPolicyGraphEdgeId{3}, TPolicyGraphEdgeKind::root_to_safe_point, root, safePoint}));
    assert(graph.AddEdge(TPolicyGraphEdge{TPolicyGraphId{1001}, TPolicyGraphEdgeId{4}, TPolicyGraphEdgeKind::root_to_lifecycle, root, lifecycle}));
    assert(graph.AddEdge(TPolicyGraphEdge{TPolicyGraphId{1001}, TPolicyGraphEdgeId{5}, TPolicyGraphEdgeKind::root_to_realization_binding, root, realization}));
    assert(graph.AddEdge(TPolicyGraphEdge{TPolicyGraphId{1001}, TPolicyGraphEdgeId{6}, TPolicyGraphEdgeKind::root_to_observation, root, observation}));
    assert(graph.IsStructurallyValidMinimum());
    policy.SetGraph(graph);

    TPolicySequenceChannel channel{TPolicySequenceChannelId{1}, TPolicySequenceChannelKind::linear, TPolicyChannelSlotCardinality{1}};
    TPolicyRelation relation{TPolicyRelationId{1}, TPolicyRelationKind::precedence, true};
    TPolicyTransition transition{TPolicyTransitionId{1}, TPolicySequenceChannelId{1}, TPolicyRelationId{1}, TPolicySequenceChannelId{1}};
    policy.SetTraversalFoundation(TPolicyTraversalFoundationView{&channel, 1, &relation, 1, &transition, 1});
    assert(policy.HasTraversalFoundation());

    const auto report = policy.Validate();
    assert(report.IsStructurallyComplete());
    const auto build = policy.BuildResult();
    assert(build.Accepted());
    assert(build.StructurallyComplete());

    const auto snapshot = policy.Snapshot();
    assert(snapshot.structurally_complete);
    assert(snapshot.clause_count == 1);
    assert(snapshot.audit_marker_count == 1);
    assert(snapshot.graph_node_count == 7);
    assert(snapshot.traversal_channel_count == 1);

    const auto view = policy.View();
    assert(view.IsPresent());
    assert(view.IsStructurallyComplete());
    assert(view.HasTraversalFoundation());

    return 0;
}
