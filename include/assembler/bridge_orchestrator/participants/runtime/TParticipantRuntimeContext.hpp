#pragma once
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/runtime/TParticipantObligationSurfaceBinding.hpp"
#include "assembler/communication_context/participants/runtime/TParticipantRoleBindingMap.hpp"

/**
 * @file TParticipantRuntimeContext.hpp
 * @brief Runtime context combining participant identity with binding and obligation context.
 *
 * This is not an endpoint object. It is ASCC-local runtime context.
 */
namespace assembler::communication_context {
    struct TParticipantRuntimeContext final {
        TParticipant participant{};
        TParticipantRoleBindingMap role_binding{};
        TParticipantObligationSurfaceBinding obligation_binding{};
        bool admitted{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return participant.is_valid() && role_binding.is_valid() && obligation_binding.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && admitted; }
    };
}
