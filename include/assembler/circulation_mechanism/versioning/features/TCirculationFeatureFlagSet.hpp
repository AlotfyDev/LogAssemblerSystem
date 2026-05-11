#pragma once
#include "TCirculationFeatureFlag.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationFeatureFlagSet final {
    TCirculationFeatureFlag pre_bridge{TCirculationFeatureFlagKind::pre_bridge_engine, TCirculationFeatureFlagState::enabled};
    TCirculationFeatureFlag read_side{TCirculationFeatureFlagKind::read_side_engine, TCirculationFeatureFlagState::enabled};
    TCirculationFeatureFlag diagnostics_export{TCirculationFeatureFlagKind::diagnostics_export, TCirculationFeatureFlagState::enabled};
    TCirculationFeatureFlag adapter_contracts{TCirculationFeatureFlagKind::adapter_contracts, TCirculationFeatureFlagState::enabled};
    TCirculationFeatureFlag performance_benchmarks{TCirculationFeatureFlagKind::performance_benchmarks, TCirculationFeatureFlagState::enabled};
    TCirculationFeatureFlag concurrency_policy{TCirculationFeatureFlagKind::concurrency_policy, TCirculationFeatureFlagState::enabled};
    TCirculationFeatureFlag legacy_compatibility_layer{TCirculationFeatureFlagKind::legacy_compatibility_layer, TCirculationFeatureFlagState::deprecated};
    [[nodiscard]] constexpr bool required_production_features_enabled() const noexcept {
        return pre_bridge.enabled() && read_side.enabled() && diagnostics_export.enabled() && adapter_contracts.enabled() && performance_benchmarks.enabled() && concurrency_policy.enabled() && !pre_bridge.blocked() && !read_side.blocked();
    }
    [[nodiscard]] constexpr bool uses_deprecated_legacy_compatibility() const noexcept {
        return legacy_compatibility_layer.state == TCirculationFeatureFlagState::deprecated;
    }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler
