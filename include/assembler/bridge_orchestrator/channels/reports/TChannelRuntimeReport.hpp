#pragma once
#include "assembler/communication_context/channels/reports/TChannelTransitionReport.hpp"
#include "assembler/communication_context/channels/runtime/TChannelRuntimeContext.hpp"

/**
 * @file TChannelRuntimeReport.hpp
 * @brief Aggregate runtime report for ASCC channel readiness and lifecycle.
 */
namespace assembler::communication_context {
    struct TChannelRuntimeReport final {
        TChannelRuntimeContext context{};
        TChannelTransitionReport transition{};
        bool binding_bridge_ready{false};
        bool session_preparation_ready{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return context.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return context.ready() && binding_bridge_ready && session_preparation_ready; }
    };
}
