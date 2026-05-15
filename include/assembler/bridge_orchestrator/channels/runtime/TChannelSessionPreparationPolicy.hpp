#pragma once
#include "assembler/communication_context/channels/runtime/TChannelRuntimeContext.hpp"

/**
 * @file TChannelSessionPreparationPolicy.hpp
 * @brief Determines whether an admitted channel can prepare a session-open path.
 */
namespace assembler::communication_context {
    struct TChannelSessionPreparationPolicy final {
        [[nodiscard]] static constexpr bool can_prepare_session(TChannelRuntimeContext context) noexcept {
            return context.ready();
        }
    };
}
