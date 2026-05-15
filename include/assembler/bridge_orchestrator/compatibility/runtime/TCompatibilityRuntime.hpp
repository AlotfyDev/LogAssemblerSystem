#pragma once
#include "assembler/communication_context/compatibility/TCompatibilityEvaluator.hpp"
#include "assembler/communication_context/compatibility/reports/TCompatibilityRuntimeReport.hpp"
#include "assembler/communication_context/compatibility/runtime/TCompatibilityRuntimeContext.hpp"

/**
 * @file TCompatibilityRuntime.hpp
 * @brief Component-level compatibility runtime for ASCC readiness.
 */
namespace assembler::communication_context {
    struct TCompatibilityRuntime final {
        template <std::size_t MatrixCapacity>
        [[nodiscard]] static constexpr TCompatibilityRuntimeReport<MatrixCapacity> evaluate(TCompatibilityRuntimeContext context) noexcept {
            const auto matrix = TCompatibilityEvaluator::evaluate_strict_binding(context.binding);
            const auto coverage = TCompatibilityDimensionCoverageReport{
                context.participant_ready,
                context.channel_ready,
                context.binding_ready,
                context.obligation_ready,
                context.carrier_ready,
                context.session_ready,
                context.protocol_ready,
                "compatibility_dimension_coverage"
            };
            return {matrix, coverage, context.is_valid()};
        }
    };
}
