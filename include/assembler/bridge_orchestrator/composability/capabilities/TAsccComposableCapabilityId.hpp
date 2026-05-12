#pragma once

#include <cstdint>

/**
 * @file TAsccComposableCapabilityId.hpp
 * @brief Opaque identity for an ASCC composable capability record.
 */

namespace assembler::communication_context
{
    struct TAsccComposableCapabilityId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TAsccComposableCapabilityId invalid() noexcept
        {
            return TAsccComposableCapabilityId{};
        }

        [[nodiscard]] static constexpr TAsccComposableCapabilityId from_value(
            std::uint64_t id) noexcept
        {
            return TAsccComposableCapabilityId{id};
        }

        friend constexpr bool operator==(
            TAsccComposableCapabilityId lhs,
            TAsccComposableCapabilityId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        friend constexpr bool operator!=(
            TAsccComposableCapabilityId lhs,
            TAsccComposableCapabilityId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
