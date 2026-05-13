#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccReadinessEvidenceRef.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessIssue.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccReadinessReport.hpp
 * @brief Aggregate ASCC readiness report for W06 evidence aggregation.
 *
 * @section ascc_comp_w06 Purpose
 * This report aggregates lightweight evidence references and readiness issues
 * from participant, binding, protocol, session, bridge, diagnostics, and
 * registry surfaces. It is not a production readiness gate and it does not run
 * endpoints, sessions, protocols, bridges, or pipeline composition.
 */

namespace assembler::communication_context
{
    template <std::size_t EvidenceCapacity, std::size_t IssueCapacity>
    struct TAsccReadinessReport final
    {
        std::array<TAsccReadinessEvidenceRef, EvidenceCapacity> evidence{};
        std::array<TAsccReadinessIssue, IssueCapacity> issues{};
        std::size_t evidence_count{0u};
        std::size_t issue_count{0u};
        std::uint64_t rejected_evidence{0u};
        std::uint64_t rejected_issues{0u};
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        std::string_view report_name{"ascc_readiness_report"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return EvidenceCapacity > 0u
                && IssueCapacity > 0u
                && evidence_count <= EvidenceCapacity
                && issue_count <= IssueCapacity
                && status != TAsccReadinessStatus::unknown
                && !report_name.empty();
        }

        [[nodiscard]] constexpr bool full_evidence() const noexcept
        {
            return evidence_count >= EvidenceCapacity;
        }

        [[nodiscard]] constexpr bool full_issues() const noexcept
        {
            return issue_count >= IssueCapacity;
        }

        constexpr bool add_evidence(TAsccReadinessEvidenceRef ref) noexcept
        {
            if (!ref.is_valid() || full_evidence())
            {
                ++rejected_evidence;
                return false;
            }

            evidence[evidence_count] = ref;
            ++evidence_count;
            return true;
        }

        constexpr bool add_issue(TAsccReadinessIssue issue) noexcept
        {
            if (!issue.is_valid() || full_issues())
            {
                ++rejected_issues;
                return false;
            }

            issues[issue_count] = issue;
            ++issue_count;
            return true;
        }

        [[nodiscard]] constexpr std::size_t blocking_issue_count() const noexcept
        {
            std::size_t total{0u};
            for (std::size_t index = 0u; index < issue_count; ++index)
            {
                if (issues[index].blocks_core_readiness())
                {
                    ++total;
                }
            }
            return total;
        }

        [[nodiscard]] constexpr std::size_t deferred_issue_count() const noexcept
        {
            std::size_t total{0u};
            for (std::size_t index = 0u; index < issue_count; ++index)
            {
                if (issues[index].is_deferred())
                {
                    ++total;
                }
            }
            return total;
        }

        [[nodiscard]] constexpr std::size_t ready_evidence_count() const noexcept
        {
            std::size_t total{0u};
            for (std::size_t index = 0u; index < evidence_count; ++index)
            {
                if (evidence[index].is_ready_evidence())
                {
                    ++total;
                }
            }
            return total;
        }

        [[nodiscard]] constexpr std::size_t blocking_evidence_count() const noexcept
        {
            std::size_t total{0u};
            for (std::size_t index = 0u; index < evidence_count; ++index)
            {
                if (evidence[index].blocks_core_readiness())
                {
                    ++total;
                }
            }
            return total;
        }

        [[nodiscard]] constexpr bool passed_for_core() const noexcept
        {
            return is_valid()
                && !is_blocking_readiness_status(status)
                && blocking_issue_count() == 0u
                && blocking_evidence_count() == 0u;
        }

        [[nodiscard]] constexpr bool failed_for_core() const noexcept
        {
            return !passed_for_core();
        }

        [[nodiscard]] static constexpr TAsccReadinessReport make(
            TAsccReadinessStatus readiness_status = TAsccReadinessStatus::ready,
            std::string_view name = "ascc_readiness_report") noexcept
        {
            return TAsccReadinessReport{
                {},
                {},
                0u,
                0u,
                0u,
                0u,
                readiness_status,
                name
            };
        }
    };
}
