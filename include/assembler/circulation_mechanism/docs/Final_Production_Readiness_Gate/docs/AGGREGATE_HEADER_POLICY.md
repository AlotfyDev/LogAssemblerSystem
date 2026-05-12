# AGGREGATE_HEADER_POLICY — CME-PROD-HARDEN-W01

## 1. Canonical Root Aggregates

```text
circulation_mechanism.hpp
circulation_mechanism_bundle_agent.hpp
circulation_mechanism_capacity.hpp
circulation_mechanism_communication_bindings.hpp
circulation_mechanism_container.hpp
circulation_mechanism_container_registry.hpp
circulation_mechanism_diagnostics.hpp
circulation_mechanism_dispatcher.hpp
circulation_mechanism_eviction.hpp
circulation_mechanism_ids.hpp
circulation_mechanism_ingress.hpp
circulation_mechanism_moderator.hpp
circulation_mechanism_production_readiness.hpp
circulation_mechanism_read_side_profile.hpp
circulation_mechanism_reference_precalculator.hpp
circulation_mechanism_release_recycle.hpp
circulation_mechanism_reports.hpp
circulation_mechanism_round_manager.hpp
circulation_mechanism_safe_points.hpp
circulation_mechanism_slot.hpp
circulation_mechanism_state.hpp
circulation_mechanism_views.hpp
```

## 2. Full Domain Aggregate

```text
circulation_mechanism.hpp
```

## 3. Policy

1. Use component production aggregates for component-level inclusion.
2. Use `circulation_mechanism.hpp` for full-domain integration only.
3. Do not use legacy wave aggregate headers from root.
4. Read-side profile is included through `circulation_mechanism_read_side_profile.hpp`.
5. Type owners must be included from canonical owner paths.
