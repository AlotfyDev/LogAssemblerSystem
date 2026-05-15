#pragma once
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentProfileId.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/sessions/requests/TSessionOpenRequest.hpp"

/**
 * @file TSessionRuntimeContext.hpp
 * @brief Runtime context for ASCC session lifecycle operation.
 */
namespace assembler::communication_context {
    struct TSessionRuntimeContext final {
        TSessionOpenRequest open_request{};
        TSession session{};
        TAsccComponentProfileId profile_id{TAsccComponentProfileId::invalid()};
        bool admitted{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return open_request.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return admitted && session.is_open(); }
    };
}
