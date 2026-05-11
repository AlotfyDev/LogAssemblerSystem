#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

enum class TCirculationFeatureFlagState : std::uint8_t { disabled, enabled, deprecated, blocked, experimental };
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler
