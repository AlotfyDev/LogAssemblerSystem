#!/usr/bin/env python3
"""
File System Registry System
Implements layer registries for folder/file separation and relationships.
Part of the Multi-Tier Object Architecture.
"""

from dataclasses import dataclass, field
from typing import Dict, Set, Optional, Any
from collections import defaultdict

# Import RelationshipAttributes for layer relationships
from filesystem_layers import RelationshipAttributes


@dataclass
class LayerRegistry:
    """Registry for nodes at a specific layer with rich relationship attributes."""
    layer: int
    folders: Dict[str, 'FileSystemNode'] = field(default_factory=dict)  # name -> node
    files: Dict[str, 'FileSystemNode'] = field(default_factory=dict)    # name -> node

    # Cross-mappings within the layer
    folder_to_files: Dict[str, Set[str]] = field(default_factory=lambda: defaultdict(set))  # folder_name -> set of file_names
    file_to_folder: Dict[str, str] = field(default_factory=dict)  # file_name -> parent_folder_name

    # Layer-level relationship attributes
    layer_relationships: 'RelationshipAttributes' = field(default_factory=lambda: RelationshipAttributes())

    # Layer statistics
    folder_count: int = 0
    file_count: int = 0
    total_size: int = 0

    def add_node(self, node):
        """Add a node to this layer registry and update relationships."""
        if node.is_file:
            self.files[node.name] = node
            self.file_count += 1
            self.total_size += node.size_bytes

            # Map file to its parent folder (if in same layer)
            if node.parent and node.parent.absolute_layer == self.layer:
                self.file_to_folder[node.name] = node.parent.name
                self.folder_to_files[node.parent.name].add(node.name)

                # Update node relationships
                node.relationships.parent_folder = str(node.parent.path)
                node.relationships.sibling_files = self.folder_to_files[node.parent.name] - {node.name}

        else:
            self.folders[node.name] = node
            self.folder_count += 1

            # Update folder relationships
            if node.parent and node.parent.absolute_layer == self.layer:
                node.relationships.parent_folder = str(node.parent.path)

            # Update child relationships
            node.relationships.child_files = self.folder_to_files.get(node.name, set())

    def build_relationships(self):
        """Build comprehensive relationships for all nodes in this layer."""
        # Build sibling relationships
        self._build_sibling_relationships()

        # Build community relationships
        self._build_community_relationships()

        # Build layer-level relationships
        self._build_layer_level_relationships()

    def _build_sibling_relationships(self):
        """Build sibling relationships within the layer."""
        # For each folder, identify sibling folders and files
        for folder_name, folder_node in self.folders.items():
            if folder_node.parent and folder_node.parent.absolute_layer == self.layer:
                # Sibling folders (other folders in same parent)
                parent_children = [f for f in self.folders.values()
                                 if f.parent == folder_node.parent and f != folder_node]
                folder_node.relationships.sibling_folders = {str(f.path) for f in parent_children}

        # For each file, sibling files are already set in add_node
        # But we can enhance with additional sibling detection
        for file_name, file_node in self.files.items():
            # Files in same folder are siblings (already set)
            # Could add additional sibling detection based on file characteristics
            pass

    def _build_community_relationships(self):
        """Build community relationships based on similarity."""
        # Group files by extension (community detection)
        files_by_extension = defaultdict(list)
        for file_node in self.files.values():
            if file_node.extension:
                files_by_extension[file_node.extension].append(file_node)

        # Files with same extension are community members
        for ext, file_nodes in files_by_extension.items():
            if len(file_nodes) > 1:
                for file_node in file_nodes:
                    community_files = {str(f.path) for f in file_nodes if f != file_node}
                    file_node.relationships.community_files = community_files

        # Group folders by structure similarity (simplified - could be enhanced)
        folders_by_child_count = defaultdict(list)
        for folder_node in self.folders.values():
            child_count = len(folder_node.relationships.child_files) + len(folder_node.relationships.child_folders)
            folders_by_child_count[child_count].append(folder_node)

        # Folders with similar child counts are community members
        for count, folder_nodes in folders_by_child_count.items():
            if len(folder_nodes) > 1:
                for folder_node in folder_nodes:
                    community_folders = {str(f.path) for f in folder_nodes if f != folder_node}
                    folder_node.relationships.community_folders = community_folders

    def _build_layer_level_relationships(self):
        """Build layer-level relationship attributes."""
        # All files and folders at this layer are layer-level siblings
        all_files = {str(node.path) for node in self.files.values()}
        all_folders = {str(node.path) for node in self.folders.values()}

        # Update layer relationships
        self.layer_relationships.sibling_files = all_files
        self.layer_relationships.sibling_folders = all_folders
        self.layer_relationships.community_files = all_files  # All files in layer are community
        self.layer_relationships.community_folders = all_folders  # All folders in layer are community

    def get_layer_composition(self) -> Dict[str, any]:
        """Get composition statistics for this layer."""
        return {
            'layer': self.layer,
            'folders': self.folder_count,
            'files': self.file_count,
            'total_nodes': self.folder_count + self.file_count,
            'total_size': self.total_size,
            'files_per_folder_avg': self.file_count / max(1, self.folder_count),
            'folder_names': list(self.folders.keys()),
            'file_extensions': list(set(f.extension for f in self.files.values() if f.extension)),
            'relationship_density': self._calculate_relationship_density()
        }

    def _calculate_relationship_density(self) -> float:
        """Calculate relationship density for this layer."""
        total_relationships = 0

        for node in list(self.files.values()) + list(self.folders.values()):
            summary = node.relationships.get_relationship_summary()
            total_relationships += (
                summary['single_layer']['sibling_files_count'] +
                summary['single_layer']['sibling_folders_count'] +
                summary['single_layer']['community_files_count'] +
                summary['single_layer']['community_folders_count'] +
                summary['parent_child']['total_children']
            )

        return total_relationships / max(1, len(self.files) + len(self.folders))

    def find_related_nodes(self, node_name: str) -> Dict[str, any]:
        """Find related nodes within this layer using rich relationships."""
        if node_name in self.files:
            node = self.files[node_name]
            return node.get_file_relationships()
        elif node_name in self.folders:
            node = self.folders[node_name]
            return node.get_folder_relationships()

        return {'type': 'not_found'}

    def get_layer_relationships(self) -> Dict[str, Any]:
        """Get comprehensive layer-level relationship analysis."""
        return {
            'layer_number': self.layer,
            'layer_composition': self.get_layer_composition(),
            'layer_relationships': self.layer_relationships.get_relationship_summary(),
            'sibling_community_analysis': self.layer_relationships.get_sibling_community(),
            'relationship_density': self._calculate_relationship_density(),
            'layer_statistics': {
                'total_nodes': len(self.files) + len(self.folders),
                'relationship_richness': len([n for n in list(self.files.values()) + list(self.folders.values())
                                            if n.relationships.get_relationship_summary()['relationship_types_active'] > 0]),
                'average_relationships_per_node': self._calculate_relationship_density()
            }
        }

    def get_folder_relationships(self) -> Dict[str, list]:
        """Get folder-to-folder relationships within this layer."""
        relationships = {}
        for folder_name in self.folders:
            contained_files = list(self.folder_to_files.get(folder_name, set()))
            relationships[folder_name] = contained_files
        return relationships

    def get_file_clusters(self) -> Dict[str, list]:
        """Get files clustered by parent folder."""
        clusters = {}
        for folder_name in self.folders:
            files = list(self.folder_to_files.get(folder_name, set()))
            if files:
                clusters[folder_name] = files
        return clusters


