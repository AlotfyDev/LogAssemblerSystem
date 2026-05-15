#pragma once
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/diagnostics/policies/TDiagnosticPolicy.hpp"
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticSourceRegistry.hpp"

/**
 * @file TDiagnosticRuntimeContext.hpp
 * @brief Runtime context for ASCC component-level diagnostics.
 */
namespace assembler::communication_context {
    template <std::size_t SourceCapacity>
    struct TDiagnosticRuntimeContext final {
        TDiagnosticPolicy policy{};
        TDiagnosticSourceRegistry<SourceCapacity> sources{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        bool diagnostics_enabled{true};

        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return sources.is_valid();
        }
    };
}
