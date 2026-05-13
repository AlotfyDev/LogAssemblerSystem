#pragma once

#include <cstdint>

namespace assembler::communication_context
{
    struct TAsccComponentProfileId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TAsccComponentProfileId invalid() noexcept
        {
            return TAsccComponentProfileId{};
        }

        [[nodiscard]] static constexpr TAsccComponentProfileId from_value(
            std::uint64_t id) noexcept
        {
            return TAsccComponentProfileId{id};
        }
    };
}
