#pragma once

#include <cstdint>

/**
 * @file TPortId.hpp
 * @brief Opaque bridge-visible receiver/container-provider port identity.
 *
 * @section ascc_comp_w01_reg05 REG-05 Identity Normalization
 * `TPortId` gives ASCC registries a first-class ID type compatible with
 * `TBoundedRegistry`.  It identifies a bridge-visible port surface/descriptor,
 * not a concrete endpoint-owned port object lifecycle.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This ID does not own receiver state, endpoint instances, endpoint lifecycle,
 * pipeline composition, or policy execution.
 */

namespace assembler::communication_context
{
    struct TPortId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TPortId invalid() noexcept
        {
            return TPortId{};
        }

        [[nodiscard]] static constexpr TPortId from_value(
            std::uint64_t id) noexcept
        {
            return TPortId{id};
        }

        friend constexpr bool operator==(
            TPortId lhs,
            TPortId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        friend constexpr bool operator!=(
            TPortId lhs,
            TPortId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
