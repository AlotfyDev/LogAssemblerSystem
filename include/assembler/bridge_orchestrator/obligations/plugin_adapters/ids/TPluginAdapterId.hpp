#pragma once

#include <cstdint>

/**
 * @file TPluginAdapterId.hpp
 * @brief Opaque bridge-visible content-side plugin-adapter identity.
 *
 * @section ascc_comp_w01_reg05 REG-05 Identity Normalization
 * `TPluginAdapterId` gives ASCC registries a first-class ID type compatible
 * with `TBoundedRegistry`.  It identifies a bridge-visible plugin-adapter
 * surface/descriptor, not a concrete endpoint-owned adapter object lifecycle.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This ID does not own payloads, endpoint instances, endpoint lifecycle,
 * pipeline composition, or policy execution.
 */

namespace assembler::communication_context
{
    struct TPluginAdapterId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TPluginAdapterId invalid() noexcept
        {
            return TPluginAdapterId{};
        }

        [[nodiscard]] static constexpr TPluginAdapterId from_value(
            std::uint64_t id) noexcept
        {
            return TPluginAdapterId{id};
        }

        friend constexpr bool operator==(
            TPluginAdapterId lhs,
            TPluginAdapterId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        friend constexpr bool operator!=(
            TPluginAdapterId lhs,
            TPluginAdapterId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
