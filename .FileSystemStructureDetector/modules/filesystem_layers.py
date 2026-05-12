#!/usr/bin/env python3
"""
File System Layer System
Implements layer coordinates, keys, and basic layer operations.
Part of the Multi-Tier Object Architecture.
"""

from dataclasses import dataclass, field
from typing import Dict, Optional, List, Any, Set
from pathlib import Path
from collections import defaultdict


@dataclass
class SystemLimits:
    """Dynamic system limits calculated from actual system dimensions."""
    max_traversal_depth: int = field(init=False)
    max_query_complexity: int = field(init=False)
    max_relationship_hops: int = field(init=False)
    max_layer_span: int = field(init=False)
    max_matrix_dimensions: int = field(init=False)

    def __post_init__(self):
        """Initialize with safe defaults - will be updated dynamically."""
        self.max_traversal_depth = 100  # Will be updated based on actual graph depth
        self.max_query_complexity = 1000  # Will be updated based on relationship density
        self.max_relationship_hops = 10  # Will be updated based on graph connectivity
        self.max_layer_span = 50  # Will be updated based on actual layer range
        self.max_matrix_dimensions = 1000  # Will be updated based on matrix sizes

    def update_from_matrix_capacity(self, graph):
        """
        Calculate limits BOUND TO ACTUAL MATRIX SYSTEM CAPACITY.
        True matrix-capacity binding instead of traditional graph metrics.
        """
        if not graph:
            return

        # MATRIX-CAPACITY BOUND CALCULATIONS
        matrix_capacity = self._calculate_matrix_system_capacity(graph)

        # Bind traversal depth to layer registry capacity
        self.max_traversal_depth = matrix_capacity['max_layer_depth']

        # Bind query complexity to relationship matrix capacity
        self.max_query_complexity = matrix_capacity['relationship_matrix_capacity']

        # Bind relationship hops to cross-layer matrix connectivity
        self.max_relationship_hops = matrix_capacity['cross_layer_connectivity']

        # Bind layer span to actual layer registry span
        self.max_layer_span = matrix_capacity['layer_registry_span']

        # Bind matrix dimensions to actual nested matrix capacity
        self.max_matrix_dimensions = matrix_capacity['nested_matrix_capacity']

    def _calculate_matrix_system_capacity(self, graph) -> Dict[str, int]:
        """
        Calculate TRUE matrix system capacity metrics.
        This is the actual capacity of our nested index matrices.
        """
        capacity = {
            'max_layer_depth': 0,
            'relationship_matrix_capacity': 0,
            'cross_layer_connectivity': 0,
            'layer_registry_span': 0,
            'nested_matrix_capacity': 0
        }

        if not graph.registry_system.layer_registries:
            # Fallback to minimal capacity
            return {k: 10 for k in capacity.keys()}

        # Calculate from ACTUAL MATRIX DIMENSIONS
        registries = graph.registry_system.layer_registries
        matrices = graph.matrix_system.matrices

        # 1. Layer depth capacity = number of layer registries
        capacity['max_layer_depth'] = len(registries)

        # 2. Relationship matrix capacity = total relationships across all registries
        total_relationships = 0
        for registry in registries.values():
            # Count all relationship types in this registry
            for node in list(registry.files.values()) + list(registry.folders.values()):
                summary = node.relationships.get_relationship_summary()
                total_relationships += (
                    summary['single_layer']['sibling_files_count'] +
                    summary['single_layer']['sibling_folders_count'] +
                    summary['single_layer']['community_files_count'] +
                    summary['single_layer']['community_folders_count'] +
                    summary['parent_child']['total_children'] +
                    summary['ancestor_descendant']['total_descendant_files'] +
                    summary['ancestor_descendant']['total_descendant_folders'] +
                    summary['cross_layer']['total_cross_layer_files'] +
                    summary['cross_layer']['total_cross_layer_folders']
                )
        capacity['relationship_matrix_capacity'] = max(100, total_relationships)

        # 3. Cross-layer connectivity = number of cross-layer relationship matrices
        total_cross_layer_relationships = 0
        for matrix in matrices.values():
            total_cross_layer_relationships += (
                len(matrix.folder_hierarchy_matrix) +
                len(matrix.file_dependency_matrix)
            )
        capacity['cross_layer_connectivity'] = max(5, total_cross_layer_relationships)

        # 4. Layer registry span = range of layer indices
        if registries:
            layer_indices = list(registries.keys())
            capacity['layer_registry_span'] = max(layer_indices) - min(layer_indices) + 1
        else:
            capacity['layer_registry_span'] = 1

        # 5. Nested matrix capacity = total matrix storage capacity
        matrix_storage_capacity = 0
        for matrix in matrices.values():
            matrix_stats = matrix.get_matrix_statistics()
            matrix_storage_capacity += (
                matrix_stats.get('folder_hierarchy_relationships', 0) +
                matrix_stats.get('file_dependency_relationships', 0) +
                len(matrix.layer_registries) * 100  # Base capacity per registry
            )
        capacity['nested_matrix_capacity'] = max(1000, matrix_storage_capacity)

        return capacity

    def update_from_matrices(self, matrix_system):
        """Update limits based on matrix dimensions."""
        if not matrix_system.matrices:
            return

        # Find the largest matrix dimensions
        max_matrix_size = 0
        for matrix in matrix_system.matrices.values():
            matrix_stats = matrix.get_matrix_statistics()
            matrix_size = (matrix_stats.get('folder_hierarchy_relationships', 0) +
                          matrix_stats.get('file_dependency_relationships', 0))
            max_matrix_size = max(max_matrix_size, matrix_size)

        self.max_matrix_dimensions = min(10000, max_matrix_size * 2)


