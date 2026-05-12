#!/usr/bin/env python3
"""
Directory Tree to CSV Generator with Graph-Based Structure
Creates a detailed CSV file with file information and Excel hyperlinks.
Features in-memory graph structure for advanced querying and pathfinding.
All comments are in English as requested.
"""

import os
import csv
import argparse
import json
import pickle
from datetime import datetime
from pathlib import Path
from typing import List, Optional, Dict, Set, Tuple
from dataclasses import dataclass, field
from collections import defaultdict


# FileSystemNode and other classes are now imported from modules

# Import modular components
import sys
import os

# Add the modules directory to Python path
modules_path = os.path.join(os.path.dirname(__file__), 'modules')
sys.path.insert(0, modules_path)

# Import the modular components
from filesystem_core import FileSystemGraph, FileSystemNode
from filesystem_layers import LayerSystem
from filesystem_registries import RegistrySystem
from filesystem_matrices import MatrixSystem


def get_file_size(file_path: Path) -> str:
    """Return human-readable file size."""
    try:
        size_bytes = file_path.stat().st_size
        for unit in ['B', 'KB', 'MB', 'GB']:
            if size_bytes < 1024:
                return f"{size_bytes:.1f} {unit}"
            size_bytes /= 1024
        return f"{size_bytes:.1f} TB"
    except Exception:
        return "N/A"


def build_filesystem_graph_ancestor_first(
    root_dirs: List[str],
    extensions: Optional[List[str]] = None,
    user_max_depth: Optional[int] = None
) -> FileSystemGraph:
    """
    Build graph using ANCESTOR-FIRST instantiation approach.

    CORRECT DATA FLOW:
    1. Parse path strings into hierarchical components
    2. Create FileSystemNode objects with complete ancestor context
    3. Populate layer indexes and matrices during instantiation
    4. Establish relationships once during creation (not reconstruction)

    Args:
        root_dirs: List of root directories to scan
        extensions: List of extensions to include (optional)
        user_max_depth: User-specified max depth (optional)

    Returns:
        FileSystemGraph: Graph with ancestor vectors populated during instantiation
    """
    return FileSystemGraph.build_ancestor_first(root_dirs, extensions, user_max_depth)


def build_filesystem_graph(
    root_dirs: List[str],
    extensions: Optional[List[str]] = None
) -> FileSystemGraph:
    """
    Build a graph-based representation of the file system structure.

    Args:
        root_dirs: List of root directories to scan
        extensions: List of extensions to include (optional)

    Returns:
        FileSystemGraph: Graph structure with nodes and indexes
    """
    graph = FileSystemGraph()

    print(f"Building graph structure from {len(root_dirs)} root directory(ies)...\n")

    for root_dir in root_dirs:
        root_path = Path(root_dir).resolve()

        if not root_path.exists():
            print(f"Warning: Path not found -> {root_path}")
            continue

        print(f"Scanning: {root_path}")

        # Calculate absolute layer from file system root
        try:
            # Get the actual file system root (drive letter on Windows, / on Unix)
            fs_root = Path(root_path.anchor) if hasattr(root_path, 'anchor') else Path('/')
            absolute_layer = len(root_path.relative_to(fs_root).parts)
        except Exception:
            absolute_layer = 0

        # Create root node
        root_node = FileSystemNode(
            name=root_path.name,
            path=root_path,
            is_file=False,
            depth=0,
            absolute_layer=absolute_layer
        )
        graph.add_node(root_node, root_path)

        # Walk directory tree and build graph
        for dirpath, dirnames, filenames in os.walk(root_path):
            current_path = Path(dirpath)

            # Get or create current directory node
            if str(current_path) == str(root_path):
                current_node = root_node
            else:
                current_node = graph.get_node(str(current_path))
                if not current_node:
                    # Create intermediate directory node
                    rel_path = current_path.relative_to(root_path)
                    depth = len(rel_path.parts)

                    # Calculate absolute layer
                    try:
                        fs_root = Path(current_path.anchor) if hasattr(current_path, 'anchor') else Path('/')
                        absolute_layer = len(current_path.relative_to(fs_root).parts)
                    except Exception:
                        absolute_layer = parent_node.absolute_layer + 1

                    current_node = FileSystemNode(
                        name=current_path.name,
                        path=current_path,
                        is_file=False,
                        depth=depth,
                        absolute_layer=absolute_layer
                    )

                    # Find parent
                    parent_path = current_path.parent
                    parent_node = graph.get_node(str(parent_path))
                    if parent_node:
                        current_node.parent = parent_node
                        parent_node.children[current_node.name] = current_node

                    graph.add_node(current_node, root_path)

            # Add files
            for filename in filenames:
                file_path = current_path / filename

                # Extension filter
                if extensions and not any(filename.lower().endswith(ext.lower()) for ext in extensions):
                    continue

                try:
                    stat_info = file_path.stat()
                    file_size = stat_info.st_size
                except Exception:
                    file_size = 0

                # Calculate absolute layer for file
                try:
                    fs_root = Path(file_path.anchor) if hasattr(file_path, 'anchor') else Path('/')
                    absolute_layer = len(file_path.relative_to(fs_root).parts)
                except Exception:
                    absolute_layer = current_node.absolute_layer + 1

                file_node = FileSystemNode(
                    name=filename,
                    path=file_path,
                    is_file=True,
                    size_bytes=file_size,
                    extension=file_path.suffix.lower(),
                    parent=current_node,
                    depth=current_node.depth + 1,
                    absolute_layer=absolute_layer
                )

                current_node.children[filename] = file_node
                graph.add_node(file_node, root_path)

    # Build nested index matrix relationships
    graph.index_matrix.build_relationships_from_graph(graph)

    print(f"Graph built with {len(graph.all_nodes)} nodes")
    print(f"Nested index matrix: {len(graph.index_matrix.layer_registries)} layer registries")
    return graph


