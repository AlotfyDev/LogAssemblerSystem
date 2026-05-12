#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/coverage/TAsccCoverageMatrix.hpp"

/**
 * @file TAsccComposabilityReport.hpp
 * @brief ASCC composability coverage summary report.
 */

namespace assembler::communication_context
{
    struct TAsccComposabilityReport final
    {
        std::string_view report_name{};
        std::size_t total_items{0u};
        std::size_t covered_items{0u};
        std::size_t blocked_items{0u};
        std::size_t deferred_items{0u};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !report_name.empty();
        }

        [[nodiscard]] constexpr bool passed_for_core() const noexcept
        {
            return is_valid() && blocked_items == 0u;
        }

        [[nodiscard]] constexpr bool failed_for_core() const noexcept
        {
            return !passed_for_core();
        }

        template <std::size_t Capacity>
        [[nodiscard]] static constexpr TAsccComposabilityReport from_matrix(
            const TAsccCoverageMatrix<Capacity>& matrix,
            std::string_view name = "ascc_composability_report",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccComposabilityReport{
                name,
                matrix.count,
                matrix.covered_count(),
                matrix.blocked_count(),
                matrix.deferred_count(),
                token
            };
        }
    };
}
