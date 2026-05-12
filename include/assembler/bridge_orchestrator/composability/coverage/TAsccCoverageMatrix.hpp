#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/coverage/TAsccCoverageItem.hpp"

/**
 * @file TAsccCoverageMatrix.hpp
 * @brief Fixed-capacity ASCC composability coverage matrix.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccCoverageMatrix final
    {
        std::array<TAsccCoverageItem, Capacity> items{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view matrix_name{"ascc_coverage_matrix"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !matrix_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        constexpr bool add(TAsccCoverageItem item) noexcept
        {
            if (!is_valid() || full() || !item.is_valid())
            {
                ++rejected_insertions;
                return false;
            }

            items[count] = item;
            ++count;
            return true;
        }

        [[nodiscard]] constexpr std::size_t blocked_count() const noexcept
        {
            std::size_t result{0u};
            for (std::size_t index = 0u; index < count; ++index)
            {
                if (items[index].blocks_core_readiness())
                {
                    ++result;
                }
            }
            return result;
        }

        [[nodiscard]] constexpr std::size_t deferred_count() const noexcept
        {
            std::size_t result{0u};
            for (std::size_t index = 0u; index < count; ++index)
            {
                if (items[index].is_deferred())
                {
                    ++result;
                }
            }
            return result;
        }

        [[nodiscard]] constexpr std::size_t covered_count() const noexcept
        {
            std::size_t result{0u};
            for (std::size_t index = 0u; index < count; ++index)
            {
                if (is_covered(items[index].state))
                {
                    ++result;
                }
            }
            return result;
        }

        [[nodiscard]] constexpr bool has_blocking_core_items() const noexcept
        {
            return blocked_count() > 0u;
        }

        [[nodiscard]] static constexpr TAsccCoverageMatrix make(
            std::string_view name = "ascc_coverage_matrix",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccCoverageMatrix{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