def generate_directory_csv(
    graph: FileSystemGraph,
    output_dir: str = ".",
    output_filename: str = None
):
    """
    Generate a CSV file from the file system graph.

    Args:
        graph: FileSystemGraph containing the structure
        output_dir: Directory where the CSV file will be saved
        output_filename: Custom name for the output CSV (optional)
    """

    # Prepare output path
    output_path = Path(output_dir).resolve()
    output_path.mkdir(parents=True, exist_ok=True)

    if output_filename is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        output_filename = f"directory_tree_{timestamp}.csv"

    csv_file = output_path / output_filename

    data = []
    serial = 1

    # Extract file nodes from graph
    for node in graph.all_nodes.values():
        if not node.is_file:
            continue

        absolute_path = node.full_path
        file_ext = node.extension

        # Excel Hyperlink
        hyperlink = f'=HYPERLINK("file:///{absolute_path.replace(os.sep, "/")}", "{node.name}")'

        data.append([
            serial,
            node.name,
            file_ext,
            get_file_size(node.path),
            node.relative_path,
            absolute_path,
            hyperlink
        ])

        serial += 1

    # Write CSV
    with open(csv_file, 'w', newline='', encoding='utf-8-sig') as f:
        writer = csv.writer(f)
        writer.writerow([
            "Serial",
            "File Name",
            "Extension",
            "Size",
            "Relative Path",
            "Absolute Path",
            "Hyperlink (Excel)"
        ])
        writer.writerows(data)

    print("\n" + "="*60)
    print("CSV File Generated Successfully!")
    print(f"   Location : {csv_file}")
    print(f"   Files    : {len(data)}")
    print(f"   Nodes    : {len(graph.all_nodes)}")
    print("="*60)


def query_files_in_directory(graph: FileSystemGraph, dir_path: str, recursive: bool = True):
    """Query all files in a directory."""
    files = graph.find_files_in_directory(dir_path, recursive)
    if not files:
        print(f"No files found in directory: {dir_path}")
        return

    print(f"\nFiles in {dir_path} (recursive={recursive}):")
    print("-" * 60)
    for file in files:
        print(f"{file.name} ({get_file_size(file.path)}) - {file.relative_path}")
    print(f"Total: {len(files)} files")


def query_files_by_extension(graph: FileSystemGraph, extension: str, root_path: str = None):
    """Query files by extension."""
    files = graph.find_files_by_extension(extension, root_path)
    if not files:
        print(f"No files found with extension: {extension}")
        return

    print(f"\nFiles with extension '{extension}':")
    print("-" * 60)
    for file in files:
        print(f"{file.name} ({get_file_size(file.path)}) - {file.relative_path}")
    print(f"Total: {len(files)} files")


def query_relative_path(graph: FileSystemGraph, path1: str, path2: str):
    """Query the relative path between two points."""
    relative_path = graph.find_nearest_relative_path(path1, path2)
    if relative_path is None:
        print(f"Could not find relative path between: {path1} and {path2}")
        return

    print(f"\nRelative path from '{path1}' to '{path2}':")
    print(f"  {relative_path}")


def query_nodes_by_layer(graph: FileSystemGraph, target_path: str, relative_layer: int):
    """Query all nodes at a specific relative layer from target."""
    nodes = graph.get_nodes_by_layer(target_path, relative_layer)
    if not nodes:
        print(f"No nodes found at relative layer {relative_layer} from {target_path}")
        return

    layer_name = f"Relative Layer {relative_layer:+d}"
    print(f"\n{layer_name} from '{target_path}':")
    print("-" * 60)
    for i, node in enumerate(nodes, 1):
        node_type = "FILE" if node.is_file else "DIR"
        coords = node.get_layer_coordinates(target_path)
        print(f"{i:2d}. [{coords['layer_key']}] {node.name} ({node_type}) - Abs:{node.absolute_layer}, Rel:{coords['relative_layer']:+d}")
    print(f"Total: {len(nodes)} nodes")


def show_layer_hierarchy(graph: FileSystemGraph, target_path: str, max_depth: int = 3):
    """Show hierarchical view by relative layers."""
    hierarchy = graph.get_layer_hierarchy(target_path, max_depth)

    print(f"\nLayer Hierarchy from '{target_path}':")
    print("=" * 80)

    for layer in sorted(hierarchy.keys()):
        nodes = hierarchy[layer]
        layer_name = f"Layer {layer:+d}" if layer != 0 else "Layer 0 (Target)"
        print(f"\n{layer_name}: {len(nodes)} nodes")
        print("-" * 40)

        for node in nodes[:10]:  # Show first 10 nodes per layer
            node_type = "FILE" if node.is_file else "DIR"
            print(f"  [{node.get_layer_key(target_path)}] {node.name} ({node_type})")

        if len(nodes) > 10:
            print(f"  ... and {len(nodes) - 10} more nodes")

        print()


def show_layer_statistics(graph: FileSystemGraph, target_path: str = None):
    """Show spatial coordinate statistics."""
    stats = graph.calculate_spatial_metrics()

    print(f"\nSpatial Statistics{' from ' + target_path if target_path else ''}:")
    print("=" * 60)
    print(f"Total nodes: {stats.get('total_nodes', 0)}")
    print(f"Unique absolute layers: {stats.get('unique_absolute_layers', 0)}")
    print(f"Layer range: {stats.get('layer_range', 'N/A')}")
    print(f"Most populated layer: {stats.get('most_populated_layer', 'N/A')}")
    print(f"Average layer depth: {stats.get('average_layer_depth', 0):.2f}")
    print(f"Spatial density: {stats.get('spatial_density', 0):.2f}")

    if 'layer_distribution' in stats:
        print(f"\nAbsolute Layer Distribution:")
        for layer in sorted(stats['layer_distribution'].keys()):
            count = stats['layer_distribution'][layer]
            print(f"  Layer {layer}: {count} nodes")


