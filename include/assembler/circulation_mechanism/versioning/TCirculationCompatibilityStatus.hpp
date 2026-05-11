#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

enum class TCirculationCompatibilityStatus : std::uint8_t { unknown, compatible, compatible_with_deprecation, requires_migration, incompatible, blocked };
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler
