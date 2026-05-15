#pragma once
#include "assembler/communication_context/diagnostics/collectors/TDiagnosticCollector.hpp"
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticRoutingPolicy.hpp"
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticRuntimeReport.hpp"

/**
 * @file TDiagnosticRuntime.hpp
 * @brief Component-level diagnostic runtime for ASCC.
 */
namespace assembler::communication_context {
    template <std::size_t RecordCapacity, std::size_t SourceCapacity>
    struct TDiagnosticRuntime final {
        TDiagnosticCollector<RecordCapacity> collector{};
        TDiagnosticRuntimeContext<SourceCapacity> context{};

        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return collector.is_valid() && context.is_valid();
        }

        constexpr bool collect(TDiagnosticSourceKind source, TDiagnosticRecord record) noexcept {
            if (!TDiagnosticRoutingPolicy::should_collect(context, source, record)) {
                ++collector.report.rejected_records;
                return false;
            }
            return collector.add(record);
        }

        [[nodiscard]] constexpr TDiagnosticRuntimeReport report() const noexcept {
            return TDiagnosticRuntimeReport{
                collector.report.count,
                collector.report.rejected_records,
                collector.report.failure_count(),
                collector.report.highest_severity(),
                context.sources.count
            };
        }
    };
}
