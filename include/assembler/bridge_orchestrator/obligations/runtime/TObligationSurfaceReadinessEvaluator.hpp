#pragma once
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"
#include "assembler/communication_context/obligations/surface_pairs/TObligationSurfacePair.hpp"

/**
 * @file TObligationSurfaceReadinessEvaluator.hpp
 * @brief Evaluates obligation surface pair readiness.
 */
namespace assembler::communication_context {
    struct TObligationSurfaceReadinessEvaluator final {
        [[nodiscard]] static constexpr TObligationReport evaluate_primary_placement(TObligationSurfacePair pair) noexcept {
            return pair.report_primary_placement_support();
        }
    };
}
