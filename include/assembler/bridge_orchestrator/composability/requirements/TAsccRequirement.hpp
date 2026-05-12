#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/requirements/TAsccRequirementKind.hpp"

/**
 * @file TAsccRequirement.hpp
 * @brief One ASCC composability requirement declaration.
 */

namespace assembler::communication_context
{
    struct TAsccRequirement final
    {
        std::uint64_t requirement_id{0u};
        TAsccRequirementKind kind{TAsccRequirementKind::unknown};
        std::string_view required_by{};
        std::string_view note{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return requirement_id != 0u
                && kind != TAsccRequirementKind::unknown
                && !required_by.empty();
        }

        [[nodiscard]] constexpr bool is_core() const noexcept
        {
            return is_core_requirement(kind);
        }

        [[nodiscard]] constexpr bool is_deferred() const noexcept
        {
            return is_deferred_requirement(kind);
        }

        [[nodiscard]] static constexpr TAsccRequirement make(
            std::uint64_t id,
            TAsccRequirementKind requirement_kind,
            std::string_view owner,
            std::string_view requirement_note = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccRequirement{
                id,
                requirement_kind,
                owner,
                requirement_note,
                token
            };
        }
    };
}