def find_node_by_layer_key(graph: FileSystemGraph, layer_key: str):
    """Find node by its layer key."""
    path = graph.find_path_by_layer_key(layer_key)
    if not path:
        print(f"No node found with layer key: {layer_key}")
        return

    node = graph.get_node(path)
    if node:
        print(f"\nNode found for layer key '{layer_key}':")
        print(f"  Path: {path}")
        print(f"  Name: {node.name}")
        print(f"  Type: {'File' if node.is_file else 'Directory'}")
        print(f"  Absolute Layer: {node.absolute_layer}")
        print(f"  Size: {get_file_size(node.path) if node.is_file else 'N/A'}")
    else:
        print(f"Error: Could not retrieve node for path: {path}")


def save_graph(graph: FileSystemGraph, filepath: str):
    """Save graph to file."""
    try:
        if filepath.endswith('.json'):
            graph.save_to_json(filepath)
        elif filepath.endswith('.pkl'):
            with open(filepath, 'wb') as f:
                pickle.dump(graph, f)
        else:
            print(f"Unsupported file format: {filepath}")
            return

        print(f"Graph saved to: {filepath}")
    except Exception as e:
        print(f"Error saving graph: {e}")


def load_graph(filepath: str) -> Optional[FileSystemGraph]:
    """Load graph from file."""
    try:
        graph = FileSystemGraph()
        if filepath.endswith('.json'):
            graph.load_from_json(filepath)
        elif filepath.endswith('.pkl'):
            with open(filepath, 'rb') as f:
                graph = pickle.load(f)
        else:
            print(f"Unsupported file format: {filepath}")
            return None

        print(f"Graph loaded from: {filepath} ({len(graph.all_nodes)} nodes)")
        return graph
    except Exception as e:
        print(f"Error loading graph: {e}")
        return None


# ====================== MAIN ======================

