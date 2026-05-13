#pragma once

#include <cstdint>

namespace assembler::communication_context
{
    struct TAsccComponentId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TAsccComponentId invalid() noexcept
        {
            return TAsccComponentId{};
        }

        [[nodiscard]] static constexpr TAsccComponentId from_value(
            std::uint64_t id) noexcept
        {
            return TAsccComponentId{id};
        }

        [[nodiscard]] friend constexpr bool operator==(
            TAsccComponentId lhs,
            TAsccComponentId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(
            TAsccComponentId lhs,
            TAsccComponentId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
