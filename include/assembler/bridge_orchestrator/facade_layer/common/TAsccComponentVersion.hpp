#pragma once

#include <cstdint>

namespace assembler::communication_context
{
    struct TAsccComponentVersion final
    {
        std::uint16_t major{0u};
        std::uint16_t minor{0u};
        std::uint16_t patch{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return major != 0u;
        }

        [[nodiscard]] static constexpr TAsccComponentVersion v1(
            std::uint16_t minor_version = 0u,
            std::uint16_t patch_version = 0u) noexcept
        {
            return TAsccComponentVersion{1u, minor_version, patch_version};
        }
    };
}
