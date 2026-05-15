#pragma once
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"

/**
 * @file TParticipantRegistryAdmissionPolicy.hpp
 * @brief Policy for admitting participants into an ASCC participant registry if present.
 */
namespace assembler::communication_context {
    struct TParticipantRegistryAdmissionPolicy final {
        [[nodiscard]] static constexpr bool admits(TParticipant p) noexcept { return p.is_valid(); }
    };
}
