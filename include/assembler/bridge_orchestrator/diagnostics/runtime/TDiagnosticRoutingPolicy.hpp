#pragma once
#include "assembler/communication_context/diagnostics/records/TDiagnosticRecord.hpp"
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticRuntimeContext.hpp"
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticSourceKind.hpp"

/**
 * @file TDiagnosticRoutingPolicy.hpp
 * @brief Routing policy for diagnostic records into ASCC diagnostic runtime.
 */
namespace assembler::communication_context {
    struct TDiagnosticRoutingPolicy final {
        template <std::size_t SourceCapacity>
        [[nodiscard]] static constexpr bool should_collect(
            const TDiagnosticRuntimeContext<SourceCapacity>& context,
            TDiagnosticSourceKind source,
            TDiagnosticRecord record) noexcept
        {
            return context.diagnostics_enabled
                && context.is_valid()
                && context.sources.includes(source)
                && context.policy.includes(record);
        }
    };
}
