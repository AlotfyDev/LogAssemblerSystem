# CME-PRD-MAP-001 Verification Asset Transfer Mapping

## Purpose

This document defines the official transfer mapping from source-wave verification assets into the unified package verification spine.

It is the direct execution reference for:

- `PRD-014` compile verification
- `PRD-015` smoke verification
- `PRD-016` gate-report verification
- `PRD-017` compatibility leakage verification
- `PRD-018` benchmark and stress scope

## Scope

This mapping classifies source-wave artifacts into exactly four destination groups:

1. move to `tests/compile`
2. move to `tests/smoke`
3. move to `tests/benchmarks`
4. keep as evidence-only

## Move To `tests/compile`

| Source wave(s) | Exact source file / artifact family | Target destination | Rationale |
|---|---|---|---|
| `00.01` | `tests/cme_full_system_all_aggregates_compile_test.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_full_aggregate.cpp` | Canonical aggregate compile probe already matches `PRD-014` isolated TU coverage. |
| `00.02` | `tests_hardening_w02/*full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_runtime_diagnostics_surface.cpp` or adjacent compile TU(s) | These are subsystem compile probes for runtime-core surfaces, not behavior-first smoke tests. |
| `00.03` | `tests_prebridge_w01/*full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_pre_bridge_surface.cpp` | PreBridge aggregate-probe assets map directly to standalone surface compilation checks. |
| `00.06` | `tests_readside_w01/cme_readside_full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_read_side_surface.cpp` | ReadSide facade compile coverage belongs in the canonical compile matrix. |
| `00.07` | `tests_readside_w02/cme_readside_runtime_lists_full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_read_side_surface.cpp` or focused compile TU | Runtime-list aggregate assembly is a compile-surface concern. |
| `00.08` | `tests_readside_w03/cme_readside_admission_full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_read_side_surface.cpp` or focused compile TU | Admission/backpressure aggregate viability is best preserved as compile verification. |
| `00.09` | `tests_readside_w04/cme_readside_adapter_contracts_full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_read_side_surface.cpp` or focused compile TU | Adapter-contract aggregate coverage is structural and compile-oriented. |
| `00.11` | `tests_hardening_w03/cme_diagnostic_export_full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_runtime_diagnostics_surface.cpp` | Diagnostic export aggregate assembly belongs in runtime/diagnostics compile coverage. |
| `00.14` | `tests_hardening_w06/cme_concurrency_full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_canonical_combo.cpp` or focused concurrency compile TU | Concurrency policy surface is a structural compile target under `PRD-014`. |
| `00.15` | `tests_hardening_w07/cme_versioning_full_aggregate_probe.cpp` | `include/assembler/circulation_mechanism/tests/compile/compile_readiness_combo.cpp` or focused versioning compile TU | Versioning/compatibility surface belongs in repeatable aggregate compile verification. |

## Move To `tests/smoke`

