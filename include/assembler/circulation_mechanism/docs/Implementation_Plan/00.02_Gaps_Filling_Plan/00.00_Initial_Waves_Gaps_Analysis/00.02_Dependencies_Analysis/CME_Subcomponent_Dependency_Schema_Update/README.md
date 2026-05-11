# CME Subcomponent Dependency Schema Update

## Purpose

Adds dependency/dependent fields to the proposed subcomponent schema.

This supports the next analysis phase:

```text
Phase 1: Inter-component dependency analysis
Phase 2: Intra-component subcomponent dependency analysis
```

## Main New Fields

```text
parent_component_scope
subcomponent_scope
proposed_dependency_internal
proposed_dependent_internal
proposed_dependency_parent_components
proposed_dependent_parent_components
may_reveal_new_gaps
new_gap_detection_notes
```

## Files

```text
cme_proposed_subcomponents_with_dependency_fields.csv
cme_subcomponent_dependency_schema.csv
cme_intra_component_dependency_edge_schema.csv
summary.json
```

## Usage

Use `cme_proposed_subcomponents_with_dependency_fields.csv` as the seed for intra-component dependency analysis.

Use `cme_intra_component_dependency_edge_schema.csv` as the edge schema for the next package.
