#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/composability/capabilities/TAsccComposableCapabilityId.hpp"
#include "assembler/communication_context/composability/capabilities/TAsccComposableCapabilityKind.hpp"

/**
 * @file TAsccComposableCapability.hpp
 * @brief One functional ASCC capability declaration.
 */

namespace assembler::communication_context
{
    struct TAsccComposableCapability final
    {
        TAsccComposableCapabilityId capability_id{TAsccComposableCapabilityId::invalid()};
        TAsccComposableCapabilityKind kind{TAsccComposableCapabilityKind::unknown};
        std::string_view component{};
        std::string_view note{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return capability_id.is_valid()
                && kind != TAsccComposableCapabilityKind::unknown
                && !component.empty();
        }

        [[nodiscard]] static constexpr TAsccComposableCapability make(
            TAsccComposableCapabilityId id,
            TAsccComposableCapabilityKind capability_kind,
            std::string_view component_name,
            std::string_view capability_note = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAsccComposableCapability{
                id,
                capability_kind,
                component_name,
                capability_note,
                token
            };
        }
    };
}
