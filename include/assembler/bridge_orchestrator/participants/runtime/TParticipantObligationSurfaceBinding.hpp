#pragma once
#include <string_view>

/**
 * @file TParticipantObligationSurfaceBinding.hpp
 * @brief Descriptor binding a participant to an obligation surface without invoking it.
 */
namespace assembler::communication_context {
    struct TParticipantObligationSurfaceBinding final {
        std::uint64_t participant_id{0u};
        std::string_view obligation_surface{};
        std::string_view operation_family{};
        bool callable_surface_declared{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return participant_id != 0u && !obligation_surface.empty() && !operation_family.empty(); }
    };
}
