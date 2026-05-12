#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/requirements/TAsccRequirement.hpp"

/**
 * @file TAsccRequirementSet.hpp
 * @brief Fixed-capacity ASCC composability requirement set.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccRequirementSet final
    {
        std::array<TAsccRequirement, Capacity> requirements{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view set_name{"ascc_requirement_set"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !set_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr bool contains(TAsccRequirementKind kind) const noexcept
        {
            if (kind == TAsccRequirementKind::unknown)
            {
                return false;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (requirements[index].kind == kind)
                {
                    return true;
                }
            }

            return false;
        }

        constexpr bool add(TAsccRequirement requirement) noexcept
        {
            if (!is_valid() || full() || !requirement.is_valid() || contains(requirement.kind))
            {
                ++rejected_insertions;
                return false;
            }

            requirements[count] = requirement;
            ++count;
            return true;
        }

        [[nodiscard]] constexpr std::size_t core_count() const noexcept
        {
            std::size_t result{0u};
            for (std::size_t index = 0u; index < count; ++index)
            {
                if (requirements[index].is_core())
                {
                    ++result;
                }
            }
            return result;
        }

        [[nodiscard]] static constexpr TAsccRequirementSet make(
            std::string_view name = "ascc_requirement_set",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccRequirementSet{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
