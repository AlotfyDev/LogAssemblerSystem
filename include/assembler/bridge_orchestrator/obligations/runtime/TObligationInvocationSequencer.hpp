#pragma once
#include <cstdint>
#include <string_view>

/**
 * @file TObligationInvocationSequencer.hpp
 * @brief Static sequencing vocabulary for ASCC obligation invocation flow.
 */
namespace assembler::communication_context {
    enum class TObligationInvocationStep {
        unknown,
        adapter_readiness,
        adapter_prepare_request,
        port_readiness,
        port_admit,
        port_placement_handle,
        adapter_accept_handle,
        adapter_emit_load_signal,
        port_receive_load_signal,
        adapter_next_destination_request,
        port_next_destination
    };

    struct TObligationInvocationSequencer final {
        [[nodiscard]] static constexpr std::uint32_t order(TObligationInvocationStep step) noexcept {
            switch (step) {
                case TObligationInvocationStep::adapter_readiness: return 1u;
                case TObligationInvocationStep::adapter_prepare_request: return 2u;
                case TObligationInvocationStep::port_readiness: return 3u;
                case TObligationInvocationStep::port_admit: return 4u;
                case TObligationInvocationStep::port_placement_handle: return 5u;
                case TObligationInvocationStep::adapter_accept_handle: return 6u;
                case TObligationInvocationStep::adapter_emit_load_signal: return 7u;
                case TObligationInvocationStep::port_receive_load_signal: return 8u;
                case TObligationInvocationStep::adapter_next_destination_request: return 9u;
                case TObligationInvocationStep::port_next_destination: return 10u;
                case TObligationInvocationStep::unknown: return 0u;
            }
            return 0u;
        }
    };
}
