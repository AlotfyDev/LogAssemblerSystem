#!/usr/bin/env python3
"""
File System Structure Detector - Modular Architecture
Multi-tier object architecture for advanced file system analysis.
"""

# Import all subsystems for easy access
from .filesystem_core import FileSystemGraph, FileSystemNode
from .filesystem_layers import LayerSystem
from .filesystem_registries import RegistrySystem, LayerRegistry
from .filesystem_matrices import MatrixSystem, NestedIndexMatrix
from .filesystem_queries import QuerySystem

__version__ = "1.0.0"
__all__ = [
    'FileSystemGraph',
    'FileSystemNode',
    'LayerSystem',
    'RegistrySystem',
    'LayerRegistry',
    'MatrixSystem',
    'NestedIndexMatrix',
    'QuerySystem'
]