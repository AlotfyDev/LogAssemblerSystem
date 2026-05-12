#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/capabilities/TAsccComposableCapability.hpp"

/**
 * @file TAsccComposableCapabilitySet.hpp
 * @brief Fixed-capacity ASCC composable capability set.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccComposableCapabilitySet final
    {
        std::array<TAsccComposableCapability, Capacity> capabilities{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view set_name{"ascc_capability_set"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !set_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr bool contains(TAsccComposableCapabilityKind kind) const noexcept
        {
            if (kind == TAsccComposableCapabilityKind::unknown)
            {
                return false;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (capabilities[index].kind == kind)
                {
                    return true;
                }
            }

            return false;
        }

        constexpr bool add(TAsccComposableCapability capability) noexcept
        {
            if (!is_valid() || full() || !capability.is_valid() || contains(capability.kind))
            {
                ++rejected_insertions;
                return false;
            }

            capabilities[count] = capability;
            ++count;
            return true;
        }

        [[nodiscard]] static constexpr TAsccComposableCapabilitySet make(
            std::string_view name = "ascc_capability_set",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccComposableCapabilitySet{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
