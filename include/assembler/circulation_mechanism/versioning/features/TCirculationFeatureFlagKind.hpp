#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

enum class TCirculationFeatureFlagKind : std::uint8_t { pre_bridge_engine, read_side_engine, diagnostics_export, adapter_contracts, performance_benchmarks, concurrency_policy, legacy_compatibility_layer, experimental };
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler
