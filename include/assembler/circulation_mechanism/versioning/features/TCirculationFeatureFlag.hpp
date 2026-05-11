#pragma once
#include "TCirculationFeatureFlagKind.hpp"
#include "TCirculationFeatureFlagState.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationFeatureFlag final {
    TCirculationFeatureFlagKind kind{TCirculationFeatureFlagKind::experimental};
    TCirculationFeatureFlagState state{TCirculationFeatureFlagState::disabled};
    [[nodiscard]] constexpr bool enabled() const noexcept {
        return state == TCirculationFeatureFlagState::enabled || state == TCirculationFeatureFlagState::deprecated || state == TCirculationFeatureFlagState::experimental;
    }
    [[nodiscard]] constexpr bool blocked() const noexcept { return state == TCirculationFeatureFlagState::blocked; }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler
