#pragma once
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowRuntime.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

/**
 * @file TObligationCarrierFlowBridge.hpp
 * @brief Bridges obligation invocation outcomes into carrier-flow runtime evidence.
 */
namespace assembler::communication_context {
    struct TObligationCarrierFlowBridge final {
        template <std::size_t Capacity>
        [[nodiscard]] static constexpr bool record(TCarrierFlowRuntime<Capacity>& runtime, TCarrierView carrier, TCarrierFlowDirection direction) noexcept {
            return runtime.accept_record(TCarrierFlowRecord{carrier, direction, carrier.correlation, "obligation", "obligation carrier flow"});
        }
    };
}
