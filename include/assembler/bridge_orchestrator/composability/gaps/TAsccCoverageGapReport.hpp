#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/gaps/TAsccCoverageGap.hpp"

/**
 * @file TAsccCoverageGapReport.hpp
 * @brief Fixed-capacity derived coverage-gap report.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccCoverageGapReport final
    {
        std::array<TAsccCoverageGap, Capacity> gaps{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view report_name{"ascc_coverage_gap_report"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !report_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        constexpr bool add(TAsccCoverageGap gap) noexcept
        {
            if (!is_valid() || full() || !gap.is_valid())
            {
                ++rejected_insertions;
                return false;
            }

            gaps[count] = gap;
            ++count;
            return true;
        }

        [[nodiscard]] constexpr std::size_t blocking_count() const noexcept
        {
            std::size_t result{0u};
            for (std::size_t index = 0u; index < count; ++index)
            {
                if (gaps[index].blocks_core_readiness())
                {
                    ++result;
                }
            }
            return result;
        }

        [[nodiscard]] constexpr bool blocks_core_readiness() const noexcept
        {
            return blocking_count() > 0u;
        }

        [[nodiscard]] static constexpr TAsccCoverageGapReport make(
            std::string_view name = "ascc_coverage_gap_report",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccCoverageGapReport{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