def main():
    """Main CLI function."""
    parser = argparse.ArgumentParser(
        description="Directory Tree to CSV Generator with Graph-Based Queries",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Basic CSV generation
  python generate_tree_csv.py /path/to/dir1 /path/to/dir2
  python generate_tree_csv.py -o /output/dir -e .hpp,.cpp,.md /path/to/code

  # Save/load graph structure
  python generate_tree_csv.py --save-graph structure.json /path/to/dir
  python generate_tree_csv.py --load-graph structure.json --query-dir /some/path

  # Query operations
  python generate_tree_csv.py --load-graph structure.json --query-extension .cpp
  python generate_tree_csv.py --load-graph structure.json --relative-path /path1 /path2
        """
    )

    # Main operation modes
    parser.add_argument(
        'root_dirs',
        nargs='*',
        help='One or more root directories to scan (not needed with --load-graph)'
    )

    # Output options
    parser.add_argument(
        '-o', '--output-dir',
        default='.',
        help='Output directory for CSV file (default: current directory)'
    )

    parser.add_argument(
        '-f', '--filename',
        help='Custom name for the output CSV file (optional)'
    )

    parser.add_argument(
        '-e', '--extensions',
        help='Comma-separated list of file extensions to include (e.g., .hpp,.cpp,.md)'
    )

    parser.add_argument(
        '--max-depth',
        type=int,
        help='Override maximum directory depth (default: bound to matrix system capacity)'
    )

    parser.add_argument(
        '--layer-aware',
        action='store_true',
        help='Use ancestor-first instantiation with layer-aware traversal (prevents depth hell)'
    )

    # Graph operations
    parser.add_argument(
        '--save-graph',
        help='Save graph structure to file (.json or .pkl)'
    )

    parser.add_argument(
        '--load-graph',
        help='Load graph structure from file (.json or .pkl)'
    )

    # Query operations
    parser.add_argument(
        '--query-dir',
        help='Query all files in directory (use with --load-graph)'
    )

    parser.add_argument(
        '--query-extension',
        help='Query files by extension (use with --load-graph)'
    )

    parser.add_argument(
        '--relative-path',
        nargs=2,
        metavar=('PATH1', 'PATH2'),
        help='Find relative path between two points (use with --load-graph)'
    )

    parser.add_argument(
        '--no-recursive',
        action='store_true',
        help='For --query-dir: do not recurse into subdirectories'
    )

    # Layer-based operations
    parser.add_argument(
        '--query-layer',
        nargs=2,
        metavar=('TARGET_PATH', 'RELATIVE_LAYER'),
        help='Query nodes at specific relative layer from target path'
    )

    parser.add_argument(
        '--layer-hierarchy',
        metavar='TARGET_PATH',
        help='Show hierarchical view by relative layers from target path'
    )

    parser.add_argument(
        '--layer-stats',
        nargs='?',
        const=None,
        metavar='TARGET_PATH',
        help='Show layer distribution statistics (optional target for relative layers)'
    )

    parser.add_argument(
        '--find-by-layer-key',
        metavar='LAYER_KEY',
        help='Find node by its layer key (SERIAL_ABSOLUTE_RELATIVE_ALPHA format)'
    )

    # Matrix-based operations
    parser.add_argument(
        '--matrix-path',
        nargs=2,
        metavar=('START_PATH', 'END_PATH'),
        help='Find shortest path using nested matrix system'
    )

    parser.add_argument(
        '--multi-point-path',
        nargs='+',
        metavar='PATH',
        help='Find optimal path connecting multiple points'
    )

    parser.add_argument(
        '--query-relationships',
        nargs=2,
        metavar=('TYPE', 'LAYER'),
        help='Query relationships by type and optional layer (types: same_layer_siblings, cross_layer_hierarchy, file_dependencies)'
    )

    parser.add_argument(
        '--analyze-matrices',
        action='store_true',
        help='Analyze patterns in all nested matrices'
    )

    parser.add_argument(
        '--bounded-query',
        nargs=2,
        metavar=('TYPE', 'PATTERN'),
        help='Execute depth-bounded query (types: file_search, pathfinding)'
    )

    # Spatial coordinate-based operations
    parser.add_argument(
        '--spatial-absolute',
        metavar='ABSOLUTE_LAYER',
        type=int,
        help='Query all nodes at specific absolute layer using intrinsic coordinates'
    )

    parser.add_argument(
        '--spatial-relative',
        nargs=2,
        metavar=('TARGET_PATH', 'RELATIVE_LAYER'),
        help='Query nodes at relative layer from target using intrinsic coordinates'
    )

    parser.add_argument(
        '--spatial-hierarchy',
        nargs=2,
        metavar=('CENTER_PATH', 'RADIUS'),
        help='Show spatial hierarchy centered on path with given radius'
    )

    parser.add_argument(
        '--spatial-neighbors',
        nargs=2,
        metavar=('NODE_PATH', 'DISTANCE'),
        help='Find spatial neighbors of node at given distance'
    )

    parser.add_argument(
        '--spatial-metrics',
        action='store_true',
        help='Calculate and display spatial distribution metrics'
    )

    # Ancestor vector analysis
    parser.add_argument(
        '--ancestor-analysis',
        metavar='FILE_PATH',
        help='Analyze ancestor vector and layer indicators for a file'
    )

    parser.add_argument(
        '--common-ancestor',
        nargs=2,
        metavar=('PATH1', 'PATH2'),
        help='Find common ancestor between two paths using ancestor vectors'
    )

    parser.add_argument(
        '--ancestor-path',
        nargs=2,
        metavar=('START_PATH', 'END_PATH'),
        help='Find path using ancestor vector analysis (primary method)'
    )

    parser.add_argument(
        '--relative-path-ancestor',
        nargs=2,
        metavar=('PATH1', 'PATH2'),
        help='Find relative path using ancestor vector approach (layer indicator method)'
    )

    parser.add_argument(
        '--compare-relative-methods',
        nargs=2,
        metavar=('PATH1', 'PATH2'),
        help='Compare ancestor vector vs traditional relative path methods'
    )

    parser.add_argument(
        '--validate-spatial',
        action='store_true',
        help='Validate spatial coordinate integrity'
    )

    parser.add_argument(
        '--show-config',
        action='store_true',
        help='Display current system configuration bound to matrix capacity'
    )

    parser.add_argument(
        '--spatial-diff-path',
        nargs=2,
        metavar=('START_PATH', 'END_PATH'),
        help='Find path using spatial attribute differences (not graph distance)'
    )

    # Rich relationship queries
    parser.add_argument(
        '--file-relationships',
        metavar='FILE_PATH',
        help='Show rich relationship attributes for a specific file'
    )

    parser.add_argument(
        '--folder-relationships',
        metavar='FOLDER_PATH',
        help='Show rich relationship attributes for a specific folder'
    )

    parser.add_argument(
        '--layer-relationships',
        metavar='LAYER_NUMBER',
        type=int,
        help='Show layer-level relationship analysis for a specific layer'
    )

    parser.add_argument(
        '--relationship-analysis',
        action='store_true',
        help='Analyze relationship patterns across the entire graph'
    )

    args = parser.parse_args()

    # Parse extensions
    extensions = None
    if args.extensions:
        extensions = [ext.strip() for ext in args.extensions.split(',') if ext.strip()]

    graph = None

    # Load existing graph if specified
    if args.load_graph:
        graph = load_graph(args.load_graph)
        if not graph:
            return

    # Build graph from directories if no load specified or if we have root dirs
    elif args.root_dirs:
        if args.layer_aware:
            graph = build_filesystem_graph_ancestor_first(args.root_dirs, extensions,
                                                        args.max_depth if args.max_depth else None)
        else:
            graph = build_filesystem_graph(args.root_dirs, extensions)

    # Perform queries if requested
    if args.query_dir and graph:
        recursive = not args.no_recursive
        query_files_in_directory(graph, args.query_dir, recursive)

    if args.query_extension and graph:
        root_path = args.root_dirs[0] if args.root_dirs else None
        query_files_by_extension(graph, args.query_extension, root_path)

    if args.relative_path and graph:
        query_relative_path(graph, args.relative_path[0], args.relative_path[1])

    # Layer-based queries
    if args.query_layer and graph:
        target_path, rel_layer_str = args.query_layer
        try:
            rel_layer = int(rel_layer_str)
            query_nodes_by_layer(graph, target_path, rel_layer)
        except ValueError:
            print(f"Error: Invalid relative layer '{rel_layer_str}'. Must be an integer.")

    if args.layer_hierarchy and graph:
        show_layer_hierarchy(graph, args.layer_hierarchy)

    if hasattr(args, 'layer_stats') and graph:
        show_layer_statistics(graph, getattr(args, 'layer_stats', None))

    if args.find_by_layer_key and graph:
        find_node_by_layer_key(graph, args.find_by_layer_key)

    # Matrix-based operations
    if args.matrix_path and graph:
        matrix_path_result = graph.find_shortest_path_matrix(args.matrix_path[0], args.matrix_path[1])
        if matrix_path_result:
            print(f"\nMatrix-based path: {' -> '.join(matrix_path_result)}")
        else:
            print(f"No matrix-based path found between {args.matrix_path[0]} and {args.matrix_path[1]}")

    if args.multi_point_path and graph:
        multi_result = graph.multi_point_pathfinding(args.multi_point_path)
        print(f"\nMulti-point pathfinding result:")
        print(f"Points: {multi_result.get('points', [])}")
        print(f"Traversal path: {multi_result.get('traversal_path', [])}")
        print(f"Connected: {multi_result.get('total_points', 0)}/{multi_result.get('connected_points', 0)} points")

    if args.query_relationships and graph:
        rel_type, layer_str = args.query_relationships
        layer = int(layer_str) if layer_str.isdigit() else None
        relationships = graph.query_by_relationship_type(rel_type, layer)
        print(f"\nRelationships of type '{rel_type}'{' at layer ' + str(layer) if layer else ''}:")
        for match in relationships.get('matches', []):
            print(f"  {match}")

    if args.analyze_matrices and graph:
        matrix_analysis = graph.analyze_matrix_patterns()
        print(f"\nMatrix Pattern Analysis:")
        for matrix_name, analysis in matrix_analysis.items():
            print(f"Matrix '{matrix_name}':")
            patterns = analysis.get('patterns', {})
            if 'structural_similarity_groups' in patterns:
                print(f"  Similar layer groups: {len(patterns['structural_similarity_groups'])}")
            stats = analysis.get('statistics', {})
            print(f"  Total relationships: {stats.get('folder_hierarchy_relationships', 0) + stats.get('file_dependency_relationships', 0)}")

    if args.bounded_query and graph:
        query_type, pattern = args.bounded_query
        parameters = {'pattern': pattern, 'max_results': 10}
        results = graph.query_system.execute_layer_bounded_query(query_type, parameters)

        print(f"\nBounded {query_type} query for '{pattern}':")
        if results:
            for i, result in enumerate(results[:10], 1):
                print(f"  {i}. {result}")
            if len(results) > 10:
                print(f"  ... and {len(results) - 10} more results")
        else:
            print("  No results found")

    # Spatial coordinate-based operations
    if args.spatial_absolute and graph:
        try:
            layer = int(args.spatial_absolute)
            nodes = graph.query_absolute_layer(layer)
            print(f"\nNodes at absolute layer {layer} (using intrinsic coordinates):")
            for i, node in enumerate(nodes[:20], 1):  # Limit display
                print(f"  {i}. {node.name} ({'FILE' if node.is_file else 'DIR'}) - {node.spatial_signature}")
            if len(nodes) > 20:
                print(f"  ... and {len(nodes) - 20} more nodes")
        except ValueError:
            print(f"Error: Invalid absolute layer '{args.spatial_absolute}'")

    if args.spatial_relative and graph:
        target_path, rel_layer_str = args.spatial_relative
        try:
            rel_layer = int(rel_layer_str)
            nodes = graph.query_relative_layer(target_path, rel_layer)
            print(f"\nNodes at relative layer {rel_layer:+d} from '{target_path}':")
            for i, node in enumerate(nodes[:15], 1):
                print(f"  {i}. {node.name} ({'FILE' if node.is_file else 'DIR'}) - Abs:{node.absolute_layer}, Sig:{node.spatial_signature}")
        except ValueError:
            print(f"Error: Invalid relative layer '{rel_layer_str}'")

    if args.spatial_hierarchy and graph:
        center_path, radius_str = args.spatial_hierarchy
        try:
            radius = int(radius_str)
            hierarchy = graph.get_spatial_hierarchy(center_path, radius)
            print(f"\nSpatial hierarchy centered on '{center_path}' (radius {radius}):")
            for rel_layer in sorted(hierarchy.keys()):
                nodes = hierarchy[rel_layer]
                layer_name = f"Layer {rel_layer:+d}" if rel_layer != 0 else "Center (Layer 0)"
                print(f"\n{layer_name}: {len(nodes)} nodes")
                for node in nodes[:5]:  # Show first 5 per layer
                    print(f"  - {node.name} ({'FILE' if node.is_file else 'DIR'}) Sig:{node.spatial_signature}")
                if len(nodes) > 5:
                    print(f"  ... and {len(nodes) - 5} more")
        except ValueError:
            print(f"Error: Invalid radius '{radius_str}'")

    if args.spatial_neighbors and graph:
        node_path, distance_str = args.spatial_neighbors
        try:
            distance = int(distance_str)
            neighbors = graph.get_spatial_neighbors(node_path, distance)
            print(f"\nSpatial neighbors of '{node_path}' at distance {distance}:")
            for neighbor_type, nodes in neighbors.items():
                if nodes:
                    print(f"\n{neighbor_type.replace('_', ' ').title()}: {len(nodes)} nodes")
                    for node in nodes[:3]:  # Show first 3 per type
                        print(f"  - {node.name} ({'FILE' if node.is_file else 'DIR'}) Abs:{node.absolute_layer}")
                    if len(nodes) > 3:
                        print(f"  ... and {len(nodes) - 3} more")
        except ValueError:
            print(f"Error: Invalid distance '{distance_str}'")

    if args.spatial_metrics and graph:
        metrics = graph.calculate_spatial_metrics()
        print(f"\nSpatial Distribution Metrics:")
        print(f"  Total nodes: {metrics.get('total_nodes', 0)}")
        print(f"  Unique absolute layers: {metrics.get('unique_absolute_layers', 0)}")
        print(f"  Layer range: {metrics.get('layer_range', 'N/A')}")
        print(f"  Most populated layer: {metrics.get('most_populated_layer', 'N/A')}")
        print(f"  Average layer depth: {metrics.get('average_layer_depth', 0):.2f}")
        print(f"  Spatial density: {metrics.get('spatial_density', 0):.2f}")

    if args.validate_spatial and graph:
        validation = graph.validate_spatial_integrity()
        print(f"\nSpatial Coordinate Validation:")
        print(f"  Status: {'✓ VALID' if validation.get('is_valid', False) else '✗ INVALID'}")
        print(f"  Checked nodes: {validation.get('stats', {}).get('checked_nodes', 0)}")
        print(f"  Valid coordinates: {validation.get('stats', {}).get('valid_coordinates', 0)}")
        print(f"  Invalid coordinates: {validation.get('stats', {}).get('invalid_coordinates', 0)}")

        if validation.get('issues'):
            print(f"  Issues found: {len(validation['issues'])}")
            for issue in validation['issues'][:3]:  # Show first 3 issues
                print(f"    - {issue}")
            if len(validation['issues']) > 3:
                print(f"    ... and {len(validation['issues']) - 3} more issues")

    if args.ancestor_analysis and graph:
        node = graph.get_node(args.ancestor_analysis)
        if node:
            print(f"\nAncestor Vector Analysis for: {args.ancestor_analysis}")
            print("=" * 80)

            ancestor_vector = node.relationships.ancestor_vector
            print(f"Layer Depth (Vector Capacity): {ancestor_vector.layer_depth}")
            print(f"Ancestor Chain: {ancestor_vector.ancestors}")
            print(f"Root Ancestor: {ancestor_vector.root_ancestor}")
            print(f"Immediate Parent: {ancestor_vector.immediate_parent}")

            # Show layer indicator power
            print(f"\nLayer Indicator Power:")
            print(f"  Absolute Layer: {node.absolute_layer} (derived from ancestor vector length!)")
            print(f"  Ancestor Chain Length: {len(ancestor_vector.ancestors)}")
            print(f"  Hierarchical Depth: {len(ancestor_vector.ancestors)} levels from root")

            # Show relationship summary
            summary = node.relationships.get_relationship_summary()
            print(f"\nRelationship Summary:")
            print(f"  Single Layer: {summary['single_layer']['sibling_files_count']} sibling files")
            print(f"  Parent-Child: {summary['parent_child']['total_children']} children")
            print(f"  Ancestor-Descendant: {summary['ancestor_descendant']['total_descendant_files']} descendant files")
        else:
            print(f"Node not found: {args.ancestor_analysis}")

    if args.common_ancestor and graph:
        path1, path2 = args.common_ancestor
        node1 = graph.get_node(path1)
        node2 = graph.get_node(path2)

        if node1 and node2:
            print(f"\nCommon Ancestor Analysis")
            print("=" * 60)
            print(f"Path 1: {path1}")
            print(f"Path 2: {path2}")

            common_ancestor = node1.find_common_ancestor_with(node2)
            branching_point = node1.find_branching_point_with(node2)
            ancestor_distance = node1.get_ancestor_distance_to(node2)

            print(f"\nResults:")
            print(f"  Common Ancestor: {common_ancestor or 'None'}")
            print(f"  Branching Point: {branching_point or 'N/A'}")
            print(f"  Ancestor Distance: {ancestor_distance}")

            print(f"\nAncestor Vectors:")
            print(f"  Path 1 Chain: {node1.ancestor_chain}")
            print(f"  Path 2 Chain: {node2.ancestor_chain}")

            # Show layer indicator in action
            print(f"\nLayer Indicators:")
            print(f"  Path 1 Layer: {node1.absolute_layer} (vector length: {len(node1.ancestor_chain)})")
            print(f"  Path 2 Layer: {node2.absolute_layer} (vector length: {len(node2.ancestor_chain)})")
        else:
            print(f"One or both paths not found: {path1}, {path2}")

    if args.ancestor_path and graph:
        start_path, end_path = args.ancestor_path
        print(f"\nAncestor Vector Pathfinding from '{start_path}' to '{end_path}':")
        print("Using ancestor vector analysis as primary method (layer indicator = vector capacity)")

        start_node = graph.get_node(start_path)
        end_node = graph.get_node(end_path)

        if not start_node or not end_node:
            print(f"Error: Could not find nodes for paths")
            return

        # Show ancestor vector differences
        common_ancestor = start_node.find_common_ancestor_with(end_node)
        branching_point = start_node.find_branching_point_with(end_node)
        ancestor_distance = start_node.get_ancestor_distance_to(end_node)

        print(f"Ancestor Vector Analysis:")
        print(f"  Common Ancestor: {common_ancestor or 'None'}")
        print(f"  Branching Point: {branching_point or 'N/A'}")
        print(f"  Ancestor Distance: {ancestor_distance}")
        print(f"  Start Layer (Vector Length): {start_node.absolute_layer}")
        print(f"  End Layer (Vector Length): {end_node.absolute_layer}")

        # Try pathfinding
        ancestor_path = graph.query_system._ancestor_vector_pathfinding(start_node, end_node)
        if ancestor_path:
            print(f"\nPath found using ancestor vectors:")
            for i, path_segment in enumerate(ancestor_path, 1):
                print(f"  {i}. {path_segment}")
        else:
            print("No ancestor vector path found")

    if args.relative_path_ancestor and graph:
        path1, path2 = args.relative_path_ancestor
        print(f"\nRelative Path using Ancestor Vectors")
        print("=" * 50)
        print(f"From: {path1}")
        print(f"To:   {path2}")

        # Show ancestor vector information
        node1 = graph.get_node(path1)
        node2 = graph.get_node(path2)

        if node1 and node2:
            print(f"\nAncestor Vector Analysis:")
            print(f"  Path1 Layer Depth: {node1.absolute_layer} (vector capacity)")
            print(f"  Path2 Layer Depth: {node2.absolute_layer} (vector capacity)")
            print(f"  Path1 Ancestors: {node1.ancestor_chain}")
            print(f"  Path2 Ancestors: {node2.ancestor_chain}")

            common_ancestor = node1.find_common_ancestor_with(node2)
            print(f"  Common Ancestor: {common_ancestor or 'None'}")

            # Calculate relative path using ancestor vectors
            relative_path = graph.find_nearest_relative_path(path1, path2)
            print(f"\nRelative Path (Ancestor Vector Method): {relative_path}")

            # Show traditional method for comparison
            traditional_path = graph._calculate_traditional_relative_path(path1, path2)
            print(f"Traditional Method: {traditional_path}")

            # Verify they match
            if relative_path == traditional_path:
                print("✓ Ancestor vector method matches traditional approach!")
            else:
                print("⚠ Methods differ - ancestor vector method may be more accurate")

    if args.compare_relative_methods and graph:
        path1, path2 = args.compare_relative_methods

        print(f"\n[*] Ancestor Vector Relative Path Demo")
        print("=" * 50)
        print(f"From: {path1}")
        print(f"To:   {path2}")

        # Simple demonstration
        node1 = graph.get_node(path1)
        node2 = graph.get_node(path2)

        if node1 and node2:
            print("\n[*] Ancestor Vector Method:")
            print(f"  Layer 1 Depth: {node1.absolute_layer} (vector capacity)")
            print(f"  Layer 2 Depth: {node2.absolute_layer} (vector capacity)")
            print(f"  Ancestor Chain 1: {node1.ancestor_chain}")
            print(f"  Ancestor Chain 2: {node2.ancestor_chain}")

            common = node1.find_common_ancestor_with(node2)
            print(f"  Common Ancestor: {common}")

            relative = graph.find_nearest_relative_path(path1, path2)
            print(f"  Relative Path: {relative}")

            print("\n[+] Ancestor vectors provide immediate layer indicators!")
            print("   No string parsing needed - pre-computed hierarchical context!")
        else:
            print("Nodes not found")

    if args.spatial_diff_path and graph:
        start_path, end_path = args.spatial_diff_path
        print(f"\nSpatial Difference Pathfinding from '{start_path}' to '{end_path}':")
        print("Using spatial attribute value differences (not traditional graph distance)")

        start_node = graph.get_node(start_path)
        end_node = graph.get_node(end_path)

        if not start_node or not end_node:
            print(f"Error: Could not find nodes for paths")
            return

        # Show spatial differences between start and end
        spatial_diffs = graph.query_system._calculate_spatial_differences(start_node, end_node)
        print(f"Spatial differences between start and end:")
        print(f"  Absolute layer diff: {spatial_diffs['absolute_layer_diff']}")
        print(f"  Relative layer diff: {spatial_diffs['relative_layer_diff']}")
        print(f"  Spatial signature diff: {spatial_diffs['spatial_signature_diff']}")
        print(f"  Combined spatial distance: {spatial_diffs['combined_spatial_distance']:.2f}")

        spatial_path = graph.query_system.find_shortest_path_matrix(start_path, end_path)
        if spatial_path:
            print("\nPath found:")
            for i, path_segment in enumerate(spatial_path, 1):
                print(f"  {i}. {path_segment}")

            # Show spatial differences along the path
            print("\nSpatial differences along path:")
            for i in range(len(spatial_path) - 1):
                node1 = graph.get_node(spatial_path[i])
                node2 = graph.get_node(spatial_path[i + 1])
                if node1 and node2:
                    diffs = graph.query_system._calculate_spatial_differences(node1, node2)
                    print(f"  {spatial_path[i]} -> {spatial_path[i + 1]}:")
                    print(f"    Absolute layer diff: {diffs['absolute_layer_diff']}")
                    print(f"    Combined spatial distance: {diffs['combined_spatial_distance']:.2f}")
        else:
            print("No spatial difference path found")
            print("This could be because:")
            print("  - Nodes are not connected through relationship attributes")
            print("  - Spatial differences are too large for current limits")
            print("  - Relationship matrix has insufficient connectivity")

    if args.show_config and graph:
        print(f"\nSystem Configuration (Matrix-Capacity Bound)")
        print("=" * 60)

        traversal_limits = graph.config.get_traversal_limits()
        print(f"Traversal Limits:")
        print(f"  Max Depth: {traversal_limits['max_depth']}")
        print(f"  Breadth-First Limit: {traversal_limits['breadth_first_limit']}")
        print(f"  Safety Buffer: {traversal_limits['safety_buffer']}")

        query_limits = graph.config.get_query_limits()
        print(f"\nQuery Limits:")
        print(f"  Max Results: {query_limits['max_results']}")
        print(f"  Timeout: {query_limits['timeout_seconds']}s")
        print(f"  Max Parallel Ops: {query_limits['max_parallel_operations']}")
        print(f"  Relationship Hop Limit: {query_limits['relationship_hop_limit']}")

        matrix_limits = graph.config.get_matrix_limits()
        print(f"\nMatrix Limits:")
        print(f"  Max Dimensions: {matrix_limits['max_dimensions']}")
        print(f"  Relationship Threshold: {matrix_limits['relationship_threshold']}")
        print(f"  Similarity Threshold: {matrix_limits['pattern_similarity_threshold']}")
        print(f"  Optimization: {'Enabled' if matrix_limits['optimization_enabled'] else 'Disabled'}")

        print(f"\nSystem Limits (Bound to Matrix Capacity):")
        print(f"  Max Traversal Depth: {graph.config.system_limits.max_traversal_depth} (layer registry count × 2)")
        print(f"  Max Query Complexity: {graph.config.system_limits.max_query_complexity} (relationship matrix capacity)")
        print(f"  Max Relationship Hops: {graph.config.system_limits.max_relationship_hops} (cross-layer connectivity)")
        print(f"  Max Layer Span: {graph.config.system_limits.max_layer_span} (layer registry span)")
        print(f"  Max Matrix Dimensions: {graph.config.system_limits.max_matrix_dimensions} (nested matrix capacity)")

    # Rich relationship queries
    if args.file_relationships and graph:
        node = graph.get_node(args.file_relationships)
        if node and node.is_file:
            relationships = node.get_file_relationships()
            print(f"\nRich File Relationships for: {args.file_relationships}")
            print("=" * 80)

            if 'error' in relationships:
                print(f"Error: {relationships['error']}")
            else:
                print(f"Sibling Files: {len(relationships['sibling_files'])}")
                for sibling in relationships['sibling_files'][:5]:
                    print(f"  - {sibling}")
                if len(relationships['sibling_files']) > 5:
                    print(f"  ... and {len(relationships['sibling_files']) - 5} more")

                print(f"\nCommunity Files: {len(relationships['community_files'])}")
                for community in relationships['community_files'][:5]:
                    print(f"  - {community}")

                print(f"\nParent Folder: {relationships['parent_folder'] or 'None'}")
                print(f"Ancestor Chain: {relationships['ancestor_chain']}")

                analysis = relationships['sibling_community_analysis']
                print(f"\nRelationship Analysis:")
                print(f"  Pure Siblings: {len(analysis['pure_siblings_files'])}")
                print(f"  Pure Community: {len(analysis['pure_community_files'])}")
                print(f"  Overlapping: {len(analysis['overlapping_community'])}")
        else:
            print(f"File not found or is not a file: {args.file_relationships}")

    if args.folder_relationships and graph:
        node = graph.get_node(args.folder_relationships)
        if node and not node.is_file:
            relationships = node.get_folder_relationships()
            print(f"\nRich Folder Relationships for: {args.folder_relationships}")
            print("=" * 80)

            if 'error' in relationships:
                print(f"Error: {relationships['error']}")
            else:
                print(f"Sibling Folders: {len(relationships['sibling_folders'])}")
                for sibling in relationships['sibling_folders'][:5]:
                    print(f"  - {sibling}")

                print(f"\nChild Files: {len(relationships['child_files'])}")
                for child in relationships['child_files'][:5]:
                    print(f"  - {child}")

                print(f"\nChild Folders: {len(relationships['child_folders'])}")
                for child in relationships['child_folders'][:5]:
                    print(f"  - {child}")

                print(f"\nCommunity Folders: {len(relationships['community_folders'])}")
                for community in relationships['community_folders'][:5]:
                    print(f"  - {community}")

                print(f"\nParent Folder: {relationships['parent_folder'] or 'None'}")
                print(f"Ancestor Chain: {relationships['ancestor_chain']}")

                depth_info = relationships['hierarchical_depth']
                print(f"\nHierarchical Depth:")
                print(f"  Ancestor Levels: {depth_info['ancestor_depth']}")
                print(f"  Max Descendant Depth (Files): {depth_info['max_descendant_depth_files']}")
                print(f"  Max Descendant Depth (Folders): {depth_info['max_descendant_depth_folders']}")
                print(f"  Total Span: {depth_info['total_hierarchical_span']}")
        else:
            print(f"Folder not found or is not a folder: {args.folder_relationships}")

    if args.layer_relationships is not None and graph:
        layer_info = graph.registry_system.get_registry(args.layer_relationships)
        if layer_info:
            relationships = layer_info.get_layer_relationships()
            print(f"\nLayer {args.layer_relationships} Relationship Analysis")
            print("=" * 80)

            stats = relationships['layer_statistics']
            print(f"Total Nodes in Layer: {stats['total_nodes']}")
            print(f"Relationship-Rich Nodes: {stats['relationship_richness']}")
            print(f"Average Relationships per Node: {stats['average_relationships_per_node']:.2f}")

            composition = relationships['layer_composition']
            print(f"\nLayer Composition:")
            print(f"  Folders: {composition['folders']}")
            print(f"  Files: {composition['files']}")
            print(f"  Relationship Density: {composition['relationship_density']:.2f}")

            layer_rels = relationships['layer_relationships']
            print(f"\nLayer Relationship Summary:")
            print(f"  Single Layer Relationships: {layer_rels['single_layer']}")
            print(f"  Parent-Child Relationships: {layer_rels['parent_child']}")
            print(f"  Cross-Layer Relationships: {layer_rels['cross_layer']}")
        else:
            print(f"Layer not found: {args.layer_relationships}")

    if args.relationship_analysis and graph:
        analysis = graph.registry_system.analyze_registry_patterns()
        print(f"\nComprehensive Relationship Analysis")
        print("=" * 80)

        print(f"Total Layers: {analysis['total_layers']}")
        print(f"Layer Range: {analysis['layer_range']}")

        # Show relationship patterns by layer
        for layer_num in sorted(analysis['relationship_patterns'].keys()):
            patterns = analysis['relationship_patterns'][layer_num]
            stats = patterns['layer_statistics']
            print(f"\nLayer {layer_num}:")
            print(f"  Nodes: {stats['total_nodes']}, Rich Relationships: {stats['relationship_richness']}")
            print(f"  Avg Relationships/Node: {stats['average_relationships_per_node']:.2f}")

        # Show hierarchical patterns
        hierarchy = analysis['ancestor_descendant_patterns']
        print(f"\nHierarchical Patterns:")
        print(f"  Total Ancestor Chains: {hierarchy['total_ancestor_chains']}")
        print(f"  Total Descendant Relationships: {hierarchy['total_descendant_relationships']}")
        print(f"  Average Chain Length: {hierarchy['average_chain_length']:.2f}")

        print(f"\nCross-Layer Relationships: {len(analysis['cross_layer_relationships'])} layer pairs")

    # Save graph if requested
    if args.save_graph and graph:
        save_graph(graph, args.save_graph)

    # Generate CSV if we have a graph and no specific query was requested
    spatial_queries = [args.spatial_absolute, args.spatial_relative, args.spatial_hierarchy,
                      args.spatial_neighbors, args.spatial_metrics, args.validate_spatial]
    other_queries = [args.query_dir, args.query_extension, args.relative_path,
                    args.bounded_query, args.query_relationships, args.analyze_matrices]

    if graph and not any(other_queries + spatial_queries):
        generate_directory_csv(
            graph=graph,
            output_dir=args.output_dir,
            output_filename=args.filename
        )


if __name__ == "__main__":
    main()