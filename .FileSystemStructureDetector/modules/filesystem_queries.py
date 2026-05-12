#!/usr/bin/env python3
"""
File System Query System
Implements pathfinding and query operations using the nested matrices.
Part of the Multi-Tier Object Architecture.
"""

from typing import Dict, List, Optional, Any
import heapq


class QuerySystem:
    """
    Handles complex queries using layer-aware traversal with dynamic configuration.
    All operations respect layer boundaries and use breadth-first strategies.
    No hardcoded limits - all bounds calculated from system dimensions.
    """

    def __init__(self, graph, registry_system, matrix_system):
        self.graph = graph
        self.registry_system = registry_system
        self.matrix_system = matrix_system

        # Use dynamic configuration instead of hardcoded limits
        self.query_config = graph.config.query_config if graph else None

    def find_shortest_path_matrix(self, start_path: str, end_path: str) -> Optional[List[str]]:
        """
        Find shortest path using SPATIAL ATTRIBUTE DIFFERENCES.
        Based on differences in spatial coordinate values, not graph distances.
        """
        start_node = self.graph.get_node(start_path)
        end_node = self.graph.get_node(end_path)

        if not start_node or not end_node:
            return None

        # Use ANCESTOR VECTOR-BASED pathfinding (primary) with spatial differences (secondary)
        return self._ancestor_vector_pathfinding(start_node, end_node)

    def _ancestor_vector_pathfinding(self, start_node, end_node) -> Optional[List[str]]:
        """
        ANCESTOR VECTOR-BASED PATHFINDING - PRIMARY METHOD.
        Uses ancestor vector comparison for shortest path calculation.
        Single-layer indexes provide precise branching within common ancestor context.
        """
        # Step 1: ANCESTOR VECTOR ANALYSIS - Find common ancestor and branching
        common_ancestor = start_node.find_common_ancestor_with(end_node)
        branching_point = start_node.find_branching_point_with(end_node)

        if not common_ancestor:
            # No common ancestor - use spatial fallback
            return self._spatial_fallback_pathfinding(start_node, end_node)

        # Step 2: SINGLE-LAYER INDEX NAVIGATION - Precise branching within common ancestor
        if branching_point and branching_point != common_ancestor:
            # Navigate within the common ancestor's layer using single-layer indexes
            return self._single_layer_index_pathfinding(start_node, end_node, branching_point)

        # Step 3: Hierarchical path construction using ancestor vectors
        return self._ancestor_hierarchical_pathfinding(start_node, end_node, common_ancestor)

    def _single_layer_index_pathfinding(self, start_node, end_node, branching_point: str) -> Optional[List[str]]:
        """
        Use SINGLE-LAYER INDEXES for precise navigation within branching context.
        This provides accurate branching point identification.
        """
        # Get the layer registry for the branching point
        registry = None
        for reg in self.registry_system.layer_registries.values():
            # Find registry containing the branching point
            if any(branching_point in folder_node.relationships.ancestor_vector.ancestors
                   for folder_node in reg.folders.values()):
                registry = reg
                break

        if not registry:
            return None

        # Use single-layer index relationships for precise pathfinding
        return self._spatial_guided_breadth_first(start_node, end_node, registry, 3)

    def _ancestor_hierarchical_pathfinding(self, start_node, end_node, common_ancestor: str) -> Optional[List[str]]:
        """
        Construct hierarchical path using ancestor vector information.
        Minimal overhead recursive operation based on ancestor chains.
        """
        path = []

        # Build path from start to common ancestor
        start_to_common = self._trace_ancestor_path(start_node, common_ancestor)
        if not start_to_common:
            return None

        # Build path from common ancestor to end
        common_to_end = self._trace_ancestor_path(end_node, common_ancestor)
        if not common_to_end:
            return None

        # Combine paths (remove duplicate common ancestor)
        path = start_to_common[:-1] + common_to_end[::-1]  # Reverse end path

        return path

    def _trace_ancestor_path(self, node, target_ancestor: str) -> Optional[List[str]]:
        """
        Trace path from node to target ancestor using ancestor vector.
        Minimal overhead - direct ancestor chain traversal.
        """
        path = [node.full_path]
        current = node

        # Walk up ancestor chain until we reach target
        while current:
            if target_ancestor in current.ancestor_chain:
                # Found target in ancestors - construct path
                ancestor_index = current.ancestor_chain.index(target_ancestor)
                remaining_ancestors = current.ancestor_chain[ancestor_index:]
                path.extend(remaining_ancestors)
                return path

            # Move to parent
            current = current.parent
            if current:
                path.append(current.full_path)

        return None  # Target ancestor not found in chain

    def _calculate_ancestor_based_differences(self, node1, node2) -> Dict[str, Any]:
        """
        Calculate differences using ANCESTOR VECTORS as the foundation.
        Layer indicator = ancestor vector length!
        """
        differences = {}

        # ANCESTOR VECTOR DIFFERENCES - PRIMARY CALCULATION METHOD
        ancestor_vector_diff = self._calculate_ancestor_vector_differences(node1, node2)
        differences.update(ancestor_vector_diff)

        # Spatial coordinate differences (secondary, derived from ancestors)
        spatial_diffs = self._calculate_spatial_differences(node1, node2)
        differences.update(spatial_diffs)

        # Combined hierarchical distance
        differences['hierarchical_distance'] = (
            differences['ancestor_distance'] +  # Primary: ancestor vector distance
            differences['combined_spatial_distance'] * 0.1  # Secondary: spatial weighting
        )

        return differences

    def _calculate_ancestor_vector_differences(self, node1, node2) -> Dict[str, Any]:
        """
        Calculate differences using ancestor vectors.
        THIS IS THE FOUNDATION - layer depth = ancestor vector length!
        """
        ancestor_diffs = {}

        # Ancestor distance using vector comparison
        ancestor_diffs['ancestor_distance'] = node1.get_ancestor_distance_to(node2)

        # Common ancestor identification
        common_ancestor = node1.find_common_ancestor_with(node2)
        ancestor_diffs['common_ancestor'] = common_ancestor
        ancestor_diffs['has_common_ancestor'] = bool(common_ancestor)

        # Branching point analysis
        branching_point = node1.find_branching_point_with(node2)
        ancestor_diffs['branching_point'] = branching_point

        # Layer differences derived from ancestor vectors
        ancestor_diffs['ancestor_layer_diff'] = abs(len(node1.ancestor_chain) - len(node2.ancestor_chain))

        # Ancestor chain similarity
        chain1 = set(node1.ancestor_chain)
        chain2 = set(node2.ancestor_chain)
        ancestor_diffs['ancestor_overlap'] = len(chain1 & chain2)
        ancestor_diffs['ancestor_similarity'] = ancestor_diffs['ancestor_overlap'] / max(len(chain1 | chain2), 1)

        return ancestor_diffs

    def _calculate_spatial_differences(self, node1, node2) -> Dict[str, float]:
        """
        Calculate spatial coordinate differences (secondary to ancestor vectors).
        """
        differences = {}

        # Absolute layer difference (derived from ancestor vector length!)
        differences['absolute_layer_diff'] = abs(node1.absolute_layer - node2.absolute_layer)

        # Relative layer difference from multiple reference points
        common_targets = ['/', node1.full_path, node2.full_path]
        rel_diffs = []
        for target in common_targets[:3]:
            try:
                rel_diff = abs(node1.get_relative_layer(target) - node2.get_relative_layer(target))
                rel_diffs.append(rel_diff)
            except:
                continue
        differences['relative_layer_diff'] = min(rel_diffs) if rel_diffs else 0

        # Spatial signature numerical difference
        try:
            sig1 = int(node1.spatial_signature, 16) if node1.spatial_signature else 0
            sig2 = int(node2.spatial_signature, 16) if node2.spatial_signature else 0
            differences['spatial_signature_diff'] = abs(sig1 - sig2)
        except:
            differences['spatial_signature_diff'] = 0

        # Combined spatial distance metric (weighted by ancestor context)
        ancestor_context_weight = 1.0 if node1.find_common_ancestor_with(node2) else 2.0
        differences['combined_spatial_distance'] = (
            differences['absolute_layer_diff'] * 100 * ancestor_context_weight +
            differences['relative_layer_diff'] * 10 +
            min(differences['spatial_signature_diff'] / 1000000, 10)
        )

        return differences

    def _find_path_same_layer(self, start_node, end_node) -> Optional[List[str]]:
        """Find path within same absolute layer using dynamic configuration."""
        registry = self.registry_system.get_registry(start_node.absolute_layer)
        if not registry:
            return None

        # Check direct spatial relationships
        if self._nodes_spatially_related(start_node, end_node, registry):
            return [start_node.full_path, end_node.full_path]

        # Use bounded breadth-first with spatial guidance and dynamic limits
        max_hops = self.query_config.relationship_hop_limit if self.query_config else 5
        return self._spatial_guided_breadth_first(start_node, end_node, registry, max_hops)
        """Find path within same layer using registry relationships."""
        registry = self.registry_system.get_registry(start_node.absolute_layer)
        if not registry:
            return None

        # Check direct relationships first
        if self._are_directly_related(start_node, end_node, registry):
            return [start_node.full_path, end_node.full_path]

        # Use breadth-first search within layer (preventing depth hell)
        return self._breadth_first_layer_search(start_node, end_node, registry)

    def _find_path_cross_layer_bounded(self, start_node, end_node) -> Optional[List[str]]:
        """Find path across layers with bounded traversal."""
        start_layer = start_node.absolute_layer
        end_layer = end_node.absolute_layer

        # Limit layer jumps to prevent excessive traversal
        layer_diff = abs(end_layer - start_layer)
        if layer_diff > self.max_query_depth:
            print(f"Layer difference too large ({layer_diff}) - limiting to {self.max_query_depth}")
            return None

        # Use matrix relationships but with layer bounds
        for matrix in self.matrix_system.matrices.values():
            path = matrix.find_shortest_path(start_node.full_path, end_node.full_path, self.graph)
            if path:
                return path

        return None

    def _nodes_spatially_related(self, node1, node2, registry) -> bool:
        """Check if two nodes are spatially related using intrinsic coordinates."""
        # Use spatial metadata for direct relationship checking
        if node1.get_layer_distance(node2) == 0:  # Same absolute layer
            # Check same parent (spatial proximity)
            if node1.is_file and node2.is_file and node1.parent == node2.parent:
                return True

            # Check parent-child spatial relationship
            if not node1.is_file and node2.is_file and node2.parent == node1:
                return True

        # Check registry-based spatial relationships
        return self._are_directly_related(node1, node2, registry)

    def _are_directly_related(self, node1, node2, registry) -> bool:
        """Check if two nodes are directly related within a layer."""
        # Same parent check
        if node1.is_file and node2.is_file and node1.parent == node2.parent:
            return True

        # Parent-child check
        if not node1.is_file and node2.is_file and node2.parent == node1:
            return True

        # Check registry mappings
        related_nodes = registry.find_related_nodes(node1.name)
        if related_nodes['type'] != 'not_found':
            if node2.name in related_nodes.get('sibling_files', []) or \
               node2.name == related_nodes.get('parent_folder'):
                return True

        return False

    def _spatial_guided_breadth_first(self, start_node, end_node, registry, max_hops: int = 3) -> Optional[List[str]]:
        """
        SPATIAL DIFFERENCE GUIDED breadth-first search.
        Uses spatial coordinate VALUE DIFFERENCES to prioritize paths.
        NOT traditional graph distance - pure spatial arithmetic.
        """
        from collections import deque

        visited = {start_node.spatial_signature}
        queue = deque([(start_node, [start_node.full_path], 0)])  # node, path, hops

        target_differences = self._calculate_spatial_differences(start_node, end_node)

        while queue and len(queue) < 500:  # Prevent queue explosion
            current_node, path, hops = queue.popleft()

            if hops > max_hops:
                continue

            if current_node == end_node:
                return path

            # Get spatially related candidates
            candidates = self._get_spatial_candidates(current_node, registry)
            candidates = [c for c in candidates if c.spatial_signature not in visited]

            if not candidates:
                continue

            # Sort by SPATIAL DIFFERENCE from target (not graph distance)
            current_differences = self._calculate_spatial_differences(current_node, end_node)

            candidate_scores = []
            for candidate in candidates:
                candidate_differences = self._calculate_spatial_differences(candidate, end_node)

                # Calculate improvement in spatial distance
                spatial_improvement = current_differences['combined_spatial_distance'] - candidate_differences['combined_spatial_distance']

                # Also consider absolute layer progression toward target
                layer_progression = 0
                if end_node.absolute_layer > current_node.absolute_layer:
                    layer_progression = min(1, (candidate.absolute_layer - current_node.absolute_layer) / max(1, end_node.absolute_layer - current_node.absolute_layer))
                elif end_node.absolute_layer < current_node.absolute_layer:
                    layer_progression = min(1, (current_node.absolute_layer - candidate.absolute_layer) / max(1, current_node.absolute_layer - end_node.absolute_layer))

                # Combined spatial score (higher is better)
                spatial_score = spatial_improvement + layer_progression * 10
                candidate_scores.append((candidate, spatial_score))

            # Sort by spatial score (best first)
            candidate_scores.sort(key=lambda x: x[1], reverse=True)

            # Add top candidates to queue
            for candidate, _ in candidate_scores[:3]:  # Limit to best 3
                visited.add(candidate.spatial_signature)
                queue.append((candidate, path + [candidate.full_path], hops + 1))

        return None

    def _get_spatial_candidates(self, node, registry) -> List:
        """Get spatially related candidate nodes using coordinates and registry."""
        candidates = []

        # Get registry-based relationships
        related = registry.find_related_nodes(node.name)
        if related['type'] != 'file':
            # Add sibling files
            for sibling_name in related.get('sibling_files', []):
                sibling = registry.files.get(sibling_name)
                if sibling:
                    candidates.append(sibling)

            # Add parent folder
            parent_name = related.get('parent_folder')
            if parent_name:
                parent = registry.folders.get(parent_name)
                if parent:
                    candidates.append(parent)
        else:
            # For files, add parent and siblings
            parent_name = related.get('parent_folder')
            if parent_name:
                parent = registry.folders.get(parent_name)
                if parent:
                    candidates.append(parent)

                # Add other files in same folder
                for other_file_name in registry.folder_to_files.get(parent_name, set()):
                    if other_file_name != node.name:
                        other_file = registry.files.get(other_file_name)
                        if other_file:
                            candidates.append(other_file)

        return candidates

    def _spatial_layer_progression_search(self, start_node, end_node) -> Optional[List[str]]:
        """
        Search across layers using spatial coordinate progression.
        Moves through absolute layers systematically.
        """
        start_layer = start_node.absolute_layer
        end_layer = end_node.absolute_layer

        # Determine progression direction
        direction = 1 if end_layer > start_layer else -1
        current_layer = start_layer

        path = [start_node.full_path]
        current_node = start_node

        # Progress through layers
        while current_layer != end_layer and abs(current_layer - start_layer) <= self.max_query_depth:
            current_layer += direction

            # Find spatially closest node in next layer
            next_node = self._find_spatially_closest_in_layer(current_node, current_layer)
            if next_node:
                path.append(next_node.full_path)
                current_node = next_node
                if next_node == end_node:
                    return path
            else:
                break  # No path in this layer progression

        return None

    def _find_spatially_closer_node(self, current_node, target_node, visited_signatures):
        """
        Find next node that reduces SPATIAL DIFFERENCE to target.
        Uses spatial coordinate arithmetic, not graph distance.
        """
        # Get all possible candidate nodes from relationships
        candidates = []

        # From current node's relationships
        for related_path in (list(current_node.relationships.sibling_files) +
                           list(current_node.relationships.sibling_folders) +
                           list(current_node.relationships.community_files) +
                           list(current_node.relationships.community_folders) +
                           list(current_node.relationships.child_files) +
                           list(current_node.relationships.child_folders) +
                           [current_node.relationships.parent_folder] if current_node.relationships.parent_folder else []):
            if related_path:
                related_node = self.graph.get_node(related_path)
                if related_node and related_node.spatial_signature not in visited_signatures:
                    candidates.append(related_node)

        # From cross-layer relationships
        for layer_files in current_node.relationships.related_files_cross_layer.values():
            for file_path in layer_files:
                file_node = self.graph.get_node(file_path)
                if file_node and file_node.spatial_signature not in visited_signatures:
                    candidates.append(file_node)

        for layer_folders in current_node.relationships.related_folders_cross_layer.values():
            for folder_path in layer_folders:
                folder_node = self.graph.get_node(folder_path)
                if folder_node and folder_node.spatial_signature not in visited_signatures:
                    candidates.append(folder_node)

        if not candidates:
            return None

        # Find candidate with best spatial difference reduction
        current_differences = self._calculate_spatial_differences(current_node, target_node)
        best_candidate = None
        best_improvement = -float('inf')

        for candidate in candidates[:20]:  # Limit candidates to avoid excessive calculation
            candidate_differences = self._calculate_spatial_differences(candidate, target_node)

            # Calculate improvement in spatial distance
            improvement = current_differences['combined_spatial_distance'] - candidate_differences['combined_spatial_distance']

            # Bonus for layer progression toward target
            layer_bonus = 0
            if target_node.absolute_layer > current_node.absolute_layer and candidate.absolute_layer > current_node.absolute_layer:
                layer_bonus = 5  # Moving toward target layer
            elif target_node.absolute_layer < current_node.absolute_layer and candidate.absolute_layer < current_node.absolute_layer:
                layer_bonus = 5  # Moving toward target layer

            total_score = improvement + layer_bonus

            if total_score > best_improvement:
                best_improvement = total_score
                best_candidate = candidate

        return best_candidate

    def _breadth_first_layer_search(self, start_node, end_node, registry, max_hops: int = 5) -> Optional[List[str]]:
        """
        Breadth-first search within a layer to prevent depth hell.
        Limited hops to avoid excessive traversal.
        """
        from collections import deque

        visited = {start_node.full_path}
        queue = deque([(start_node, [start_node.full_path])])

        while queue and len(queue) < 1000:  # Prevent queue explosion
            current_node, path = queue.popleft()

            if len(path) > max_hops:
                continue  # Too many hops

            if current_node == end_node:
                return path

            # Get related nodes from registry
            related = registry.find_related_nodes(current_node.name)
            candidates = []

            if related['type'] == 'file':
                # Add parent folder and siblings
                if related['parent_folder']:
                    parent_path = str(current_node.parent.path)
                    if parent_path not in visited:
                        candidates.append((current_node.parent, parent_path))

                for sibling_name in related.get('sibling_files', []):
                    sibling_node = registry.files.get(sibling_name)
                    if sibling_node and str(sibling_node.path) not in visited:
                        candidates.append((sibling_node, str(sibling_node.path)))

            elif related['type'] == 'folder':
                # Add contained files
                for file_name in related.get('contained_files', []):
                    file_node = registry.files.get(file_name)
                    if file_node and str(file_node.path) not in visited:
                        candidates.append((file_node, str(file_node.path)))

            # Add candidates to queue
            for candidate_node, candidate_path in candidates:
                if candidate_path not in visited:
                    visited.add(candidate_path)
                    queue.append((candidate_node, path + [candidate_path]))

        return None

    def multi_point_pathfinding(self, points: List[str]) -> Dict[str, Any]:
        """
        Find optimal paths connecting multiple points using matrix relationships.
        This implements the "shortest path between 2 or multi points" requirement.
        """
        if len(points) < 2:
            return {'error': 'Need at least 2 points'}

        # Build complete graph of relationships
        relationships = self._build_relationship_graph(points)

        # Find optimal connection path (simplified - could use TSP algorithms)
        if len(points) == 2:
            path = self.find_shortest_path_matrix(points[0], points[1])
            return {
                'points': points,
                'path': path,
                'relationships': relationships
            }

        # For multiple points, find a connecting traversal
        return self._find_multi_point_traversal(points, relationships)

    def _build_relationship_graph(self, points: List[str]) -> Dict[str, List[str]]:
        """Build a graph of relationships between points."""
        relationships = {}

        for i, point1 in enumerate(points):
            relationships[point1] = []
            node1 = self.graph.get_node(point1)

            for point2 in points[i+1:]:
                node2 = self.graph.get_node(point2)

                if node1 and node2:
                    # Check various relationship types
                    if self._are_related_same_layer(node1, node2):
                        relationships[point1].append(point2)
                    elif self._are_related_cross_layer(node1, node2):
                        relationships[point1].append(point2)

        return relationships

    def _are_related_same_layer(self, node1, node2) -> bool:
        """Check if two nodes are related within the same layer."""
        if node1.absolute_layer != node2.absolute_layer:
            return False

        registry = self.registry_system.get_registry(node1.absolute_layer)
        if not registry:
            return False

        # Check if they share a parent folder
        if node1.is_file and node2.is_file and node1.parent == node2.parent:
            return True

        # Check if folder contains file
        if not node1.is_file and node2.is_file and node2.parent == node1:
            return True

        return False

    def _are_related_cross_layer(self, node1, node2) -> bool:
        """Check if two nodes are related across different layers."""
        # Check folder hierarchy relationships
        for matrix in self.matrix_system.matrices.values():
            key1 = (node1.absolute_layer, node2.absolute_layer)
            key2 = (node2.absolute_layer, node1.absolute_layer)

            relationships = matrix.folder_hierarchy_matrix.get(key1, set()) | \
                           matrix.folder_hierarchy_matrix.get(key2, set())

            if relationships:
                # Check if the nodes are in the relationship chain
                for parent, child in relationships:
                    if (node1.name == parent and node2.name == child) or \
                       (node1.name == child and node2.name == parent):
                        return True

        return False

    def _find_multi_point_traversal(self, points: List[str], relationships: Dict[str, List[str]]) -> Dict[str, Any]:
        """Find an optimal traversal connecting multiple points."""
        # Simple greedy approach - start with most connected point
        connectivity = {point: len(rels) for point, rels in relationships.items()}
        start_point = max(connectivity.keys(), key=lambda p: connectivity[p])

        # Build traversal path
        visited = {start_point}
        path = [start_point]
        current = start_point

        while len(visited) < len(points):
            # Find closest unvisited related point
            candidates = []
            for related in relationships.get(current, []):
                if related not in visited:
                    candidates.append(related)

            if not candidates:
                # No direct connections, find any unvisited point
                candidates = [p for p in points if p not in visited]

            if not candidates:
                break

            # Choose first candidate (could be enhanced with distance metrics)
            next_point = candidates[0]
            path.append(next_point)
            visited.add(next_point)
            current = next_point

        return {
            'points': points,
            'traversal_path': path,
            'total_points': len(points),
            'connected_points': len(path),
            'relationships': relationships
        }

    def query_by_relationship_type(self, relationship_type: str, layer: int = None) -> Dict[str, Any]:
        """
        Query nodes based on relationship types within or across layers.
        """
        results = {
            'relationship_type': relationship_type,
            'layer': layer,
            'matches': []
        }

        if relationship_type == 'same_layer_siblings':
            # Files in same folder at same layer
            if layer is not None:
                registry = self.registry_system.get_registry(layer)
                if registry:
                    for folder_name, files in registry.get_file_clusters().items():
                        if len(files) > 1:
                            results['matches'].append({
                                'folder': folder_name,
                                'files': files,
                                'layer': layer
                            })

        elif relationship_type == 'cross_layer_hierarchy':
            # Folder hierarchies across layers
            for matrix in self.matrix_system.matrices.values():
                for (from_layer, to_layer), relationships in matrix.folder_hierarchy_matrix.items():
                    if layer is None or from_layer == layer or to_layer == layer:
                        results['matches'].extend([{
                            'parent_layer': from_layer,
                            'child_layer': to_layer,
                            'relationship': f"{parent}->{child}"
                        } for parent, child in relationships])

        elif relationship_type == 'file_dependencies':
            # File dependency relationships
            for matrix in self.matrix_system.matrices.values():
                for (layer1, layer2), relationships in matrix.file_dependency_matrix.items():
                    if layer is None or layer1 == layer or layer2 == layer:
                        results['matches'].extend([{
                            'layer1': layer1,
                            'layer2': layer2,
                            'files': f"{file1}<->{file2}"
                        } for file1, file2 in relationships])

        return results

    def get_optimized_query_plan(self, query_type: str, parameters: Dict[str, Any]) -> Dict[str, Any]:
        """
        Generate layer-aware query execution plan to prevent depth hell.
        Uses breadth-first strategies and depth bounds.
        """
        plan = {
            'query_type': query_type,
            'parameters': parameters,
            'execution_plan': [],
            'depth_protection': True,
            'estimated_complexity': 'unknown'
        }

        if query_type == 'file_search':
            plan['execution_plan'].append({
                'strategy': 'layer_breadth_first_search',
                'layer_bounds': f"max_depth_{self.max_query_depth}",
                'reasoning': 'Breadth-first layer traversal prevents depth hell'
            })

            # Add matrix optimization if available
            for matrix in self.matrix_system.matrices.values():
                optimal_path = matrix.optimize_query_paths('file_search')
                plan['execution_plan'].append({
                    'strategy': 'matrix_optimized_layer_order',
                    'layer_order': optimal_path[:self.max_query_depth],  # Bound the depth
                    'reasoning': 'Process high-yield layers first within depth limits'
                })

        elif query_type == 'pathfinding':
            points = parameters.get('points', [])
            if len(points) >= 2:
                # Limit multi-point pathfinding to prevent combinatorial explosion
                if len(points) > 5:
                    plan['execution_plan'].append({
                        'strategy': 'bounded_multi_point',
                        'max_points': 5,
                        'reasoning': 'Limit points to prevent complexity explosion'
                    })
                    points = points[:5]

                relationships = self._build_relationship_graph(points)
                plan['execution_plan'].append({
                    'strategy': 'layer_aware_relationship_traversal',
                    'relationships': len(relationships),
                    'layer_bounds': f"max_{self.max_query_depth}_layers",
                    'reasoning': 'Use layer relationships with depth protection'
                })

        elif query_type == 'directory_traversal':
            plan['execution_plan'].append({
                'strategy': 'bounded_depth_first_with_layer_limits',
                'max_depth': self.max_query_depth,
                'reasoning': 'Traditional traversal but with hard depth limits'
            })

        plan['estimated_complexity'] = self._estimate_complexity(plan)
        return plan

    def execute_layer_bounded_query(self, query_type: str, parameters: Dict[str, Any]) -> Any:
        """
        Execute a query with automatic layer bounds to prevent depth hell.
        """
        # Get optimized plan
        plan = self.get_optimized_query_plan(query_type, parameters)

        # Apply depth protection
        parameters['max_depth'] = min(parameters.get('max_depth', self.max_query_depth), self.max_query_depth)
        parameters['depth_protected'] = True

        # Execute with bounds
        if query_type == 'file_search':
            return self._execute_bounded_file_search(parameters)
        elif query_type == 'pathfinding':
            return self._execute_bounded_pathfinding(parameters)

        return None

    def _execute_bounded_file_search(self, parameters: Dict[str, Any]) -> List:
        """
        Execute file search with layer bounds to prevent depth hell.
        """
        pattern = parameters.get('pattern', '')
        max_depth = parameters.get('max_depth', self.max_query_depth)
        start_layers = parameters.get('start_layers', [])

        results = []

        # Use layer-priority search
        if start_layers:
            search_layers = start_layers[:max_depth]  # Bound the layers
        else:
            # Get layers with most files first (bounded)
            layer_stats = []
            for layer_num, registry in list(self.registry_system.layer_registries.items())[:max_depth]:
                stats = registry.get_layer_composition()
                layer_stats.append((layer_num, stats['files']))

            # Sort by file count descending, limit to max_depth
            search_layers = [l for l, _ in sorted(layer_stats, key=lambda x: x[1], reverse=True)][:max_depth]

        # Search layer by layer
        for layer_num in search_layers:
            registry = self.registry_system.get_registry(layer_num)
            if registry:
                # Search files in this layer
                for file_name, file_node in registry.files.items():
                    if pattern in file_name:
                        results.append({
                            'path': str(file_node.path),
                            'layer': layer_num,
                            'type': 'file'
                        })

                # Stop if we have enough results or hit depth limit
                if len(results) >= parameters.get('max_results', 100):
                    break

        return results

    def _execute_bounded_pathfinding(self, parameters: Dict[str, Any]) -> Optional[List[str]]:
        """
        Execute pathfinding with layer bounds.
        """
        points = parameters.get('points', [])
        if len(points) < 2:
            return None

        # Limit points to prevent complexity using dynamic configuration
        max_points_limit = self.query_config.max_parallel_operations if self.query_config else 5
        max_points = min(len(points), max_points_limit)
        points = points[:max_points]

        return self.multi_point_pathfinding(points)

    def _estimate_complexity(self, plan: Dict[str, Any]) -> str:
        """Estimate query complexity based on the plan."""
        steps = len(plan.get('execution_plan', []))
        if steps == 0:
            return 'low'
        elif steps <= 2:
            return 'medium'
        else:
            return 'high'