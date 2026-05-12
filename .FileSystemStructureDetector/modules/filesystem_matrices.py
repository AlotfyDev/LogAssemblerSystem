#!/usr/bin/env python3
"""
File System Matrix System
Implements nested indexing matrices for complex relationships.
Part of the Multi-Tier Object Architecture.
"""

from dataclasses import dataclass, field
from typing import Dict, Tuple, Set, Optional, List, Any
from collections import defaultdict


@dataclass
class NestedIndexMatrix:
    """Nested matrix system for organizing layer registries and their relationships."""

    # Primary layer registries (Level 1) - managed by RegistrySystem
    layer_registries: Dict[int, 'LayerRegistry'] = field(default_factory=dict)

    # Cross-layer relationship matrices (Level 2)
    folder_hierarchy_matrix: Dict[Tuple[int, int], Set[Tuple[str, str]]] = field(
        default_factory=lambda: defaultdict(set)
    )  # (from_layer, to_layer) -> set of (parent_folder, child_folder)
    file_dependency_matrix: Dict[Tuple[int, int], Set[Tuple[str, str]]] = field(
        default_factory=lambda: defaultdict(set)
    )  # (from_layer, to_layer) -> set of (file, related_file)

    # Higher-level organization matrices (Level 3)
    layer_progression_patterns: Dict[str, List[int]] = field(default_factory=dict)
    structural_similarity_matrix: Dict[Tuple[int, int], float] = field(default_factory=dict)
    query_optimization_paths: Dict[str, List[int]] = field(default_factory=dict)

    # Statistical distributions (Level 4)
    layer_statistics_matrix: Dict[int, Dict[str, any]] = field(default_factory=dict)
    pattern_recognition_matrix: Dict[str, Dict[int, float]] = field(default_factory=dict)

    def add_folder_relationship(self, parent_layer: int, child_layer: int,
                               parent_name: str, child_name: str):
        """Add folder hierarchy relationship between layers."""
        key = (parent_layer, child_layer)
        self.folder_hierarchy_matrix[key].add((parent_name, child_name))

    def add_file_relationship(self, layer1: int, layer2: int, file1: str, file2: str):
        """Add file dependency relationship between layers."""
        key = (min(layer1, layer2), max(layer1, layer2))
        self.file_dependency_matrix[key].add((file1, file2))

    def build_relationships_from_graph(self, graph):
        """Build all relationship matrices from the file system graph."""
        # Import avoided to prevent circular import - using graph parameter

        # Build folder hierarchy matrix
        for node in graph.all_nodes.values():
            if not node.is_file and node.parent:
                parent_layer = node.parent.absolute_layer
                child_layer = node.absolute_layer
                if parent_layer != child_layer:
                    self.add_folder_relationship(parent_layer, child_layer,
                                               node.parent.name, node.name)

        # Build file dependency matrix (simplified - files in same directory at different layers)
        for registry in self.layer_registries.values():
            for file_name, parent_folder in registry.file_to_folder.items():
                # Find files in same folder but different layers
                for other_layer, other_registry in self.layer_registries.items():
                    if other_layer != registry.layer:
                        if parent_folder in other_registry.folders:
                            # There are files in the same folder at different layers
                            other_files = other_registry.folder_to_files.get(parent_folder, set())
                            for other_file in other_files:
                                self.add_file_relationship(registry.layer, other_layer,
                                                         file_name, other_file)

    def find_shortest_path(self, start_path: str, end_path: str, graph) -> Optional[List[str]]:
        """
        Find shortest path between two nodes using the nested index matrices.
        This leverages layer information for optimized pathfinding.
        """
        # Import avoided to prevent circular import

        start_node = graph.get_node(start_path)
        end_node = graph.get_node(end_path)

        if not start_node or not end_node:
            return None

        # Use layer information to optimize pathfinding
        start_layer = start_node.absolute_layer
        end_layer = end_node.absolute_layer

        # If same layer, use direct layer registry relationships
        if start_layer == end_layer:
            return self._find_path_same_layer(start_node, end_node)

        # If different layers, use cross-layer relationships
        return self._find_path_cross_layer(start_node, end_node, graph)

    def _find_path_same_layer(self, start_node, end_node) -> Optional[List[str]]:
        """Find path within the same layer using registry relationships."""
        registry = self.layer_registries.get(start_node.absolute_layer)
        if not registry:
            return None

        # Simple implementation - could be enhanced with graph algorithms
        path = [start_node.full_path]

        # If both are files in same folder, direct relationship
        if (start_node.is_file and end_node.is_file and
            start_node.parent == end_node.parent):
            path.append(end_node.full_path)
            return path

        # If folder contains file
        if (not start_node.is_file and end_node.is_file and
            end_node.parent == start_node):
            path.append(end_node.full_path)
            return path

        return None  # Path not found with current simple logic

    def _find_path_cross_layer(self, start_node, end_node, graph) -> Optional[List[str]]:
        """Find path across different layers using hierarchy matrices."""
        # Use existing relative path finding but enhanced with matrix knowledge
        relative_path = graph.find_nearest_relative_path(start_node.full_path, end_node.full_path)
        if relative_path:
            return [start_node.full_path, end_node.full_path]  # Simplified

        return None

    def analyze_layer_patterns(self) -> Dict[str, any]:
        """Analyze patterns across all layer registries."""
        patterns = {
            'layer_depth_distribution': {},
            'folder_file_ratios': {},
            'common_structural_patterns': [],
            'layer_progression_trends': {}
        }

        # Calculate distributions
        for layer, stats in self.layer_statistics_matrix.items():
            patterns['layer_depth_distribution'][layer] = stats['total_nodes']
            if stats['folders'] > 0:
                patterns['folder_file_ratios'][layer] = stats['files'] / stats['folders']

        # Find progression patterns (layers with similar structures)
        self._identify_progression_patterns(patterns)

        return patterns

    def _identify_progression_patterns(self, patterns: Dict[str, any]):
        """Identify patterns in layer progression."""
        # Simple pattern recognition - layers with similar folder/file ratios
        ratios = patterns['folder_file_ratios']

        # Group layers by ratio similarity (within 20% difference)
        ratio_groups = {}
        for layer, ratio in ratios.items():
            found_group = False
            for group_ratio, layers in ratio_groups.items():
                if abs(ratio - group_ratio) / max(ratio, group_ratio) < 0.2:
                    layers.append(layer)
                    found_group = True
                    break
            if not found_group:
                ratio_groups[ratio] = [layer]

        patterns['structural_similarity_groups'] = ratio_groups

    def optimize_query_paths(self, query_type: str) -> List[int]:
        """Get optimized layer traversal path for specific query types."""
        if query_type == 'file_search':
            # For file searches, start from layers with most files
            return sorted(self.layer_statistics_matrix.keys(),
                         key=lambda l: self.layer_statistics_matrix[l]['files'],
                         reverse=True)
        elif query_type == 'folder_navigation':
            # For folder navigation, follow hierarchy depth
            return sorted(self.layer_statistics_matrix.keys())

        return list(self.layer_statistics_matrix.keys())

    def get_matrix_statistics(self) -> Dict[str, any]:
        """Get comprehensive statistics about all matrices."""
        return {
            'folder_hierarchy_relationships': len(self.folder_hierarchy_matrix),
            'file_dependency_relationships': len(self.file_dependency_matrix),
            'layer_progression_patterns': len(self.layer_progression_patterns),
            'structural_similarities': len(self.structural_similarity_matrix),
            'query_optimization_paths': len(self.query_optimization_paths),
            'layer_statistics': len(self.layer_statistics_matrix),
            'pattern_recognitions': len(self.pattern_recognition_matrix)
        }


class MatrixSystem:
    """Manages the nested index matrix operations."""

    def __init__(self):
        self.matrices: Dict[str, NestedIndexMatrix] = {}

    def create_matrix(self, name: str, registries: Dict[int, 'LayerRegistry']) -> NestedIndexMatrix:
        """Create a new nested index matrix."""
        matrix = NestedIndexMatrix(layer_registries=registries)
        self.matrices[name] = matrix
        return matrix

    def get_matrix(self, name: str) -> Optional[NestedIndexMatrix]:
        """Get a matrix by name."""
        return self.matrices.get(name)

    def analyze_all_matrices(self) -> Dict[str, Dict[str, any]]:
        """Analyze all matrices in the system."""
        analyses = {}
        for name, matrix in self.matrices.items():
            analyses[name] = {
                'patterns': matrix.analyze_layer_patterns(),
                'statistics': matrix.get_matrix_statistics()
            }
        return analyses