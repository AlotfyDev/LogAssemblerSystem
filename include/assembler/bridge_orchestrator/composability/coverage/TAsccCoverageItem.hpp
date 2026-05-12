#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/capabilities/TAsccComposableCapabilityKind.hpp"
#include "assembler/communication_context/composability/coverage/TAsccCoverageState.hpp"
#include "assembler/communication_context/composability/requirements/TAsccRequirementKind.hpp"

/**
 * @file TAsccCoverageItem.hpp
 * @brief One ASCC requirement-to-capability coverage record.
 */

namespace assembler::communication_context
{
    struct TAsccCoverageItem final
    {
        std::uint64_t item_id{0u};
        TAsccRequirementKind requirement{TAsccRequirementKind::unknown};
        TAsccComposableCapabilityKind capability{TAsccComposableCapabilityKind::unknown};
        TAsccCoverageState state{TAsccCoverageState::unknown};
        std::string_view component{};
        std::string_view owner_wave{};
        std::string_view note{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return item_id != 0u
                && requirement != TAsccRequirementKind::unknown
                && state != TAsccCoverageState::unknown
                && !component.empty();
        }

        [[nodiscard]] constexpr bool blocks_core_readiness() const noexcept
        {
            return is_core_requirement(requirement)
                && blocks_core_readiness(state);
        }

        [[nodiscard]] constexpr bool is_deferred() const noexcept
        {
            return is_deferred(state) || is_deferred_requirement(requirement);
        }

        [[nodiscard]] static constexpr TAsccCoverageItem make(
            std::uint64_t id,
            TAsccRequirementKind requirement_kind,
            TAsccComposableCapabilityKind capability_kind,
            TAsccCoverageState coverage_state,
            std::string_view component_name,
            std::string_view wave = {},
            std::string_view coverage_note = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccCoverageItem{
                id,
                requirement_kind,
                capability_kind,
                coverage_state,
                component_name,
                wave,
                coverage_note,
                token
            };
        }
    };
}
