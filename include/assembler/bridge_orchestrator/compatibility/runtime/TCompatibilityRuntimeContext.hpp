#pragma once
#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/compatibility/profiles/TCompatibilityProfile.hpp"

/**
 * @file TCompatibilityRuntimeContext.hpp
 * @brief Component-level compatibility context for ASCC admission.
 */
namespace assembler::communication_context {
    struct TCompatibilityRuntimeContext final {
        TBinding binding{};
        TCompatibilityProfile profile{};
        bool participant_ready{false};
        bool channel_ready{false};
        bool binding_ready{false};
        bool obligation_ready{false};
        bool carrier_ready{false};
        bool session_ready{false};
        bool protocol_ready{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return binding.is_valid() && profile.is_valid(); }
    };
}
