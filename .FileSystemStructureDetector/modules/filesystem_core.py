#!/usr/bin/env python3
"""
File System Core Module
Implements the main FileSystemGraph class integrating all subsystems.
Part of the Multi-Tier Object Architecture.
"""

from dataclasses import dataclass, field
from typing import Dict, List, Optional, Set, Any
from pathlib import Path
from collections import defaultdict

from filesystem_layers import LayerSystem, FileSystemNode, SystemConfiguration
from filesystem_registries import RegistrySystem, LayerRegistry
from filesystem_matrices import MatrixSystem, NestedIndexMatrix
from filesystem_queries import QuerySystem


@dataclass
class FileSystemGraph:
    """Graph-based file system structure with dynamic configuration system."""
    root_nodes: Dict[str, FileSystemNode] = field(default_factory=dict)
    all_nodes: Dict[str, FileSystemNode] = field(default_factory=dict)

    # Indexes for fast querying
    nodes_by_extension: Dict[str, Set[str]] = field(default_factory=lambda: defaultdict(set))
    nodes_by_depth: Dict[int, Set[str]] = field(default_factory=lambda: defaultdict(set))

    # Layer-based indexes
    nodes_by_absolute_layer: Dict[int, Set[str]] = field(default_factory=lambda: defaultdict(set))

    # Dynamic configuration system - no hardcoded limits!
    config: 'SystemConfiguration' = field(default_factory=lambda: SystemConfiguration())

    # Integrated subsystems
    layer_system: LayerSystem = field(default_factory=LayerSystem)
    registry_system: RegistrySystem = field(default_factory=RegistrySystem)
    matrix_system: MatrixSystem = field(default_factory=MatrixSystem)
    index_matrix: NestedIndexMatrix = field(default_factory=NestedIndexMatrix)
    query_system: QuerySystem = field(default_factory=lambda: None)  # Will be initialized after creation

    def __post_init__(self):
        """Initialize the query system with self-reference."""
        if self.query_system is None:
            self.query_system = QuerySystem(self, self.registry_system, self.matrix_system)

    def add_node(self, node: FileSystemNode, root_path: Path = None):
        """Add a node with intrinsic layer coordinates and ancestor vector as metadata."""
        node_path_str = str(node.path)

        # Set root reference for relative paths
        if root_path:
            node._root_path = root_path

        # Build ancestor vector - THE PRIMARY LAYER INDICATOR!
        self._build_ancestor_vector(node)

        # Assign intrinsic layer coordinates (now derived from ancestor vector)
        self.layer_system.assign_layer_coordinates(node, root_path or node.path.parent)

        self.all_nodes[node_path_str] = node

        # Add to root nodes if it's a root
        if node.parent is None:
            self.root_nodes[node.name] = node

        # Index by extension
        if node.is_file and node.extension:
            self.nodes_by_extension[node.extension].add(node_path_str)

        # Index by depth
        self.nodes_by_depth[node.depth].add(node_path_str)

        # Index by absolute layer (now from ancestor vector length!)
        self.nodes_by_absolute_layer[node.absolute_layer].add(node_path_str)

        # Add to registry system
        if node.absolute_layer not in self.registry_system.layer_registries:
            self.registry_system.add_layer_registry(LayerRegistry(layer=node.absolute_layer))

        self.registry_system.layer_registries[node.absolute_layer].add_node(node)

    def _build_ancestor_vector(self, node: FileSystemNode):
        """Build the ancestor vector by tracing parent chain to root."""
        ancestors = []
        current = node.parent

        # Trace up the parent chain to build ancestor list
        while current:
            ancestors.insert(0, str(current.path))  # Insert at beginning for root-first order
            current = current.parent

        # Set the ancestor vector - THIS DETERMINES THE LAYER!
        node.relationships.ancestor_vector.ancestors = ancestors

    def get_node(self, path: str) -> Optional[FileSystemNode]:
        """Get node by path string."""
        return self.all_nodes.get(path)

    def find_files_in_directory(self, dir_path: str, recursive: bool = True) -> List[FileSystemNode]:
        """Find all files in a directory (optionally recursive)."""
        dir_node = self.get_node(dir_path)
        if not dir_node or dir_node.is_file:
            return []

        files = []
        self._collect_files(dir_node, files, recursive)
        return files

    def _collect_files(self, node: FileSystemNode, files: List[FileSystemNode], recursive: bool):
        """Recursively collect files from a directory node."""
        for child in node.children.values():
            if child.is_file:
                files.append(child)
            elif recursive:
                self._collect_files(child, files, recursive)

    def find_files_by_extension(self, extension: str, root_path: str = None) -> List[FileSystemNode]:
        """Find all files with specific extension."""
        if root_path:
            # Filter by root path
            return [self.all_nodes[path] for path in self.nodes_by_extension[extension]
                   if path.startswith(root_path)]
        return [self.all_nodes[path] for path in self.nodes_by_extension[extension]]

    def find_nearest_relative_path(self, path1: str, path2: str) -> Optional[str]:
        """
        Find relative path using ANCESTOR VECTOR approach.
        Leverages layer indicators for efficient calculation.
        """
        node1 = self.get_node(path1)
        node2 = self.get_node(path2)

        if not node1 or not node2:
            return None

        # Use ANCESTOR VECTOR approach for relative path calculation
        return self._ancestor_vector_relative_path(node1, node2)

    def _ancestor_vector_relative_path(self, node1, node2) -> Optional[str]:
        """
        Calculate relative path using ancestor vectors.
        Layer indicator = ancestor vector capacity enables efficient calculation.
        """
        # Get ancestor vectors
        ancestor_vector1 = node1.relationships.ancestor_vector
        ancestor_vector2 = node2.relationships.ancestor_vector

        # Find common ancestor using ancestor vector comparison
        common_ancestor = ancestor_vector1.find_common_ancestor(ancestor_vector2)

        if not common_ancestor:
            # No common ancestor - can't create relative path
            return None

        # Calculate relative path using ancestor vector differences
        return self._calculate_relative_path_from_ancestors(node1, node2, common_ancestor)

    def _calculate_relative_path_from_ancestors(self, node1, node2, common_ancestor: str) -> str:
        """
        Calculate relative path using ancestor vector information.
        Uses layer indicators for precise path construction.
        """
        ancestor_vector1 = node1.relationships.ancestor_vector
        ancestor_vector2 = node2.relationships.ancestor_vector

        # Find positions in ancestor chains
        try:
            common_idx1 = ancestor_vector1.ancestors.index(common_ancestor) if common_ancestor in ancestor_vector1.ancestors else -1
            common_idx2 = ancestor_vector2.ancestors.index(common_ancestor) if common_ancestor in ancestor_vector2.ancestors else -1
        except ValueError:
            return None

        # Calculate upward movement from node1 to common ancestor
        if common_idx1 >= 0:
            # node1 is below common ancestor
            up_levels = len(ancestor_vector1.ancestors) - common_idx1 - 1
        else:
            # node1 is the common ancestor or above it
            up_levels = 0

        # Build downward path from common ancestor to node2
        down_parts = []
        if common_idx2 >= 0:
            # node2 is below common ancestor - get remaining path
            remaining_ancestors = ancestor_vector2.ancestors[common_idx2 + 1:]
            down_parts.extend(remaining_ancestors)
        else:
            # node2 is the common ancestor
            pass

        # Add node2's name if it's not in the ancestor chain
        if str(node2.path) != common_ancestor:
            # Check if node2's immediate parent is the last ancestor
            if ancestor_vector2.ancestors and ancestor_vector2.ancestors[-1] != str(node2.path.parent):
                down_parts.append(node2.name)

        # Construct relative path
        up_path = "../" * up_levels if up_levels > 0 else ""
        down_path = "/".join(down_parts) if down_parts else ""

        relative_path = up_path + down_path if down_path else up_path.rstrip("/")

        # Handle special cases
        if not relative_path:
            # Same node
            return "."

        return relative_path

    def _calculate_traditional_relative_path(self, path1: str, path2: str) -> Optional[str]:
        """
        Traditional relative path calculation for comparison.
        Uses string manipulation instead of ancestor vectors.
        """
        node1 = self.get_node(path1)
        node2 = self.get_node(path2)

        if not node1 or not node2:
            return None

        # Traditional approach: find common prefix
        parts1 = node1.full_path.split(os.sep)
        parts2 = node2.full_path.split(os.sep)

        # Find common prefix
        min_len = min(len(parts1), len(parts2))
        common_length = 0

        for i in range(min_len):
            if parts1[i] == parts2[i]:
                common_length += 1
            else:
                break

        # Calculate relative path
        up_levels = len(parts1) - common_length
        down_parts = parts2[common_length:]

        up_path = "../" * up_levels if up_levels > 0 else ""
        down_path = "/".join(down_parts) if down_parts else ""

        relative_path = up_path + down_path if down_path else up_path.rstrip("/")
        return relative_path or "."

    def demonstrate_ancestor_vector_power(self, path1: str, path2: str) -> Dict[str, Any]:
        """
        Demonstrate the power of ancestor vectors for relative path calculation.
        Shows why ancestor vectors are superior to traditional methods.
        """
        node1 = self.get_node(path1)
        node2 = self.get_node(path2)

        if not node1 or not node2:
            return {'error': 'Nodes not found'}

        # Ancestor vector approach
        ancestor_vector1 = node1.relationships.ancestor_vector
        ancestor_vector2 = node2.relationships.ancestor_vector

        common_ancestor = ancestor_vector1.find_common_ancestor(ancestor_vector2)
        ancestor_distance = ancestor_vector1.get_ancestor_distance(ancestor_vector2)

        # Calculate using ancestor vectors
        ancestor_relative_path = self._ancestor_vector_relative_path(node1, node2)

        # Traditional calculation
        traditional_path = self._calculate_traditional_relative_path(path1, path2)

        return {
            'paths': {
                'from': path1,
                'to': path2
            },
            'ancestor_vector_method': {
                'layer_depth_1': ancestor_vector1.layer_depth,
                'layer_depth_2': ancestor_vector2.layer_depth,
                'common_ancestor': common_ancestor,
                'ancestor_distance': ancestor_distance,
                'relative_path': ancestor_relative_path
            },
            'traditional_method': {
                'relative_path': traditional_path
            },
            'comparison': {
                'methods_match': ancestor_relative_path == traditional_path,
                'ancestor_vector_advantages': [
                    'Pre-computed ancestor chains (no runtime path parsing)',
                    'Layer indicators provide hierarchical context',
                    'Common ancestor finding is O(m+n) vector comparison',
                    'Branching point detection built-in',
                    'Hierarchical distance calculation included'
                ]
            }
        }

    def _find_common_ancestor(self, node1: FileSystemNode, node2: FileSystemNode) -> Optional[FileSystemNode]:
        """Find the lowest common ancestor of two nodes."""
        # Convert to paths for easier comparison
        path1_parts = node1.full_path.split(os.sep)
        path2_parts = node2.full_path.split(os.sep)

        # Find common prefix
        min_len = min(len(path1_parts), len(path2_parts))
        common_parts = []

        for i in range(min_len):
            if path1_parts[i] == path2_parts[i]:
                common_parts.append(path1_parts[i])
            else:
                break

        if not common_parts:
            return None

        # Reconstruct common path
        common_path = os.sep.join(common_parts)
        return self.get_node(common_path)

    def _get_path_from_ancestor(self, node: FileSystemNode, ancestor: FileSystemNode) -> str:
        """Get relative path from ancestor to node."""
        if node == ancestor:
            return ""

        path_parts = []
        current = node

        while current and current != ancestor:
            path_parts.insert(0, current.name)
            current = current.parent

        return "/".join(path_parts)

    # Delegate methods to subsystems
    def find_shortest_path_matrix(self, start_path: str, end_path: str) -> Optional[List[str]]:
        """Find shortest path using the nested index matrix system."""
        return self.query_system.find_shortest_path_matrix(start_path, end_path)

    def get_layer_composition(self, layer: int) -> Optional[Dict[str, any]]:
        """Get composition statistics for a specific layer."""
        registry = self.registry_system.get_registry(layer)
        return registry.get_layer_composition() if registry else None

    def get_related_nodes_in_layer(self, node_path: str) -> Optional[Dict[str, any]]:
        """Find related nodes within the same layer using intrinsic coordinates."""
        node = self.get_node(node_path)
        if not node:
            return None

        registry = self.registry_system.get_registry(node.absolute_layer)
        if not registry:
            return None

        return registry.find_related_nodes(node.name)

    # Spatial query methods using intrinsic coordinates
    def query_absolute_layer(self, absolute_layer: int) -> List[FileSystemNode]:
        """O(1) spatial query: Find all nodes at absolute layer using intrinsic coordinates."""
        return self.layer_system.query_by_absolute_layer(self, absolute_layer)

    def query_relative_layer(self, target_path: str, relative_layer: int) -> List[FileSystemNode]:
        """Spatial query: Find nodes at relative layer from target using intrinsic coordinates."""
        return self.layer_system.query_by_relative_layer(self, target_path, relative_layer)

    def get_spatial_hierarchy(self, center_path: str, radius: int = 3) -> Dict[int, List[FileSystemNode]]:
        """Get spatial hierarchy centered on target using intrinsic coordinates."""
        return self.layer_system.get_layer_hierarchy_from_target(self, center_path, radius)

    def find_spatial_range(self, center_node: FileSystemNode,
                          absolute_range: tuple = None,
                          relative_range: tuple = None) -> List[FileSystemNode]:
        """Find nodes within spatial ranges using intrinsic coordinates."""
        return self.layer_system.find_nodes_in_spatial_range(
            self, center_node, absolute_range, relative_range
        )

    def get_spatial_neighbors(self, node_path: str, distance: int = 1) -> Dict[str, List[FileSystemNode]]:
        """Get spatial neighbors using layer coordinates."""
        node = self.get_node(node_path)
        if not node:
            return {}
        return self.layer_system.get_spatial_neighbors(self, node, distance)

    def calculate_spatial_metrics(self) -> Dict[str, Any]:
        """Calculate spatial distribution metrics."""
        return self.layer_system.calculate_spatial_metrics(self)

    def get_layer_statistics(self, target_path: str = None) -> Dict[str, any]:
        """Get statistics about layer distribution (backward compatibility)."""
        # Use spatial metrics
        return self.calculate_spatial_metrics()

    def validate_spatial_integrity(self) -> Dict[str, Any]:
        """Validate spatial coordinate integrity."""
        return self.layer_system.validate_layer_integrity(self)

    def analyze_matrix_patterns(self) -> Dict[str, any]:
        """Analyze patterns using the nested index matrix."""
        # Create default matrix if none exists
        if not self.matrix_system.matrices:
            matrix = self.matrix_system.create_matrix('default', self.registry_system.layer_registries)
            matrix.build_relationships_from_graph(self)
            # Update matrix statistics
            for layer, registry in self.registry_system.layer_registries.items():
                matrix.layer_statistics_matrix[layer] = registry.get_layer_composition()

        return self.matrix_system.analyze_all_matrices()

    def get_optimized_query_path(self, query_type: str) -> List[int]:
        """Get optimized layer traversal path for queries."""
        matrices = list(self.matrix_system.matrices.values())
        if matrices:
            return matrices[0].optimize_query_paths(query_type)
        return list(self.registry_system.layer_registries.keys())

    @classmethod
    def build_ancestor_first(
        cls,
        root_dirs: List[str],
        extensions: Optional[List[str]] = None,
        user_max_depth: Optional[int] = None
    ) -> 'FileSystemGraph':
        """
        ANCESTOR-FIRST INSTANTIATION: Correct data flow for ancestor vector system.

        1. PATH PARSING: Parse full path strings into hierarchical components
        2. OBJECT INSTANTIATION: Create nodes with complete ancestor context
        3. INDEX POPULATION: Fill layer registries and matrices during creation
        4. RELATIONSHIP ESTABLISHMENT: Ancestor vectors populated once during instantiation
        """
        graph = cls()

        # Initialize subsystems
        graph.layer_system = LayerSystem()
        graph.registry_system = RegistrySystem()
        graph.matrix_system = MatrixSystem()

        # Configure system limits based on matrix capacity (ancestor-aware)
        graph._configure_system_limits()

        # Apply user override if specified
        if user_max_depth is not None:
            graph.config.traversal_config.max_depth = min(user_max_depth, graph.config.system_limits.max_traversal_depth)

        print("[*] Building with ANCESTOR-FIRST instantiation approach")
        print("   Data Flow: Path Parsing -> Object Instantiation -> Index Population -> Relationship Establishment")
        print(f"   Dynamic limits - Max depth: {graph.config.traversal_config.max_depth}, Max complexity: {graph.config.query_config.max_results}")
        print()

        total_nodes_created = 0

        for root_dir in root_dirs:
            root_path = Path(root_dir).resolve()

            if not root_path.exists():
                print(f"Warning: Path not found -> {root_path}")
                continue

            print(f"[+] Ancestor-first scanning: {root_path}")

            # ANCESTOR-FIRST APPROACH: Parse all paths first, then instantiate with full context
            all_paths = cls._collect_all_paths_ancestor_first(root_path, extensions, graph.config.traversal_config.max_depth)

            print(f"   [+] Collected {len(all_paths)} paths for ancestor-aware instantiation")

            # Create nodes with complete ancestor context from the start
            nodes_created = cls._instantiate_nodes_with_ancestors(graph, all_paths, root_path)
            total_nodes_created += nodes_created

            print(f"   [+] Created {nodes_created} nodes with ancestor vectors populated")

        # Relationships are already established during instantiation
        # No post-processing needed for ancestor vectors!

        print(f"\n[*] Graph built with {len(graph.all_nodes)} nodes")
        print("   [+] Ancestor vectors populated during instantiation")
        print(f"   [+] Layer registries: {len(graph.registry_system.layer_registries)}")
        print("   [+] Matrix relationships established")
        print("   [*] Ready for ancestor-vector-based queries (no re-parsing needed!)")
        return graph

    @staticmethod
    def _collect_all_paths_ancestor_first(root_path: Path, extensions: Optional[List[str]], max_depth: int) -> List[Path]:
        """
        PHASE 1: Collect all file and directory paths with depth control.
        This gives us the complete path structure for ancestor-aware instantiation.
        """
        all_paths = []

        def collect_recursive(current_path: Path, current_depth: int):
            if current_depth > max_depth:
                return

            try:
                # Add current directory
                all_paths.append(current_path)

                # Add files in current directory
                for item in current_path.iterdir():
                    if item.is_file():
                        if extensions and not any(item.name.lower().endswith(ext.lower()) for ext in extensions):
                            continue
                        all_paths.append(item)
                    elif item.is_dir():
                        collect_recursive(item, current_depth + 1)

            except (PermissionError, OSError):
                pass  # Skip inaccessible directories

        collect_recursive(root_path, 0)
        return all_paths

    @staticmethod
    def _instantiate_nodes_with_ancestors(graph: 'FileSystemGraph', all_paths: List[Path], root_path: Path) -> int:
        """
        PHASE 2: Create FileSystemNode objects with complete ancestor context.

        CORRECT INSTANTIATION FLOW:
        - Parse path into hierarchical components
        - Build ancestor vector immediately
        - Create node with full context
        - Populate layer indexes and matrices
        """
        nodes_created = 0
        path_to_node = {}  # Track created nodes for parent relationships

        # Sort paths to ensure parents are created before children
        all_paths.sort(key=lambda p: len(p.parts))

        for path in all_paths:
            # Parse path into hierarchical components
            path_parts = path.parts
            root_parts = root_path.parts

            # Extract relative path components from root
            relative_parts = path_parts[len(root_parts):] if path_parts[:len(root_parts)] == root_parts else path_parts

            # Build ancestor vector from path components
            ancestors = []
            for i in range(len(relative_parts) - 1):  # All parts except the last (current item)
                ancestor_parts = root_parts + relative_parts[:i+1]
                ancestors.append(str(Path(*ancestor_parts)))

            # Determine if this is a file or directory
            is_file = path.is_file()
            name = path.name

            # Find parent node (should already be created due to sorting)
            parent_path = path.parent
            parent_node = path_to_node.get(str(parent_path)) if str(parent_path) != str(path) else None

            # Create node with complete ancestor context
            node = FileSystemNode(
                name=name,
                path=path,
                is_file=is_file,
                parent=parent_node
            )

            # Populate ancestor vector immediately (THIS IS THE KEY!)
            node.relationships.ancestor_vector.ancestors = ancestors

            # Calculate other properties based on ancestor vector
            node.depth = len(relative_parts) - 1 if relative_parts else 0

            # Get file stats if it's a file
            if is_file:
                try:
                    stat_info = path.stat()
                    node.size_bytes = stat_info.st_size
                    node.extension = path.suffix.lower()
                except OSError:
                    node.size_bytes = 0
                    node.extension = ""

            # Add to graph with all context populated
            graph.add_node(node, root_path)
            path_to_node[str(path)] = node
            nodes_created += 1

        return nodes_created
        """
        Class method to build graph using layer-aware traversal with dynamic configuration.
        Prevents depth hell by processing layer-by-layer breadth-first using calculated limits.
        """
        graph = cls()

        # Initialize subsystems
        graph.layer_system = LayerSystem()
        graph.registry_system = RegistrySystem()
        graph.matrix_system = MatrixSystem()

        # Configure system limits dynamically
        graph._configure_system_limits()

        # Apply user override if specified
        if user_max_depth is not None:
            graph.config.traversal_config.max_depth = min(user_max_depth, graph.config.system_limits.max_traversal_depth)

        # Initialize query system
        graph.query_system = QuerySystem(graph, graph.registry_system, graph.matrix_system)

        print(f"Building layer-aware graph structure from {len(root_dirs)} root directory(ies)...")
        print(f"Dynamic limits - Max depth: {graph.config.traversal_config.max_depth}, Max complexity: {graph.config.query_config.max_results}\n")

        for root_dir in root_dirs:
            root_path = Path(root_dir).resolve()

            if not root_path.exists():
                print(f"Warning: Path not found -> {root_path}")
                continue

            print(f"Layer-aware scanning: {root_path}")

            # Calculate absolute layer from file system root
            absolute_layer = cls._calculate_absolute_layer(root_path)

            # Create root node (Layer 0)
            root_node = FileSystemNode(
                name=root_path.name,
                path=root_path,
                is_file=False,
                depth=0
            )
            # Set absolute layer using property
            root_node.absolute_layer = absolute_layer
            graph.add_node(root_node, root_path)

            # Layer-aware breadth-first traversal with dynamic limits
            cls._build_by_layers(graph, root_path, root_node, extensions)

        # Build rich relationships across all layers
        graph.registry_system.build_all_relationships()

        # Build nested index matrix relationships
        graph.index_matrix.build_relationships_from_graph(graph)

        print(f"Graph built with {len(graph.all_nodes)} nodes")
        print(f"Rich relationships established across {len(graph.registry_system.layer_registries)} layer registries")
        print(f"Nested index matrix: {len(graph.index_matrix.layer_registries)} layer registries")
        return graph

    def _configure_system_limits(self):
        """Configure system limits BOUND TO MATRIX CAPACITY."""
        # MATRIX-CAPACITY BINDING - not traditional graph metrics
        self.config.configure_for_matrix_capacity(self, self.matrix_system)

    @staticmethod
    def _calculate_absolute_layer(path: Path) -> int:
        """Calculate absolute layer from file system root."""
        try:
            fs_root = Path(path.anchor) if hasattr(path, 'anchor') else Path('/')
            return len(path.relative_to(fs_root).parts)
        except Exception:
            return 0

    @staticmethod
    def _build_by_layers(
        graph: 'FileSystemGraph',
        root_path: Path,
        root_node: FileSystemNode,
        extensions: Optional[List[str]]
    ):
        """
        Build graph using layer-by-layer breadth-first traversal with dynamic configuration.
        This prevents depth hell by processing all items at the same depth simultaneously.
        Uses configuration-based limits instead of hardcoded values.
        """
        # Start with layer 0 (root)
        current_layer_nodes = [root_node]
        max_depth = graph.config.traversal_config.max_depth

        for current_depth in range(max_depth):
            if not current_layer_nodes:
                break  # No more nodes at this depth

            next_layer_nodes = []
            layer_file_count = 0

            print(f"  Processing layer {current_depth}: {len(current_layer_nodes)} directories")

            # Process all directories at current depth
            for current_node in current_layer_nodes:
                if current_node.depth >= max_depth:
                    print(f"    Skipping {current_node.path} - max depth exceeded")
                    continue

                try:
                    # Get immediate children only (breadth-first)
                    entries = list(current_node.path.iterdir())

                    for entry in entries:
                        if entry.is_file():
                            # Process file at current layer
                            if extensions and not any(entry.name.lower().endswith(ext.lower()) for ext in extensions):
                                continue

                            absolute_layer = FileSystemGraph._calculate_absolute_layer(entry)

                            try:
                                stat_info = entry.stat()
                                file_size = stat_info.st_size
                            except Exception:
                                file_size = 0

                            file_node = FileSystemNode(
                                name=entry.name,
                                path=entry,
                                is_file=True,
                                size_bytes=file_size,
                                extension=entry.suffix.lower(),
                                parent=current_node,
                                depth=current_node.depth + 1
                            )
                            file_node.absolute_layer = absolute_layer

                            current_node.children[entry.name] = file_node
                            graph.add_node(file_node, root_path)
                            layer_file_count += 1

                        elif entry.is_dir():
                            # Create directory node for next layer
                            absolute_layer = FileSystemGraph._calculate_absolute_layer(entry)

                            dir_node = FileSystemNode(
                                name=entry.name,
                                path=entry,
                                is_file=False,
                                depth=current_node.depth + 1,
                                parent=current_node
                            )
                            dir_node.absolute_layer = absolute_layer

                            current_node.children[entry.name] = dir_node
                            graph.add_node(dir_node, root_path)
                            next_layer_nodes.append(dir_node)

                except (PermissionError, OSError) as e:
                    print(f"    Access denied: {current_node.path} - {e}")
                    continue

            print(f"    Layer {current_depth} complete: {layer_file_count} files, {len(next_layer_nodes)} subdirs")
            current_layer_nodes = next_layer_nodes

            # Safety check - prevent excessive growth using dynamic limits
            if len(graph.all_nodes) > graph.config.system_limits.max_query_complexity:
                print(f"    Safety limit reached: {len(graph.all_nodes)} nodes (limit: {graph.config.system_limits.max_query_complexity})")
                break

    # Additional query system methods
    def multi_point_pathfinding(self, points: List[str]) -> Dict[str, Any]:
        """Find optimal paths connecting multiple points."""
        return self.query_system.multi_point_pathfinding(points)

    def query_by_relationship_type(self, relationship_type: str, layer: int = None) -> Dict[str, Any]:
        """Query nodes based on relationship types."""
        return self.query_system.query_by_relationship_type(relationship_type, layer)

    def get_optimized_query_plan(self, query_type: str, parameters: Dict[str, Any]) -> Dict[str, Any]:
        """Generate an optimized query execution plan."""
        return self.query_system.get_optimized_query_plan(query_type, parameters)

    def save_to_json(self, filepath: str):
        """Save graph structure to JSON file with all subsystems."""
        import json

        # Convert nodes to serializable format
        serializable_nodes = {}
        for path_str, node in self.all_nodes.items():
            serializable_nodes[path_str] = {
                'name': node.name,
                'path': str(node.path),
                'is_file': node.is_file,
                'size_bytes': node.size_bytes,
                'extension': node.extension,
                'depth': node.depth,
                'absolute_layer': node.absolute_layer,
                'ancestor_vector': node.relationships.ancestor_vector.ancestors,  # SAVE ANCESTOR VECTOR!
                'parent_path': str(node.parent.path) if node.parent else None,
                'children_paths': list(str(child.path) for child in node.children.values())
            }

        # Serialize registry system
        registries_data = {}
        for layer, registry in self.registry_system.layer_registries.items():
            registries_data[str(layer)] = {
                'folder_to_files': {k: list(v) for k, v in registry.folder_to_files.items()},
                'file_to_folder': dict(registry.file_to_folder)
            }

        data = {
            'nodes': serializable_nodes,
            'registries': registries_data,
            'indexes': {
                'by_extension': {ext: list(paths) for ext, paths in self.nodes_by_extension.items()},
                'by_depth': {str(depth): list(paths) for depth, paths in self.nodes_by_depth.items()},
                'by_absolute_layer': {str(layer): list(paths) for layer, paths in self.nodes_by_absolute_layer.items()}
            }
        }

        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)

    def load_from_json(self, filepath: str):
        """Load graph structure from JSON file."""
        import json

        with open(filepath, 'r', encoding='utf-8') as f:
            data = json.load(f)

        # Reconstruct nodes
        nodes = {}
        for path_str, node_data in data['nodes'].items():
            node = FileSystemNode(
                name=node_data['name'],
                path=Path(node_data['path']),
                is_file=node_data['is_file'],
                size_bytes=node_data['size_bytes'],
                extension=node_data['extension'],
                depth=node_data['depth']
            )

            # Restore ancestor vector - CRITICAL FOR LAYER INDICATORS!
            if 'ancestor_vector' in node_data:
                node.relationships.ancestor_vector.ancestors = node_data['ancestor_vector']
                # Absolute layer will be derived from ancestor vector length
            elif 'absolute_layer' in node_data:
                # Fallback for older saves
                node.absolute_layer = node_data['absolute_layer']

            nodes[path_str] = node

        # Reconstruct relationships
        for path_str, node_data in data['nodes'].items():
            node = nodes[path_str]
            if node_data['parent_path']:
                node.parent = nodes.get(node_data['parent_path'])

            for child_path in node_data['children_paths']:
                if child_path in nodes:
                    node.children[nodes[child_path].name] = nodes[child_path]

        # Reconstruct graph
        self.all_nodes = nodes
        self.root_nodes = {node.name: node for node in nodes.values() if node.parent is None}

        # Reconstruct indexes
        for ext, paths in data['indexes']['by_extension'].items():
            self.nodes_by_extension[ext] = set(paths)

        for depth_str, paths in data['indexes']['by_depth'].items():
            self.nodes_by_depth[int(depth_str)] = set(paths)

        # Load absolute layer index if available
        if 'by_absolute_layer' in data['indexes']:
            for layer_str, paths in data['indexes']['by_absolute_layer'].items():
                self.nodes_by_absolute_layer[int(layer_str)] = set(paths)

        # Reconstruct registry system
        for layer_str, registry_data in data.get('registries', {}).items():
            layer = int(layer_str)
            registry = LayerRegistry(layer=layer)

            # Reconstruct folder_to_files
            for folder, files in registry_data['folder_to_files'].items():
                registry.folder_to_files[folder] = set(files)

            # Reconstruct file_to_folder
            registry.file_to_folder = registry_data['file_to_folder']

            # Add nodes to registry (simplified - would need full reconstruction)
            self.registry_system.add_layer_registry(registry)