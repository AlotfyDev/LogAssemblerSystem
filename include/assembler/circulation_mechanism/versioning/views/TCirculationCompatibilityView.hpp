#pragma once
#include "../reports/TCirculationCompatibilityReport.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace versioning {

struct TCirculationCompatibilityView final {
    TCirculationCompatibilityReport report{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report.is_valid(); }
    [[nodiscard]] constexpr bool compatible() const noexcept { return report.compatible(); }
};
} // namespace versioning
} // namespace circulation_mechanism
} // namespace assembler
