#pragma once
#include "../reports/TCirculationProductionReadinessReport.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace final_readiness {

struct TCirculationProductionReadinessGateView final {
    TCirculationProductionReadinessReport report{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return report.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return report.passed(); }
};
} // namespace final_readiness
} // namespace circulation_mechanism
} // namespace assembler
