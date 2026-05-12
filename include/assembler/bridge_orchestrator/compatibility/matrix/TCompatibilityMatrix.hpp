#pragma once

#include <array>
#include <cstddef>

#include "assembler/communication_context/compatibility/issues/TCompatibilityIssue.hpp"

/**
 * @file TCompatibilityMatrix.hpp
 * @brief Fixed-capacity compatibility diagnostic matrix.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative compatibility
 * model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - compact aggregation of compatibility issues across dimensions;
 * - deterministic capacity suitable for header-only compile-time use;
 * - future extension point for validation reports and bridge setup
 *   diagnostics.
 *
 * @section ascc_current_wave Current W07 Implementation Scope
 * This W07 version intentionally implements only compatibility classification,
 * rule modeling, issue reporting, matrix aggregation, and evaluator helpers.
 * It builds on W06 binding declarations and W05 obligation surfaces, but it
 * does not allocate sessions, execute protocols, orchestrate bridges, invoke
 * endpoint domains, or mutate endpoint lifecycle.
 *
 * - fixed-capacity issue array;
 * - add helpers that preserve first issues up to capacity;
 * - blocking, warning, fatal, and pass/fail helpers;
 * - deterministic count helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - session lifecycle or session execution;
 * - protocol stepping or bridge orchestration;
 * - endpoint-domain validation internals;
 * - concrete adapter-port invocation;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - dynamic allocation, logging backend, or persistent diagnostics store.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Compatibility model headers may depend on W01 carriers/results, W03
 * participant views, W04 channel topology, W05 obligation-surface views, and
 * W06 binding model declarations. They must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TCompatibilityMatrix final
    {
        std::array<TCompatibilityIssue, Capacity> issues{};
        std::size_t issue_count{0u};

        [[nodiscard]] constexpr std::size_t capacity() const noexcept
        {
            return Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return issue_count >= Capacity;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return issue_count == 0u;
        }

        constexpr bool add(TCompatibilityIssue issue) noexcept
        {
            if (issue.is_clean())
            {
                return true;
            }

            if (full())
            {
                return false;
            }

            issues[issue_count] = issue;
            ++issue_count;
            return true;
        }

        [[nodiscard]] constexpr std::size_t blocking_count() const noexcept
        {
            std::size_t count = 0u;

            for (std::size_t index = 0u; index < issue_count; ++index)
            {
                if (issues[index].is_blocking_issue())
                {
                    ++count;
                }
            }

            return count;
        }

        [[nodiscard]] constexpr std::size_t warning_count() const noexcept
        {
            std::size_t count = 0u;

            for (std::size_t index = 0u; index < issue_count; ++index)
            {
                if (issues[index].severity == TCompatibilitySeverity::warning)
                {
                    ++count;
                }
            }

            return count;
        }

        [[nodiscard]] constexpr bool has_blocking_issues() const noexcept
        {
            return blocking_count() > 0u;
        }

        [[nodiscard]] constexpr bool has_warnings() const noexcept
        {
            return warning_count() > 0u;
        }

        [[nodiscard]] constexpr bool compatible() const noexcept
        {
            return !has_blocking_issues();
        }

        [[nodiscard]] constexpr const TCompatibilityIssue& first_issue() const noexcept
        {
            return issues[0];
        }
    };
}
