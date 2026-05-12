#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/diagnostics/policies/TDiagnosticPolicy.hpp"
#include "assembler/communication_context/diagnostics/records/TDiagnosticRecord.hpp"

/**
 * @file TDiagnosticReport.hpp
 * @brief Bounded diagnostic report for endpoint-neutral diagnostics.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - fixed-capacity report of diagnostic records;
 * - summary counts for severity and failure state;
 * - no persistence, logging sink, telemetry exporter, or dynamic allocation.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - report metadata and bounded record array;
 * - append and policy-filtered append helpers;
 * - summary helpers for warnings/errors/critical failures.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - telemetry exporters;
 * - logging framework integration;
 * - persistence, database, file IO, or network IO;
 * - runtime scheduling, service locator, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - endpoint-domain internals;
 * - concrete adapter/port invocation;
 * - ownership or mutation of diagnosed objects;
 * - replacement of Bridge, Protocol, Session, Binding, Channel, Registry, or
 *   concrete binding semantics.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W12 may depend on W01-W11 public Communication Context surfaces.
 * It must remain optional and diagnostic-only. It must not be required by W14
 * concrete bindings or W15 first integration skeleton.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TDiagnosticReport final
    {
        std::array<TDiagnosticRecord, Capacity> records{};
        std::size_t count{0u};
        std::uint64_t rejected_records{0u};
        std::string_view report_name{"diagnostic_report"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !report_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return count == 0u;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        constexpr bool append(TDiagnosticRecord record) noexcept
        {
            if (!is_valid() || full() || !record.is_valid())
            {
                ++rejected_records;
                return false;
            }

            records[count] = record;
            ++count;
            return true;
        }

        constexpr bool append_if_included(
            TDiagnosticRecord record,
            TDiagnosticPolicy policy) noexcept
        {
            if (!policy.includes(record))
            {
                return true;
            }

            return append(record);
        }

        [[nodiscard]] constexpr std::size_t count_at_least(
            TDiagnosticSeverity minimum) const noexcept
        {
            std::size_t total = 0u;

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (severity_at_least(records[index].severity, minimum))
                {
                    ++total;
                }
            }

            return total;
        }

        [[nodiscard]] constexpr std::size_t failure_count() const noexcept
        {
            std::size_t total = 0u;

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (records[index].failed())
                {
                    ++total;
                }
            }

            return total;
        }

        [[nodiscard]] constexpr bool has_failures() const noexcept
        {
            return failure_count() > 0u;
        }

        [[nodiscard]] constexpr TDiagnosticSeverity highest_severity() const noexcept
        {
            TDiagnosticSeverity highest{TDiagnosticSeverity::none};

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (severity_rank(records[index].severity) > severity_rank(highest))
                {
                    highest = records[index].severity;
                }
            }

            return highest;
        }

        [[nodiscard]] static constexpr TDiagnosticReport make(
            std::string_view name = "diagnostic_report",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TDiagnosticReport{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
