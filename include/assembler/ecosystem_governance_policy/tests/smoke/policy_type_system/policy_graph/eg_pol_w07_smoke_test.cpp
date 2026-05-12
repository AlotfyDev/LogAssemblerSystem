#include <cassert>
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/TPolicyGraph.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyGraphId gid{1};
    TPolicyId pid{101};
    TPolicyGraph graph{gid};

    TPolicyGraphNode root{gid, TPolicyGraphNodeId{1}, TPolicyGraphNodeKind::policy_root, pid};
    TPolicyGraphNode identity{gid, TPolicyGraphNodeId{2}, TPolicyGraphNodeKind::identity_structure, pid};
    TPolicyGraphNode clause{gid, TPolicyGraphNodeId{3}, TPolicyGraphNodeKind::clause, pid};
    clause.clause_ref = TPolicyClauseId{20};
    TPolicyGraphNode safe_point{gid, TPolicyGraphNodeId{4}, TPolicyGraphNodeKind::safe_point, pid};
    safe_point.safe_point_ref = TPolicySafePointId{30};
    TPolicyGraphNode lifecycle{gid, TPolicyGraphNodeId{5}, TPolicyGraphNodeKind::lifecycle_state, pid};
    TPolicyGraphNode realization{gid, TPolicyGraphNodeId{6}, TPolicyGraphNodeKind::realization_binding, pid};
    realization.realization_binding_ref = TPolicyRealizationBindingId{40};
    TPolicyGraphNode observation{gid, TPolicyGraphNodeId{7}, TPolicyGraphNodeKind::observation_audit, pid};
    observation.observation_ref = TPolicyObservationId{50};

    assert(graph.AddNode(root));
    assert(graph.AddNode(identity));
    assert(graph.AddNode(clause));
    assert(graph.AddNode(safe_point));
    assert(graph.AddNode(lifecycle));
    assert(graph.AddNode(realization));
    assert(graph.AddNode(observation));

    assert(graph.AddEdge(TPolicyGraphEdge{gid, TPolicyGraphEdgeId{1}, TPolicyGraphEdgeKind::root_to_identity, root.node_id, identity.node_id}));
    assert(graph.AddEdge(TPolicyGraphEdge{gid, TPolicyGraphEdgeId{2}, TPolicyGraphEdgeKind::root_to_clause, root.node_id, clause.node_id}));
    assert(graph.AddEdge(TPolicyGraphEdge{gid, TPolicyGraphEdgeId{3}, TPolicyGraphEdgeKind::root_to_safe_point, root.node_id, safe_point.node_id}));
    assert(graph.AddEdge(TPolicyGraphEdge{gid, TPolicyGraphEdgeId{4}, TPolicyGraphEdgeKind::root_to_lifecycle, root.node_id, lifecycle.node_id}));
    assert(graph.AddEdge(TPolicyGraphEdge{gid, TPolicyGraphEdgeId{5}, TPolicyGraphEdgeKind::root_to_realization_binding, root.node_id, realization.node_id}));
    assert(graph.AddEdge(TPolicyGraphEdge{gid, TPolicyGraphEdgeId{6}, TPolicyGraphEdgeKind::root_to_observation, root.node_id, observation.node_id}));

    assert(graph.HasSingleRoot());
    assert(graph.HasMinimumRequiredNodeKinds());
    assert(graph.HasMinimumRequiredRootEdges());
    assert(graph.IsStructurallyValidMinimum());

    auto view = graph.View();
    assert(view.HasGraphId());
    assert(view.HasNodes());
    assert(view.HasEdges());
    assert(view.node_count == 7);
    assert(view.edge_count == 6);

    auto report = graph.ReportMinimumValidity();
    assert(report.satisfied);
    assert(!report.IsFailure());

    return 0;
}
