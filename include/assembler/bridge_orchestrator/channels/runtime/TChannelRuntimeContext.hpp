#pragma once
#include "assembler/communication_context/channels/runtime/TChannelReadinessView.hpp"

/**
 * @file TChannelRuntimeContext.hpp
 * @brief Runtime context for a channel admitted into ASCC component operation.
 */
namespace assembler::communication_context {
    struct TChannelRuntimeContext final {
        TChannelReadinessView readiness{};
        bool admitted{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return readiness.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && admitted && readiness.ready(); }
    };
}
