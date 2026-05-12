#!/usr/bin/env python3
"""
ASCC Header Audit Analyzer

Purpose
-------
Analyze the Bridge Orchestrator / Communication Context header-only codebase
as a composable component. The script is intentionally dependency-free and can
run locally or in GitHub Actions.

It is not a C++ compiler and does not replace semantic compile tests. It
provides a repeatable structural/AST-lite audit:
  - per-root-subfolder inventory
  - zero-size header classification
  - include graph extraction
  - top-level declaration extraction (classes/structs/enums/templates)
  - duplicate declaration-name hints

Usage
-----
python tools/ascc_header_audit.py \
  --root include/assembler/bridge_orchestrator \
  --out audit/ascc_header_audit

Outputs
-------
  ascc_header_inventory.csv
  ascc_zero_size_headers.csv
  ascc_includes.csv
  ascc_declarations.csv
  ascc_root_summary.csv
  ascc_audit_summary.json
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, List, Dict


INCLUDE_RE = re.compile(r'^\s*#\s*include\s*[<\"]([^>\"]+)[>\"]', re.MULTILINE)
NAMESPACE_RE = re.compile(r'\bnamespace\s+([A-Za-z_][A-Za-z0-9_:]*)')

# Declaration extraction is intentionally AST-lite, but it must not harvest
# names from comments or from the `class` token inside `enum class`.
CLASS_RE = re.compile(r'(?m)^\s*(?:template\s*<[^>]*>\s*)?(class|struct)\s+([A-Za-z_][A-Za-z0-9_]*)\b')
ENUM_CLASS_RE = re.compile(r'(?m)^\s*enum\s+class\s+([A-Za-z_][A-Za-z0-9_]*)\b')
ENUM_RE = re.compile(r'(?m)^\s*enum\s+(?!class\b)([A-Za-z_][A-Za-z0-9_]*)\b')
TEMPLATE_RE = re.compile(r'\btemplate\s*<([^>]*)>')
FUNCTION_RE = re.compile(
    r'(?m)^\s*(?:\[\[nodiscard\]\]\s*)?(?:static\s+)?(?:constexpr\s+)?'
    r'(?:auto|bool|void|std::[A-Za-z_][A-Za-z0-9_:<>]*|[A-Za-z_][A-Za-z0-9_:<>]*)\s+'
    r'([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{}]*\)\s*(?:const\s*)?(?:noexcept\s*)?(?:\{|;)'
)

FALSE_DECLARATION_NAMES = {
    "ID",
    "Id",
    "id",
    "class",
    "struct",
    "enum",
    "with",
    "if",
    "for",
    "while",
    "switch",
}


@dataclass
class HeaderRecord:
    rel_path: str
    root_folder: str
    size_bytes: int
    sha256: str
    line_count: int
    empty: bool
    classification: str


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def read_text(path: Path) -> str:
    try:
        return path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return path.read_text(encoding="utf-8", errors="replace")


def strip_cpp_comments(text: str) -> str:
    """Remove C/C++ comments while preserving line structure.

    This prevents the AST-lite declaration regexes from collecting words from
    documentation comments such as "ID", "with", or "class".
    """
    def replace_block(match: re.Match[str]) -> str:
        return "\n" * match.group(0).count("\n")

    text = re.sub(r'/\*.*?\*/', replace_block, text, flags=re.DOTALL)
    text = re.sub(r'//.*', '', text)
    return text


def rel_posix(path: Path, root: Path) -> str:
    return path.relative_to(root).as_posix()


def root_folder_for(rel_path: str) -> str:
    parts = rel_path.split("/")
    return parts[0] if parts else ""


def has_counterpart(root: Path, rel_path: str) -> bool:
    """Return true if a likely canonical counterpart exists for empty alternate paths."""
    p = Path(rel_path)

    # obligations/ports/contracts/TPort.hpp -> obligations/ports/TPort.hpp
    if "contracts" in p.parts:
        parts = list(p.parts)
        idx = parts.index("contracts")
        counterpart = Path(*parts[:idx], p.name)
        return (root / counterpart).exists()

    # bridge_core/orchestration/TBridge.hpp -> bridge_core/TBridge.hpp
    if "orchestration" in p.parts:
        parts = list(p.parts)
        idx = parts.index("orchestration")
        counterpart = Path(*parts[:idx], p.name)
        return (root / counterpart).exists()

    # registries/channel_registry/TChannelRegistry.hpp
    # -> registries/optional_registries/typed/TChannelRegistry.hpp
    if len(p.parts) >= 3 and p.parts[0] == "registries" and p.parts[1].endswith("_registry"):
        counterpart = Path("registries", "optional_registries", "typed", p.name)
        return (root / counterpart).exists()

    return False


def classify_zero_header(root: Path, rel_path: str) -> str:
    p = Path(rel_path)
    parts = p.parts

    if has_counterpart(root, rel_path):
        if "contracts" in parts or "orchestration" in parts:
            return "safe_forwarder_candidate"
        if len(parts) >= 3 and parts[0] == "registries" and parts[1].endswith("_registry"):
            return "alternate_registry_path_empty"

    if parts[:1] == ("compatibility",) and len(parts) >= 3 and parts[1].endswith("_compatibility"):
        return "compatibility_dimension_placeholder"

    if parts[:1] == ("diagnostics",) and len(parts) >= 3:
        if parts[1].endswith("_views") or parts[1] in {"carrier_snapshots", "protocol_snapshots"}:
            return "diagnostic_view_or_snapshot_placeholder"

    if parts[:1] == ("integration_boundaries",) and len(parts) >= 2 and parts[1].endswith("_ports"):
        return "integration_boundary_port_placeholder"

    if parts[:1] == ("obligations",) and "traits" in parts:
        return "obligation_traits_placeholder"

    if parts[:1] == ("protocols",) and len(parts) >= 3:
        specialized = {
            "diagnostic_exchange",
            "envelope_placement",
            "persistence_delivery",
            "receiver_delivery",
            "registry_delivery",
            "telemetry_export",
            "thin_c_abi",
        }
        if parts[1] in specialized:
            return "specialized_protocol_placeholder"
        if parts[1] == "common" and p.name.endswith("Traits.hpp"):
            return "protocol_trait_placeholder"

    if parts[:2] == ("sessions", "correlation"):
        return "session_correlation_placeholder"

    if parts[:2] == ("bindings", "binding_policies"):
        return "binding_policy_legacy_or_empty_surface"

    return "unclassified_empty_header"


def classify_header(root: Path, rel_path: str, size_bytes: int) -> str:
    if size_bytes == 0:
        return classify_zero_header(root, rel_path)
    text = read_text(root / rel_path)
    if "#pragma once" in text and INCLUDE_RE.search(text) and len(text.strip().splitlines()) <= 45:
        return "forwarding_or_thin_header"
    return "implemented_header"


def collect_headers(root: Path) -> List[HeaderRecord]:
    records: List[HeaderRecord] = []
    for path in sorted(root.rglob("*.hpp")):
        data = path.read_bytes()
        rel = rel_posix(path, root)
        text = data.decode("utf-8", errors="replace")
        line_count = 0 if not text else text.count("\n") + (0 if text.endswith("\n") else 1)
        records.append(HeaderRecord(
            rel_path=rel,
            root_folder=root_folder_for(rel),
            size_bytes=len(data),
            sha256=sha256_bytes(data),
            line_count=line_count,
            empty=(len(data) == 0),
            classification=classify_header(root, rel, len(data)),
        ))
    return records


def extract_includes(root: Path, records: Iterable[HeaderRecord]) -> List[Dict[str, str]]:
    rows: List[Dict[str, str]] = []
    for rec in records:
        if rec.empty:
            continue
        text = read_text(root / rec.rel_path)
        for inc in INCLUDE_RE.findall(text):
            if inc.startswith("assembler/communication_context/"):
                include_class = "communication_context_root"
            elif inc.startswith("assembler/bridge_orchestrator/"):
                include_class = "bridge_orchestrator_root"
            elif inc.startswith("assembler/"):
                include_class = "other_assembler_root"
            elif inc.startswith("../") or inc.startswith("./"):
                include_class = "relative"
            else:
                include_class = "system_or_external"
            rows.append({
                "HeaderPath": rec.rel_path,
                "RootFolder": rec.root_folder,
                "Include": inc,
                "IncludeClass": include_class,
            })
    return rows


def add_declaration(rows: List[Dict[str, str]], rec: HeaderRecord, kind: str, name: str, ns: str) -> None:
    if name in FALSE_DECLARATION_NAMES:
        return
    rows.append({
        "HeaderPath": rec.rel_path,
        "RootFolder": rec.root_folder,
        "DeclarationKind": kind,
        "Name": name,
        "NamespaceHints": ns,
    })


def extract_declarations(root: Path, records: Iterable[HeaderRecord]) -> List[Dict[str, str]]:
    rows: List[Dict[str, str]] = []
    for rec in records:
        if rec.empty:
            continue
        text = strip_cpp_comments(read_text(root / rec.rel_path))
        namespaces = sorted(set(NAMESPACE_RE.findall(text)))
        ns = ";".join(namespaces)

        for kind, name in CLASS_RE.findall(text):
            add_declaration(rows, rec, kind, name, ns)

        for name in ENUM_CLASS_RE.findall(text):
            add_declaration(rows, rec, "enum_class", name, ns)

        for name in ENUM_RE.findall(text):
            add_declaration(rows, rec, "enum", name, ns)

        for name in sorted(set(FUNCTION_RE.findall(text))):
            if name in FALSE_DECLARATION_NAMES:
                continue
            rows.append({
                "HeaderPath": rec.rel_path,
                "RootFolder": rec.root_folder,
                "DeclarationKind": "function_hint",
                "Name": name,
                "NamespaceHints": ns,
            })

        if TEMPLATE_RE.search(text):
            rows.append({
                "HeaderPath": rec.rel_path,
                "RootFolder": rec.root_folder,
                "DeclarationKind": "template_hint",
                "Name": "<template>",
                "NamespaceHints": ns,
            })

    return rows


def write_csv(path: Path, rows: List[Dict[str, object]], fieldnames: List[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def main() -> int:
    parser = argparse.ArgumentParser(description="Audit ASCC / Bridge Orchestrator headers.")
    parser.add_argument("--root", required=True, help="Path to include/assembler/bridge_orchestrator")
    parser.add_argument("--out", required=True, help="Output directory for audit reports")
    args = parser.parse_args()

    root = Path(args.root).resolve()
    out = Path(args.out).resolve()

    if not root.exists():
        raise SystemExit(f"root does not exist: {root}")

    records = collect_headers(root)

    inventory_rows = [{
        "HeaderPath": r.rel_path,
        "RootFolder": r.root_folder,
        "SizeBytes": r.size_bytes,
        "LineCount": r.line_count,
        "Empty": str(r.empty).lower(),
        "Classification": r.classification,
        "SHA256": r.sha256,
    } for r in records]

    zero_rows = [row for row in inventory_rows if row["Empty"] == "true"]
    includes = extract_includes(root, records)
    declarations = extract_declarations(root, records)

    root_counts = Counter(r.root_folder for r in records)
    empty_counts = Counter(r.root_folder for r in records if r.empty)
    root_summary_rows = []
    for folder in sorted(root_counts):
        total = root_counts[folder]
        empty = empty_counts[folder]
        root_summary_rows.append({
            "RootFolder": folder,
            "HeaderCount": total,
            "EmptyHeaderCount": empty,
            "NonEmptyHeaderCount": total - empty,
        })

    write_csv(out / "ascc_header_inventory.csv", inventory_rows,
              ["HeaderPath", "RootFolder", "SizeBytes", "LineCount", "Empty", "Classification", "SHA256"])
    write_csv(out / "ascc_zero_size_headers.csv", zero_rows,
              ["HeaderPath", "RootFolder", "SizeBytes", "LineCount", "Empty", "Classification", "SHA256"])
    write_csv(out / "ascc_includes.csv", includes,
              ["HeaderPath", "RootFolder", "Include", "IncludeClass"])
    write_csv(out / "ascc_declarations.csv", declarations,
              ["HeaderPath", "RootFolder", "DeclarationKind", "Name", "NamespaceHints"])
    write_csv(out / "ascc_root_summary.csv", root_summary_rows,
              ["RootFolder", "HeaderCount", "EmptyHeaderCount", "NonEmptyHeaderCount"])

    include_class_counts = Counter(row["IncludeClass"] for row in includes)
    declaration_kind_counts = Counter(row["DeclarationKind"] for row in declarations)

    duplicate_declarations = []
    by_name = defaultdict(list)
    for row in declarations:
        if row["DeclarationKind"] in {"class", "struct", "enum", "enum_class"}:
            by_name[row["Name"]].append(row["HeaderPath"])
    for name, paths in sorted(by_name.items()):
        if len(set(paths)) > 1:
            duplicate_declarations.append({"Name": name, "Paths": sorted(set(paths))})

    summary = {
        "root": str(root),
        "header_count": len(records),
        "empty_header_count": sum(1 for r in records if r.empty),
        "non_empty_header_count": sum(1 for r in records if not r.empty),
        "root_summary": root_summary_rows,
        "include_class_counts": dict(sorted(include_class_counts.items())),
        "declaration_kind_counts": dict(sorted(declaration_kind_counts.items())),
        "duplicate_declaration_name_hints": duplicate_declarations,
    }

    out.mkdir(parents=True, exist_ok=True)
    (out / "ascc_audit_summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    print(json.dumps({
        "header_count": summary["header_count"],
        "empty_header_count": summary["empty_header_count"],
        "output": str(out),
    }, indent=2))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