| Source wave(s) | Exact source file / artifact family | Target destination | Rationale |
|---|---|---|---|
| `00.01` | `tests/cme_production_readiness_gate_pass_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/verify_production_gate_contract.cpp` | This is already a production-gate success-path asset and fits `PRD-016`. |
| `00.01` | `tests/cme_production_readiness_gate_negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/verify_production_gate_contract.cpp` or sibling negative smoke test | Negative gate behavior is part of readiness smoke semantics, not pure compile coverage. |
| `00.01` | `tests/cme_end_to_end_circulation_flow_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_full_package.cpp` | It exercises a production-facing end-to-end path and belongs in canonical smoke coverage. |
| `00.02` | `tests_hardening_w02/cme_runtime_core_configuration_lifecycle_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_full_package.cpp` or focused runtime smoke test | Runtime lifecycle/configuration validation is behavioral smoke coverage. |
| `00.02` | `tests_hardening_w02/*negative_compliance_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | These validate public-surface misuse/failure semantics rather than isolated compilation. |
| `00.03` | `tests_prebridge_w01/cme_prebridge_engine_facade_injection_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_pre_bridge_profile.cpp` | Facade injection is a canonical PreBridge usage-path smoke scenario. |
| `00.03` | `tests_prebridge_w01/*negative_independence_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_pre_bridge_profile.cpp` or sibling negative smoke test | Independence semantics should remain executable smoke coverage for the subsystem boundary. |
| `00.04` | `tests_prebridge_w02/cme_prebridge_default_injection_profile_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_pre_bridge_profile.cpp` | Default injection profile is a consumer-facing PreBridge path. |
| `00.04` | `tests_prebridge_w02/*negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | These preserve behavioral guardrails around the canonical PreBridge profile. |
| `00.05` | `tests_prebridge_w03/pre_bridge_e2e_flow_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_pre_bridge_profile.cpp` | This is the strongest reusable PreBridge end-to-end smoke asset. |
| `00.05`, `00.13` | `examples/pre_bridge_basic_flow.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_pre_bridge_profile.cpp` | Consumer-facing example should be normalized into executable smoke coverage. |
| `00.06` | `tests_readside_w01/cme_readside_engine_facade_injection_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_engine.cpp` | ReadSide engine facade injection is a canonical usage-path smoke scenario. |
| `00.06` | `tests_readside_w01/cme_readside_engine_negative_independence_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_engine.cpp` or sibling negative smoke test | Independence constraints are subsystem behavior and should stay executable. |
| `00.07` | `tests_readside_w02/cme_readside_runtime_lists_flow_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_runtime_lists.cpp` | Runtime-list flow is a direct match for `PRD-015.3`. |
| `00.07` | `tests_readside_w02/cme_readside_runtime_lists_negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_runtime_lists.cpp` or sibling negative smoke test | Runtime-list constraints belong in behavioral smoke coverage. |
| `00.08` | `tests_readside_w03/cme_readside_receiver_admission_runtime_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_profile.cpp` or focused admission smoke test | Admission/backpressure behavior is canonical ReadSide operational smoke coverage. |
| `00.08` | `tests_readside_w03/cme_readside_receiver_admission_negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | Negative admission semantics should remain verified at smoke level. |
| `00.09` | `tests_readside_w04/cme_readside_adapter_contracts_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_profile.cpp` or focused adapter smoke test | Adapter-contract behavior is a production-facing ReadSide integration path. |
| `00.09` | `tests_readside_w04/cme_readside_adapter_contracts_negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | Contract misuse/failure belongs in behavioral smoke coverage. |
| `00.10`, `00.13` | `tests_readside_w05/read_side_e2e_flow_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_engine.cpp` | This is the highest-value reusable ReadSide end-to-end smoke asset. |
| `00.10`, `00.13` | `examples/read_side_basic_flow.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_profile.cpp` | Consumer onboarding example maps cleanly to canonical ReadSide smoke. |
| `00.10`, `00.13` | `examples/read_side_retry_flow.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_runtime_lists.cpp` | Retry flow is an executable runtime-lists smoke path. |
| `00.10`, `00.13` | `examples/read_side_backpressure_flow.cpp` | `include/assembler/circulation_mechanism/tests/smoke/smoke_read_side_profile.cpp` or focused admission smoke test | Backpressure flow is a canonical ReadSide behavioral scenario. |
| `00.11` | `tests_hardening_w03/cme_unified_diagnostics_collector_export_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/verify_diagnostic_export_gate_report.cpp` | Diagnostics/export behavior aligns directly with `PRD-016.2`. |
| `00.11` | `tests_hardening_w03/cme_unified_diagnostics_negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/verify_diagnostic_export_gate_report.cpp` or sibling negative test | Export-boundary failure semantics are smoke-level verification. |
| `00.14` | `tests_hardening_w06/cme_concurrency_policy_acceptance_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | Concurrency policy acceptance is production-facing subsystem behavior. |
| `00.14` | `tests_hardening_w06/cme_concurrency_policy_negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | Negative concurrency-policy behavior should remain executable, not compile-only. |
| `00.15` | `tests_hardening_w07/cme_versioning_compatibility_policy_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | Versioning/compatibility policy is a production-facing behavior path. |
| `00.15` | `tests_hardening_w07/cme_versioning_negative_test.cpp` | `include/assembler/circulation_mechanism/tests/smoke/` | Negative compatibility semantics belong in smoke verification. |

## Move To `tests/benchmarks`

| Source wave(s) | Exact source file / artifact family | Target destination | Rationale |
|---|---|---|---|
| `00.13` | all benchmark source files under `benchmarks/` | `include/assembler/circulation_mechanism/tests/benchmarks/` | The source-trace document marks the full benchmark set as reusable benchmark harnesses. |
| `00.13` | `benchmarks/cme_benchmark_common.hpp` | `include/assembler/circulation_mechanism/tests/benchmarks/cme_benchmark_common.hpp` | Shared benchmark support belongs with the normalized benchmark root. |
| `00.13` | `stress_tests/capacity_extreme_profile_stress.cpp` | `include/assembler/circulation_mechanism/tests/benchmarks/bench_capacity_profiles.cpp` or `stress_capacity_extreme_profile.cpp` | Stress capacity coverage is part of the explicit benchmark/stress acceptance scope in `PRD-018`. |

## Keep As Evidence-Only

| Source wave(s) | Exact source file / artifact family | Target destination | Rationale |
|---|---|---|---|
| all waves | all `*_TEST_REPORT.csv` | no move; retain under source/evidence references only | The source-trace document classifies all CSV reports as traceability evidence, not production-suite assets. |
| `00.01` and carried waves | `ANTI_COLLAPSE_TEST_REPORT.csv`, `INTEGRATION_TEST_REPORT.csv`, `PRODUCTION_READINESS_TEST_REPORT.csv` | no move; evidence-only | These are snapshot closure reports, not reusable normalized tests. |
| all waves | `tests_canonical/*` | no move; evidence-only unless re-authored later | The source-trace document treats many canonical probes as wave-local or snapshot rather than final-suite candidates. |
| all waves | `GAP_CLOSURE_NOTES.md` | no move; evidence-only | Closure notes document historical wave completion, not reusable verification logic. |
| all waves | `WAVE_MANIFEST.json`, `COMPILE_CHECK.json` | no move; evidence-only | These are wave snapshot manifests/check records, superseded by new Phase11 manifests. |
| `00.00` | planning package artifacts under `README.md`, `docs/`, `csv/`, `diagrams/`, `manifest.json` | no move; keep as governance/evidence references | `00.00` is the governing readiness contract, not a source of tests to relocate. |
| `00.05` | `examples/pre_bridge_with_logapi_binding.cpp` | no move; evidence/example-only | The source-trace document marks it example-only and not part of the generic production gate. |
| `00.12` | duplicate rollback/re-baseline snapshot as a whole | no move; evidence-only | `00.12` is explicitly not a forward evolution source and should not seed normalized verification assets. |

## Direct Execution Use

This mapping must be used as the direct selection reference when executing:

1. `PRD-014` compile matrix construction,
2. `PRD-015` smoke suite construction,
3. `PRD-016` readiness and diagnostic-export gate verification,
4. `PRD-017` compatibility leakage verification,
5. `PRD-018` benchmark and stress scope construction.

The required execution rule is:

1. do not import CSV reports into executable test roots,
2. do not import wave manifests or closure notes into executable test roots,
3. prefer consumer-facing examples and reusable subsystem tests over wave-local probes,
4. treat duplicate wave `00.12` as historical evidence only.
