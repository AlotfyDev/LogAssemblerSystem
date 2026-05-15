#pragma once
#include <cstdint>
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"

/**
 * @file TIntegrationBoundaryRetryPolicy.hpp
 * @brief Retry/defer policy for integration boundary handoff.
 */
namespace assembler::communication_context {
    struct TIntegrationBoundaryRetryPolicy final {
        std::uint32_t max_retries{0u};
        [[nodiscard]] constexpr bool allows_retry(TBoundaryHandoffResult result, std::uint32_t attempt) const noexcept {
            return result.deferred() && attempt < max_retries;
        }
    };
}
