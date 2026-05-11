# CME Dependency Analysis — Inter Component

## Files

```text
csv/CME-DEP-001_Component_Dependency_Edges.csv
csv/CME-DEP-002_Component_Dependency_Matrix.csv
csv/CME-DEP-003_Component_Dependency_Summary.csv
csv/CME-DEP-004_Dependency_Classification_Schema.csv
docs/CME-DEP-000_Method.md
docs/CME-DEP-001_Findings.md
```

## Counts

```text
components: 21
dependency edges: 126
```

## Query Examples

- Who depends on ReferencePrecalculator?
  - filter `target_component_key = reference_precalculator`
- What does Dispatcher depend on?
  - filter `source_component_key = dispatcher`
- Strong dependencies only:
  - filter `dependency_strength = strong`
