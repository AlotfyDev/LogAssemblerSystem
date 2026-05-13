#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccEvidenceDimension.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccReadinessIssue.hpp
 * @brief Generic readiness issue emitted by ASCC evidence aggregation.
 */

namespace assembler::communication_context
{
    struct TAsccReadinessIssue final
    {
        std::uint64_t issue_id{0u};
        TAsccEvidenceDimension dimension{TAsccEvidenceDimension::unknown};
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        bool blocking{false};
        std::string_view component{};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return issue_id != 0u
                && dimension != TAsccEvidenceDimension::unknown
                && status != TAsccReadinessStatus::unknown
                && !component.empty();
        }

        [[nodiscard]] constexpr bool blocks_core_readiness() const noexcept
        {
            return blocking || is_blocking_readiness_status(status);
        }

        [[nodiscard]] constexpr bool is_deferred() const noexcept
        {
            return is_deferred_readiness_status(status);
        }

        [[nodiscard]] static constexpr TAsccReadinessIssue make(
            std::uint64_t id,
            TAsccEvidenceDimension issue_dimension,
            TAsccReadinessStatus issue_status,
            std::string_view component_name,
            bool is_blocking_issue = false,
            std::string_view issue_note = {}) noexcept
        {
            return TAsccReadinessIssue{
                id,
                issue_dimension,
                issue_status,
                is_blocking_issue,
                component_name,
                issue_note
            };
        }
    };
}
