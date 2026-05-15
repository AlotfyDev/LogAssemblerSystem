#pragma once
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"
#include "assembler/communication_context/integration_boundaries/descriptors/TIntegrationBoundaryDescriptor.hpp"
#include "assembler/communication_context/integration_boundaries/policies/TIntegrationBoundaryPolicy.hpp"

/**
 * @file TIntegrationBoundaryRuntimeContext.hpp
 * @brief Runtime context for an ASCC integration boundary handoff.
 */
namespace assembler::communication_context {
    struct TIntegrationBoundaryRuntimeContext final {
        TIntegrationBoundaryDescriptor descriptor{};
        TIntegrationBoundaryPolicy policy{};
        TBoundaryHandoffRequest request{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return descriptor.is_valid() && request.is_valid(); }
    };
}
