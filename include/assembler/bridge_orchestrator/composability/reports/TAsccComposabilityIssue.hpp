#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/reports/TAsccComposabilitySeverity.hpp"

/**
 * @file TAsccComposabilityIssue.hpp
 * @brief One composability issue emitted from coverage/reporting evaluation.
 */

namespace assembler::communication_context
{
    struct TAsccComposabilityIssue final
    {
        std::uint64_t issue_id{0u};
        TAsccComposabilitySeverity severity{TAsccComposabilitySeverity::unknown};
        std::string_view component{};
        std::string_view note{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return issue_id != 0u
                && severity != TAsccComposabilitySeverity::unknown
                && !component.empty();
        }

        [[nodiscard]] constexpr bool blocks() const noexcept
        {
            return is_blocking(severity);
        }

        [[nodiscard]] static constexpr TAsccComposabilityIssue make(
            std::uint64_t id,
            TAsccComposabilitySeverity issue_severity,
            std::string_view component_name,
            std::string_view issue_note = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccComposabilityIssue{
                id,
                issue_severity,
                component_name,
                issue_note,
                token
            };
        }
    };
}