class RegistrySystem:
    """Manages layer registries and their relationships."""

    def __init__(self):
        self.layer_registries: Dict[int, LayerRegistry] = {}

    def add_layer_registry(self, registry: LayerRegistry):
        """Add a layer registry to the system."""
        self.layer_registries[registry.layer] = registry

    def get_registry(self, layer: int) -> Optional[LayerRegistry]:
        """Get registry for a specific layer."""
        return self.layer_registries.get(layer)

    def get_all_registries(self) -> Dict[int, LayerRegistry]:
        """Get all layer registries."""
        return self.layer_registries

    def find_cross_layer_relationships(self, layer1: int, layer2: int) -> Dict[str, any]:
        """
        Find relationships between two different layers.
        This could be extended to analyze folder hierarchies or file dependencies.
        """
        reg1 = self.get_registry(layer1)
        reg2 = self.get_registry(layer2)

        if not reg1 or not reg2:
            return {'error': 'One or both layers not found'}

        # Simple analysis - folders with same names across layers
        common_folders = set(reg1.folders.keys()) & set(reg2.folders.keys())

        return {
            'layer1': layer1,
            'layer2': layer2,
            'common_folders': list(common_folders),
            'layer1_unique_folders': list(set(reg1.folders.keys()) - common_folders),
            'layer2_unique_folders': list(set(reg2.folders.keys()) - common_folders),
            'relationship_strength': len(common_folders) / max(1, (len(reg1.folders) + len(reg2.folders)) / 2)
        }

    def build_all_relationships(self):
        """Build comprehensive relationships across all registries."""
        # Build intra-layer relationships first
        for registry in self.layer_registries.values():
            registry.build_relationships()

        # Build cross-layer relationships
        self._build_cross_layer_relationships()

        # Build ancestor-descendant matrices
        self._build_ancestor_descendant_matrices()

    def _build_cross_layer_relationships(self):
        """Build relationships between different layers."""
        # For each node, find related nodes in adjacent layers
        for registry in self.layer_registries.values():
            current_layer = registry.layer

            # Check adjacent layers
            for layer_offset in [-1, 1]:  # Previous and next layers
                adjacent_layer = current_layer + layer_offset
                adjacent_registry = self.layer_registries.get(adjacent_layer)

                if adjacent_registry:
                    # Files in current layer related to files in adjacent layer
                    for file_node in registry.files.values():
                        # Find files with similar names or extensions in adjacent layer
                        related_files = set()
                        for adj_file in adjacent_registry.files.values():
                            if (file_node.name == adj_file.name or
                                file_node.extension == adj_file.extension):
                                related_files.add(str(adj_file.path))

                        if related_files:
                            file_node.relationships.related_files_cross_layer[adjacent_layer] = related_files

                    # Similar for folders
                    for folder_node in registry.folders.values():
                        related_folders = set()
                        for adj_folder in adjacent_registry.folders.values():
                            if folder_node.name == adj_folder.name:
                                related_folders.add(str(adj_folder.path))

                        if related_folders:
                            folder_node.relationships.related_folders_cross_layer[adjacent_layer] = related_folders

    def _build_ancestor_descendant_matrices(self):
        """Build ancestor and descendant matrices for all nodes."""
        # This requires traversing the graph structure
        # For now, we'll implement a basic version that traces immediate relationships
        # A full implementation would need access to the complete graph

        for registry in self.layer_registries.values():
            for node in list(registry.files.values()) + list(registry.folders.values()):
                # Build ancestor chain (simplified - would need graph traversal)
                if node.relationships.parent_folder:
                    node.relationships.ancestor_chain = [node.relationships.parent_folder]
                    # Could extend to full ancestor chain with graph access

                # Build descendant matrices (simplified)
                if not node.is_file:  # Folders only
                    # Direct children
                    node.relationships.descendant_files[1] = node.relationships.child_files
                    node.relationships.descendant_folders[1] = node.relationships.child_folders

                    # Could extend to deeper descendants with graph traversal

    def analyze_registry_patterns(self) -> Dict[str, any]:
        """Analyze patterns across all registries with rich relationships."""
        if not self.layer_registries:
            return {}

        patterns = {
            'total_layers': len(self.layer_registries),
            'layer_range': f"{min(self.layer_registries.keys())}-{max(self.layer_registries.keys())}",
            'layer_compositions': {},
            'relationship_patterns': {},
            'cross_layer_relationships': {},
            'ancestor_descendant_patterns': {}
        }

        # Get composition and relationships for each layer
        for layer, registry in self.layer_registries.items():
            patterns['layer_compositions'][layer] = registry.get_layer_composition()
            patterns['relationship_patterns'][layer] = registry.get_layer_relationships()

        # Analyze cross-layer relationships
        layers = sorted(self.layer_registries.keys())
        for i in range(len(layers) - 1):
            layer1, layer2 = layers[i], layers[i + 1]
            patterns['cross_layer_relationships'][f"{layer1}-{layer2}"] = \
                self.find_cross_layer_relationships(layer1, layer2)

        # Analyze ancestor-descendant patterns
        patterns['ancestor_descendant_patterns'] = self._analyze_hierarchical_patterns()

        return patterns

    def _analyze_hierarchical_patterns(self) -> Dict[str, Any]:
        """Analyze hierarchical patterns across all layers."""
        patterns = {
            'total_ancestor_chains': 0,
            'total_descendant_relationships': 0,
            'average_chain_length': 0,
            'layer_hierarchy_depth': {},
            'relationship_density_by_layer': {}
        }

        total_chain_lengths = []

        for registry in self.layer_registries.values():
            layer_hierarchy = {'ancestors': 0, 'descendants': 0, 'relationships': 0}

            for node in list(registry.files.values()) + list(registry.folders.values()):
                # Count ancestor chains
                if node.relationships.ancestor_chain:
                    patterns['total_ancestor_chains'] += 1
                    total_chain_lengths.append(len(node.relationships.ancestor_chain))

                # Count descendant relationships
                total_descendants = sum(len(files) + len(folders)
                                      for files, folders in zip(
                                          node.relationships.descendant_files.values(),
                                          node.relationships.descendant_folders.values()))
                patterns['total_descendant_relationships'] += total_descendants

                layer_hierarchy['ancestors'] += len(node.relationships.ancestor_chain)
                layer_hierarchy['descendants'] += total_descendants
                layer_hierarchy['relationships'] += node.analyze_relationship_density()['total_relationships']

            patterns['layer_hierarchy_depth'][registry.layer] = layer_hierarchy
            patterns['relationship_density_by_layer'][registry.layer] = registry._calculate_relationship_density()

        if total_chain_lengths:
            patterns['average_chain_length'] = sum(total_chain_lengths) / len(total_chain_lengths)

        return patterns