@dataclass
class TraversalConfiguration:
    """Configuration for graph traversal operations."""
    max_depth: int = field(init=False)
    breadth_first_limit: int = field(init=False)
    safety_buffer: float = 1.5  # Safety multiplier for limits

    def __post_init__(self):
        self.max_depth = 50  # Will be updated dynamically
        self.breadth_first_limit = 1000  # Will be updated dynamically

    def configure_for_graph(self, graph, system_limits: SystemLimits):
        """Configure traversal limits based on graph and system limits."""
        if not graph or not graph.all_nodes:
            return

        # Calculate optimal depth based on graph structure
        max_actual_depth = max((node.depth for node in graph.all_nodes.values()), default=0)
        self.max_depth = min(system_limits.max_traversal_depth,
                           int(max_actual_depth * self.safety_buffer))

        # Calculate breadth-first limit based on branching factor
        avg_children = sum(len(node.children) for node in graph.all_nodes.values()) / len(graph.all_nodes)
        self.breadth_first_limit = min(system_limits.max_query_complexity,
                                     int(avg_children * self.max_depth * self.safety_buffer))


@dataclass
class QueryConfiguration:
    """Configuration for query execution."""
    max_results: int = field(init=False)
    timeout_seconds: float = field(init=False)
    max_parallel_operations: int = field(init=False)
    relationship_hop_limit: int = field(init=False)

    def __post_init__(self):
        self.max_results = 1000  # Will be updated dynamically
        self.timeout_seconds = 30.0  # Will be updated dynamically
        self.max_parallel_operations = 10  # Will be updated dynamically
        self.relationship_hop_limit = 5  # Will be updated dynamically

    def configure_for_complexity(self, graph, system_limits: SystemLimits):
        """Configure query limits based on graph complexity."""
        if not graph or not graph.all_nodes:
            return

        # Scale limits based on relationship density
        total_relationships = sum(
            node.analyze_relationship_density()['total_relationships']
            for node in list(graph.all_nodes.values())[:100]  # Sample for performance
        )
        avg_density = total_relationships / min(100, len(graph.all_nodes)) if graph.all_nodes else 1

        # Adjust limits based on complexity
        complexity_factor = min(5.0, avg_density / 10.0) if avg_density > 0 else 1.0

        self.max_results = min(system_limits.max_query_complexity,
                             int(1000 / complexity_factor))
        self.relationship_hop_limit = min(system_limits.max_relationship_hops,
                                        max(3, int(10 / complexity_factor)))
        self.max_parallel_operations = min(50, max(1, int(20 / complexity_factor)))


@dataclass
class MatrixConfiguration:
    """Configuration for matrix operations."""
    max_dimensions: int = field(init=False)
    relationship_threshold: float = field(init=False)
    pattern_similarity_threshold: float = field(init=False)
    optimization_enabled: bool = True

    def __post_init__(self):
        self.max_dimensions = 1000  # Will be updated dynamically
        self.relationship_threshold = 0.1  # Minimum relationship strength
        self.pattern_similarity_threshold = 0.7  # Pattern similarity threshold

    def configure_for_matrices(self, matrix_system, system_limits: SystemLimits):
        """Configure matrix limits based on actual matrix dimensions."""
        if not matrix_system.matrices:
            return

        # Calculate total matrix dimensions
        total_dimensions = 0
        for matrix in matrix_system.matrices.values():
            stats = matrix.get_matrix_statistics()
            total_dimensions += (stats.get('folder_hierarchy_relationships', 0) +
                               stats.get('file_dependency_relationships', 0))

        self.max_dimensions = min(system_limits.max_matrix_dimensions, total_dimensions * 2)


@dataclass
class SystemConfiguration:
    """Master configuration object containing all system settings."""
    system_limits: SystemLimits = field(default_factory=SystemLimits)
    traversal_config: TraversalConfiguration = field(default_factory=TraversalConfiguration)
    query_config: QueryConfiguration = field(default_factory=QueryConfiguration)
    matrix_config: MatrixConfiguration = field(default_factory=MatrixConfiguration)

    def configure_for_matrix_capacity(self, graph, matrix_system):
        """
        Configure ALL settings BOUND TO MATRIX SYSTEM CAPACITY.
        TRUE matrix-capacity binding - limits calculated from actual matrix dimensions.
        """
        # Update system limits from MATRIX CAPACITY - not traditional graph metrics
        self.system_limits.update_from_matrix_capacity(graph)

        # Configure dependent settings based on matrix capacity
        self._configure_traversal_for_matrix_capacity(graph)
        self._configure_query_for_matrix_capacity(graph)
        self._configure_matrix_for_matrix_capacity(matrix_system)

    def _configure_traversal_for_matrix_capacity(self, graph):
        """Configure traversal limits bound to matrix capacity."""
        # Bind traversal depth to layer registry count
        registry_count = len(graph.registry_system.layer_registries)
        self.traversal_config.max_depth = max(5, min(registry_count * 2,
                                                    self.system_limits.max_traversal_depth))

        # Bind breadth-first limit to relationship matrix capacity
        relationship_capacity = self.system_limits.max_query_complexity
        self.traversal_config.breadth_first_limit = max(100, min(relationship_capacity // 10,
                                                                self.system_limits.max_query_complexity))

    def _configure_query_for_matrix_capacity(self, graph):
        """Configure query limits bound to matrix capacity."""
        # Bind max results to relationship matrix capacity
        self.query_config.max_results = max(50, min(self.system_limits.max_query_complexity // 10,
                                                   self.system_limits.max_query_complexity))

        # Bind relationship hops to cross-layer connectivity
        self.query_config.relationship_hop_limit = max(3, min(self.system_limits.max_relationship_hops,
                                                             self.system_limits.max_relationship_hops))

        # Bind parallel operations to layer registry span
        layer_span = self.system_limits.max_layer_span
        self.query_config.max_parallel_operations = max(1, min(layer_span // 2, 20))

    def _configure_matrix_for_matrix_capacity(self, matrix_system):
        """Configure matrix limits bound to matrix capacity."""
        # Bind matrix dimensions to actual nested matrix capacity
        self.matrix_config.max_dimensions = max(100, min(self.system_limits.max_matrix_dimensions,
                                                        self.system_limits.max_matrix_dimensions))

    def get_traversal_limits(self) -> Dict[str, Any]:
        """Get current traversal limits."""
        return {
            'max_depth': self.traversal_config.max_depth,
            'breadth_first_limit': self.traversal_config.breadth_first_limit,
            'safety_buffer': self.traversal_config.safety_buffer
        }

    def get_query_limits(self) -> Dict[str, Any]:
        """Get current query limits."""
        return {
            'max_results': self.query_config.max_results,
            'timeout_seconds': self.query_config.timeout_seconds,
            'max_parallel_operations': self.query_config.max_parallel_operations,
            'relationship_hop_limit': self.query_config.relationship_hop_limit
        }

    def get_matrix_limits(self) -> Dict[str, Any]:
        """Get current matrix limits."""
        return {
            'max_dimensions': self.matrix_config.max_dimensions,
            'relationship_threshold': self.matrix_config.relationship_threshold,
            'pattern_similarity_threshold': self.matrix_config.pattern_similarity_threshold,
            'optimization_enabled': self.matrix_config.optimization_enabled
        }


@dataclass
class AncestorVector:
    """Powerful ancestor vector/list that serves as layer indicator and pathfinding foundation."""

    # Core ancestor chain - THIS IS THE LAYER INDICATOR!
    ancestors: List[str] = field(default_factory=list)  # Ordered list: [root, parent1, parent2, ..., immediate_parent]

    # Derived layer information from ancestor capacity
    @property
    def layer_depth(self) -> int:
        """Layer depth = length of ancestor vector. THIS IS THE PRIMARY LAYER INDICATOR!"""
        return len(self.ancestors)

    @property
    def root_ancestor(self) -> str:
        """Root ancestor (first in chain)"""
        return self.ancestors[0] if self.ancestors else ""

    @property
    def immediate_parent(self) -> str:
        """Immediate parent (last in chain)"""
        return self.ancestors[-1] if self.ancestors else ""

    def find_common_ancestor(self, other: 'AncestorVector') -> str:
        """Find nearest common ancestor by comparing ancestor vectors."""
        min_len = min(len(self.ancestors), len(other.ancestors))

        for i in range(min_len):
            if self.ancestors[i] != other.ancestors[i]:
                return self.ancestors[i-1] if i > 0 else ""

        # All compared ancestors are common
        return self.ancestors[min_len-1] if min_len > 0 else ""

    def get_ancestor_distance(self, other: 'AncestorVector') -> int:
        """Get distance in ancestor hierarchy between two vectors."""
        common_ancestor_index = -1

        # Find first non-common ancestor
        min_len = min(len(self.ancestors), len(other.ancestors))
        for i in range(min_len):
            if self.ancestors[i] != other.ancestors[i]:
                common_ancestor_index = i - 1
                break
        else:
            # All compared ancestors are common
            common_ancestor_index = min_len - 1

        if common_ancestor_index < 0:
            return max(len(self.ancestors), len(other.ancestors))  # No common ancestor

        # Distance = steps from common ancestor to each node
        distance_to_self = len(self.ancestors) - 1 - common_ancestor_index
        distance_to_other = len(other.ancestors) - 1 - common_ancestor_index

        return distance_to_self + distance_to_other

    def get_branching_point(self, other: 'AncestorVector') -> str:
        """Find exact branching point where paths diverge."""
        min_len = min(len(self.ancestors), len(other.ancestors))

        for i in range(min_len):
            if self.ancestors[i] != other.ancestors[i]:
                return self.ancestors[i-1] if i > 0 else ""

        return ""  # No branching point (identical or one is prefix of other)

    def is_ancestor_of(self, other: 'AncestorVector') -> bool:
        """Check if this vector represents an ancestor of the other."""
        if len(self.ancestors) >= len(other.ancestors):
            return False

        # Check if our ancestor chain is a prefix of theirs
        return self.ancestors == other.ancestors[:len(self.ancestors)]

    def get_relative_depth_from_ancestor(self, ancestor_path: str) -> int:
        """Get relative depth from a specific ancestor in the chain."""
        try:
            ancestor_index = self.ancestors.index(ancestor_path)
            return len(self.ancestors) - 1 - ancestor_index  # Distance from ancestor
        except ValueError:
            return -1  # Ancestor not in chain


@dataclass
class RelationshipAttributes:
    """Relationship attributes for nodes in the layered file system."""

    # ANCESTOR VECTOR - THE POWERFUL LAYER INDICATOR!
    ancestor_vector: AncestorVector = field(default_factory=AncestorVector)

    # Single Layer Level Relationships (Horizontal)
    sibling_files: Set[str] = field(default_factory=set)  # Other files in same folder
    sibling_folders: Set[str] = field(default_factory=set)  # Other folders in same parent
    community_files: Set[str] = field(default_factory=set)  # Files with similar characteristics in layer
    community_folders: Set[str] = field(default_factory=set)  # Folders with similar structures in layer

    # Parent-Child Level Relationships (Vertical)
    parent_folder: str = ""  # Immediate parent folder path (redundant with ancestor_vector, but kept for compatibility)
    child_files: Set[str] = field(default_factory=set)  # Direct child files
    child_folders: Set[str] = field(default_factory=set)  # Direct child folders

    # Ancestor-Descendant Matrices (Multi-layer) - now derived from ancestor vectors
    descendant_files: Dict[int, Set[str]] = field(default_factory=lambda: defaultdict(set))  # Files at each depth
    descendant_folders: Dict[int, Set[str]] = field(default_factory=lambda: defaultdict(set))  # Folders at each depth

    # Cross-layer relationships
    related_files_cross_layer: Dict[int, Set[str]] = field(default_factory=lambda: defaultdict(set))  # Files in other layers
    related_folders_cross_layer: Dict[int, Set[str]] = field(default_factory=lambda: defaultdict(set))  # Folders in other layers

    def get_relationship_summary(self) -> Dict[str, Any]:
        """Get summary of all relationship types."""
        return {
            'single_layer': {
                'sibling_files_count': len(self.sibling_files),
                'sibling_folders_count': len(self.sibling_folders),
                'community_files_count': len(self.community_files),
                'community_folders_count': len(self.community_folders)
            },
            'parent_child': {
                'has_parent': bool(self.parent_folder),
                'child_files_count': len(self.child_files),
                'child_folders_count': len(self.child_folders),
                'total_children': len(self.child_files) + len(self.child_folders)
            },
            'ancestor_descendant': {
                'ancestor_levels': self.ancestor_vector.layer_depth,  # LAYER INDICATOR!
                'descendant_files_depths': len(self.descendant_files),
                'descendant_folders_depths': len(self.descendant_folders),
                'total_descendant_files': sum(len(files) for files in self.descendant_files.values()),
                'total_descendant_folders': sum(len(folders) for folders in self.descendant_folders.values())
            },
            'cross_layer': {
                'related_layers_count': len(set(self.related_files_cross_layer.keys()) |
                                          set(self.related_folders_cross_layer.keys())),
                'total_cross_layer_files': sum(len(files) for files in self.related_files_cross_layer.values()),
                'total_cross_layer_folders': sum(len(folders) for folders in self.related_folders_cross_layer.values())
            }
        }

    def get_sibling_community(self) -> Dict[str, Set[str]]:
        """Get combined sibling and community relationships."""
        return {
            'all_related_files': self.sibling_files | self.community_files,
            'all_related_folders': self.sibling_folders | self.community_folders,
            'pure_siblings_files': self.sibling_files - self.community_files,
            'pure_community_files': self.community_files - self.sibling_files,
            'overlapping_community': self.sibling_files & self.community_files
        }

    def get_hierarchical_depth(self) -> Dict[str, Any]:
        """Get hierarchical depth information."""
        return {
            'ancestor_depth': len(self.ancestor_chain),
            'max_descendant_depth_files': max(self.descendant_files.keys()) if self.descendant_files else 0,
            'max_descendant_depth_folders': max(self.descendant_folders.keys()) if self.descendant_folders else 0,
            'total_hierarchical_span': (max(self.descendant_files.keys()) if self.descendant_files else 0) + len(self.ancestor_chain)
        }


@dataclass
class LayerCoordinates:
    """Spatial coordinates for a node in the layered file system."""
    absolute_layer: int = 0  # Fixed depth from file system root
    relative_layer_cache: Dict[str, int] = field(default_factory=dict)  # Cached relative layers by target
    layer_key_cache: Dict[str, str] = field(default_factory=dict)  # Cached multi-part keys
    spatial_signature: str = ""  # Unique spatial identifier

    def get_relative_layer(self, target_path: str, node_path: Path) -> int:
        """Calculate relative layer from target path to this node."""
        if target_path in self.relative_layer_cache:
            return self.relative_layer_cache[target_path]

        try:
            target = Path(target_path).resolve()
            node_resolved = node_path.resolve()

            # Find common ancestor
            target_parts = target.parts
            node_parts = node_resolved.parts

            min_len = min(len(target_parts), len(node_parts))
            common_depth = 0

            for i in range(min_len):
                if target_parts[i] == node_parts[i]:
                    common_depth += 1
                else:
                    break

            # Calculate relative movement
            up_moves = len(target_parts) - common_depth
            down_moves = len(node_parts) - common_depth
            relative_layer = down_moves - up_moves

        except Exception:
            relative_layer = 0

        self.relative_layer_cache[target_path] = relative_layer
        return relative_layer

    def get_layer_key(self, target_path: str = None, serial: int = 0) -> str:
        """Generate spatial coordinate key."""
        cache_key = f"{target_path or 'none'}_{serial}"
        if cache_key in self.layer_key_cache:
            return self.layer_key_cache[cache_key]

        abs_layer = f"{self.absolute_layer:02d}"
        rel_layer = f"{self.get_relative_layer(target_path or '', Path('.')):+03d}"
        spatial_sig = self.spatial_signature[:8] if self.spatial_signature else "00000000"

        key = f"{serial:04d}_{abs_layer}_{rel_layer}_{spatial_sig}"
        self.layer_key_cache[cache_key] = key
        return key

    def get_spatial_coordinates(self) -> Dict[str, Any]:
        """Get complete spatial positioning information."""
        return {
            'absolute_layer': self.absolute_layer,
            'spatial_signature': self.spatial_signature,
            'coordinate_system': 'layer_based',
            'dimensionality': 2  # absolute + relative dimensions
        }


@dataclass
class FileSystemNode:
    """File or directory node with rich relationship attributes and intrinsic layer coordinates."""
    name: str
    path: Path
    is_file: bool
    size_bytes: int = 0
    extension: str = ""
    parent: Optional['FileSystemNode'] = None
    children: Dict[str, 'FileSystemNode'] = field(default_factory=dict)
    depth: int = 0

    # Intrinsic layer coordinates - spatial metadata
    layer_coords: LayerCoordinates = field(default_factory=LayerCoordinates)

    # Rich relationship attributes - the core of our relationship system
    relationships: RelationshipAttributes = field(default_factory=RelationshipAttributes)

    # ANCESTOR VECTOR PROPERTIES - PRIMARY LAYER INDICATORS
    @property
    def absolute_layer(self) -> int:
        """ABSOLUTE LAYER = LENGTH OF ANCESTOR VECTOR! Primary layer indicator."""
        return self.relationships.ancestor_vector.layer_depth

    @absolute_layer.setter
    def absolute_layer(self, value: int):
        """Set absolute layer by updating ancestor vector length."""
        # This is now derived from ancestor vector, so we update layer_coords for compatibility
        self.layer_coords.absolute_layer = value

    @property
    def ancestor_chain(self) -> List[str]:
        """Full ancestor chain from root to immediate parent."""
        return self.relationships.ancestor_vector.ancestors

    @property
    def layer_from_ancestors(self) -> int:
        """Layer depth derived directly from ancestor vector capacity."""
        return len(self.ancestor_chain)

    @property
    def spatial_signature(self) -> str:
        """Unique spatial identifier based on ancestor vector."""
        if not self.layer_coords.spatial_signature:
            # Generate based on ancestor vector hash and layer
            import hashlib
            ancestors_str = "|".join(self.ancestor_chain + [self.name])
            path_hash = hashlib.md5(ancestors_str.encode()).hexdigest()[:8]
            self.layer_coords.spatial_signature = f"{self.absolute_layer:02d}{path_hash}"
        return self.layer_coords.spatial_signature

    @property
    def full_path(self) -> str:
        return str(self.path)

    @property
    def relative_path(self) -> str:
        """Get relative path from root."""
        if self.parent and hasattr(self.parent, '_root_path'):
            try:
                return str(self.path.relative_to(self.parent._root_path))
            except ValueError:
                return str(self.path)
        return self.name

    # Relationship accessors for different object types
    def get_file_relationships(self) -> Dict[str, Any]:
        """Get file-specific relationship attributes."""
        if not self.is_file:
            return {'error': 'Node is not a file'}

        return {
            'sibling_files': list(self.relationships.sibling_files),
            'parent_folder': self.relationships.parent_folder,
            'community_files': list(self.relationships.community_files),
            'ancestor_chain': self.relationships.ancestor_chain,
            'cross_layer_related_files': dict(self.relationships.related_files_cross_layer),
            'relationship_summary': self.relationships.get_relationship_summary(),
            'sibling_community_analysis': self.relationships.get_sibling_community()
        }

    def get_folder_relationships(self) -> Dict[str, Any]:
        """Get folder-specific relationship attributes."""
        if self.is_file:
            return {'error': 'Node is not a folder'}

        return {
            'sibling_folders': list(self.relationships.sibling_folders),
            'parent_folder': self.relationships.parent_folder,
            'child_files': list(self.relationships.child_files),
            'child_folders': list(self.relationships.child_folders),
            'community_folders': list(self.relationships.community_folders),
            'ancestor_chain': self.relationships.ancestor_chain,
            'descendant_files_by_depth': {k: list(v) for k, v in self.relationships.descendant_files.items()},
            'descendant_folders_by_depth': {k: list(v) for k, v in self.relationships.descendant_folders.items()},
            'cross_layer_related_folders': dict(self.relationships.related_folders_cross_layer),
            'relationship_summary': self.relationships.get_relationship_summary(),
            'hierarchical_depth': self.relationships.get_hierarchical_depth()
        }

    def get_layer_relationships(self, layer_system) -> Dict[str, Any]:
        """Get layer-level relationship attributes for this node."""
        layer_info = layer_system.get_registry(self.absolute_layer)
        if not layer_info:
            return {'error': f'No layer information for layer {self.absolute_layer}'}

        # Get all nodes at this layer
        all_layer_nodes = list(layer_info.files.values()) + list(layer_info.folders.values())

        return {
            'layer_number': self.absolute_layer,
            'layer_composition': layer_info.get_layer_composition(),
            'layer_siblings': [n for n in all_layer_nodes if n != self],
            'layer_relationships': layer_info.find_related_nodes(self.name),
            'layer_statistics': {
                'total_nodes_in_layer': len(all_layer_nodes),
                'files_in_layer': layer_info.file_count,
                'folders_in_layer': layer_info.folder_count,
                'layer_has_parent_relationships': any(n.relationships.parent_folder for n in all_layer_nodes),
                'layer_has_child_relationships': any(n.relationships.child_files or n.relationships.child_folders for n in all_layer_nodes)
            }
        }

    # Spatial coordinate methods
    def get_relative_layer(self, target_path: str) -> int:
        """Get relative layer coordinate from target."""
        return self.layer_coords.get_relative_layer(target_path, self.path)

    def get_layer_key(self, target_path: str = None, serial: int = 0) -> str:
        """Get spatial coordinate key."""
        return self.layer_coords.get_layer_key(target_path, serial)

    def get_spatial_coordinates(self) -> Dict[str, Any]:
        """Get complete spatial positioning metadata."""
        coords = self.layer_coords.get_spatial_coordinates()
        coords.update({
            'path': str(self.path),
            'is_file': self.is_file,
            'depth': self.depth,
            'name': self.name,
            'relationship_summary': self.relationships.get_relationship_summary()
        })
        return coords

    def is_at_layer(self, absolute_layer: int) -> bool:
        """Check if node exists at specific absolute layer."""
        return self.absolute_layer == absolute_layer

    def is_within_relative_layer(self, target_path: str, relative_layer: int) -> bool:
        """Check if node is at specific relative layer from target."""
        return self.get_relative_layer(target_path) == relative_layer

    def get_layer_distance(self, other_node: 'FileSystemNode') -> int:
        """Get layer distance between this node and another."""
        return abs(self.absolute_layer - other_node.absolute_layer)

    def get_spatial_relationship(self, other_node: 'FileSystemNode') -> str:
        """Get spatial relationship description."""
        abs_diff = self.absolute_layer - other_node.absolute_layer
        if abs_diff == 0:
            return "same_layer"
        elif abs_diff > 0:
            return f"deeper_by_{abs_diff}"
        else:
            return f"shallower_by_{abs(abs_diff)}"

    # ANCESTOR VECTOR METHODS - POWERFUL LAYER-BASED OPERATIONS
    def find_common_ancestor_with(self, other_node: 'FileSystemNode') -> str:
        """Find nearest common ancestor using ancestor vectors."""
        return self.relationships.ancestor_vector.find_common_ancestor(other_node.relationships.ancestor_vector)

    def get_ancestor_distance_to(self, other_node: 'FileSystemNode') -> int:
        """Get hierarchical distance using ancestor vectors."""
        return self.relationships.ancestor_vector.get_ancestor_distance(other_node.relationships.ancestor_vector)

    def find_branching_point_with(self, other_node: 'FileSystemNode') -> str:
        """Find exact branching point where ancestor paths diverge."""
        return self.relationships.ancestor_vector.get_branching_point(other_node.relationships.ancestor_vector)

    def is_ancestor_of(self, other_node: 'FileSystemNode') -> bool:
        """Check if this node is an ancestor of the other using ancestor vectors."""
        return self.relationships.ancestor_vector.is_ancestor_of(other_node.relationships.ancestor_vector)

    def get_relative_depth_from_common_ancestor(self, other_node: 'FileSystemNode') -> int:
        """Get relative depth from common ancestor."""
        common_ancestor = self.find_common_ancestor_with(other_node)
        if not common_ancestor:
            return -1

        my_distance = self.relationships.ancestor_vector.get_relative_depth_from_ancestor(common_ancestor)
        other_distance = other_node.relationships.ancestor_vector.get_relative_depth_from_ancestor(common_ancestor)

        return abs(my_distance - other_distance)

    # Relationship analysis methods
    def analyze_relationship_density(self) -> Dict[str, Any]:
        """Analyze the density and complexity of relationships."""
        summary = self.relationships.get_relationship_summary()

        total_relationships = (
            summary['single_layer']['sibling_files_count'] +
            summary['single_layer']['sibling_folders_count'] +
            summary['single_layer']['community_files_count'] +
            summary['single_layer']['community_folders_count'] +
            summary['parent_child']['total_children'] +
            summary['ancestor_descendant']['ancestor_levels'] +
            summary['ancestor_descendant']['total_descendant_files'] +
            summary['ancestor_descendant']['total_descendant_folders'] +
            summary['cross_layer']['total_cross_layer_files'] +
            summary['cross_layer']['total_cross_layer_folders']
        )

        return {
            'total_relationships': total_relationships,
            'relationship_density': total_relationships / max(1, summary['ancestor_descendant']['ancestor_levels'] + 1),
            'relationship_complexity': len([k for k, v in summary.items() if isinstance(v, dict) and any(isinstance(val, (int, list, dict)) and (isinstance(val, (int, list)) and len(val) > 0 if isinstance(val, (list, dict)) else val > 0) for val in v.values())]),
            'relationship_types_active': len([k for k, v in summary.items() if isinstance(v, dict) and any(v.values())])
        }


class LayerSystem:
    """Manages intrinsic layer coordinates and spatial operations."""

    def __init__(self):
        self._spatial_cache: Dict[str, Any] = {}  # Cache for spatial queries

    def assign_layer_coordinates(self, node: FileSystemNode, root_path: Path):
        """Assign intrinsic layer coordinates to a node."""
        # Calculate absolute layer
        node.absolute_layer = self.calculate_absolute_layer(node.path)

        # Generate spatial signature
        _ = node.spatial_signature  # Triggers generation

    def query_by_absolute_layer(self, graph, absolute_layer: int) -> List[FileSystemNode]:
        """O(1) query: Find all nodes at specific absolute layer using intrinsic coordinates."""
        return [node for node in graph.all_nodes.values() if node.is_at_layer(absolute_layer)]

    def query_by_relative_layer(self, graph, target_path: str, relative_layer: int) -> List[FileSystemNode]:
        """Query nodes at specific relative layer from target using intrinsic coordinates."""
        cache_key = f"rel_{target_path}_{relative_layer}"
        if cache_key in self._spatial_cache:
            return self._spatial_cache[cache_key]

        matching_nodes = [
            node for node in graph.all_nodes.values()
            if node.is_within_relative_layer(target_path, relative_layer)
        ]

        # Sort by spatial signature for consistent ordering
        matching_nodes.sort(key=lambda n: n.spatial_signature)
        self._spatial_cache[cache_key] = matching_nodes
        return matching_nodes

    def get_layer_hierarchy_from_target(self, graph, target_path: str, max_radius: int = 3) -> Dict[int, List[FileSystemNode]]:
        """Get spatial hierarchy centered on target using intrinsic coordinates."""
        hierarchy = {}
        for rel_layer in range(-max_radius, max_radius + 1):
            nodes = self.query_by_relative_layer(graph, target_path, rel_layer)
            if nodes:
                hierarchy[rel_layer] = nodes
        return hierarchy

    def find_nodes_in_spatial_range(self, graph, center_node: FileSystemNode,
                                  absolute_range: tuple = None,
                                  relative_range: tuple = None) -> List[FileSystemNode]:
        """
        Find nodes within spatial ranges using intrinsic coordinates.
        absolute_range: (min_layer, max_layer) for absolute positioning
        relative_range: (min_rel, max_rel) relative to center_node
        """
        results = []

        for node in graph.all_nodes.values():
            include_node = True

            # Check absolute layer range
            if absolute_range:
                min_abs, max_abs = absolute_range
                if not (min_abs <= node.absolute_layer <= max_abs):
                    include_node = False

            # Check relative layer range
            if relative_range and include_node:
                min_rel, max_rel = relative_range
                rel_layer = node.get_relative_layer(center_node.full_path)
                if not (min_rel <= rel_layer <= max_rel):
                    include_node = False

            if include_node:
                results.append(node)

        return results

    def get_spatial_neighbors(self, graph, node: FileSystemNode,
                            absolute_distance: int = 1,
                            include_diagonal: bool = False) -> Dict[str, List[FileSystemNode]]:
        """
        Get spatial neighbors using layer coordinates.
        Returns nodes at adjacent absolute layers and same relative positions.
        """
        neighbors = {
            'absolute_shallower': [],  # Same relative, shallower absolute
            'absolute_deeper': [],     # Same relative, deeper absolute
            'relative_closer': [],     # Closer relative layer
            'relative_farther': []     # Farther relative layer
        }

        target_abs = node.absolute_layer

        for other in graph.all_nodes.values():
            if other == node:
                continue

            abs_diff = abs(other.absolute_layer - target_abs)

            # Absolute layer neighbors
            if abs_diff == absolute_distance:
                if other.absolute_layer < target_abs:
                    neighbors['absolute_shallower'].append(other)
                else:
                    neighbors['absolute_deeper'].append(other)

            # Relative layer neighbors (same absolute layer)
            elif abs_diff == 0:
                rel_diff = abs(other.get_relative_layer(node.full_path))
                if rel_diff == 1:
                    if other.get_relative_layer(node.full_path) < 0:
                        neighbors['relative_closer'].append(other)
                    else:
                        neighbors['relative_farther'].append(other)

        return neighbors

    def calculate_spatial_metrics(self, graph) -> Dict[str, Any]:
        """Calculate spatial distribution metrics using intrinsic coordinates."""
        if not graph.all_nodes:
            return {}

        layers = [node.absolute_layer for node in graph.all_nodes.values()]
        unique_layers = set(layers)

        return {
            'total_nodes': len(graph.all_nodes),
            'unique_absolute_layers': len(unique_layers),
            'layer_range': f"{min(unique_layers)}-{max(unique_layers)}",
            'most_populated_layer': max(set(layers), key=layers.count),
            'layer_distribution': {layer: layers.count(layer) for layer in unique_layers},
            'average_layer_depth': sum(layers) / len(layers),
            'spatial_density': len(graph.all_nodes) / len(unique_layers) if unique_layers else 0
        }

    def validate_layer_integrity(self, graph) -> Dict[str, Any]:
        """Validate that layer coordinates are consistent and correct."""
        issues = []
        stats = {'checked_nodes': 0, 'valid_coordinates': 0, 'invalid_coordinates': 0}

        for node in graph.all_nodes.values():
            stats['checked_nodes'] += 1

            # Validate absolute layer matches actual path depth
            expected_abs = self.calculate_absolute_layer(node.path)
            if node.absolute_layer != expected_abs:
                issues.append(f"Node {node.path}: absolute_layer {node.absolute_layer} != expected {expected_abs}")
                stats['invalid_coordinates'] += 1
            else:
                stats['valid_coordinates'] += 1

            # Validate spatial signature format
            if not node.spatial_signature or len(node.spatial_signature) != 10:
                issues.append(f"Node {node.path}: invalid spatial signature '{node.spatial_signature}'")
                stats['invalid_coordinates'] += 1

        return {
            'is_valid': len(issues) == 0,
            'total_issues': len(issues),
            'issues': issues[:10],  # First 10 issues
            'stats': stats
        }

    def calculate_absolute_layer(self, path: Path) -> int:
        """Calculate absolute layer from file system root."""
        try:
            fs_root = Path(path.anchor) if hasattr(path, 'anchor') else Path('/')
            return len(path.relative_to(fs_root).parts)
        except Exception:
            return 0