#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/coverage/TAsccCoverageItem.hpp"
#include "assembler/communication_context/composability/reports/TAsccComposabilitySeverity.hpp"

/**
 * @file TAsccCoverageGap.hpp
 * @brief Derived gap report item produced from incomplete coverage.
 */

namespace assembler::communication_context
{
    struct TAsccCoverageGap final
    {
        std::uint64_t gap_id{0u};
        TAsccCoverageItem coverage{};
        TAsccComposabilitySeverity severity{TAsccComposabilitySeverity::unknown};
        std::string_view note{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return gap_id != 0u
                && coverage.is_valid()
                && severity != TAsccComposabilitySeverity::unknown;
        }

        [[nodiscard]] constexpr bool blocks_core_readiness() const noexcept
        {
            return coverage.blocks_core_readiness() && is_blocking(severity);
        }

        [[nodiscard]] static constexpr TAsccCoverageGap from_coverage(
            std::uint64_t id,
            TAsccCoverageItem item,
            TAsccComposabilitySeverity gap_severity,
            std::string_view gap_note = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccCoverageGap{
                id,
                item,
                gap_severity,
                gap_note,
                token
            };
        }
    };
}
