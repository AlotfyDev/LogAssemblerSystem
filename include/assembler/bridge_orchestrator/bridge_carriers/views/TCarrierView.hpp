#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"

/**
 * @file TCarrierView.hpp
 * @brief Bridge-visible read-only carrier diagnostic view.
 *
 * TCarrierView is the safe projection used by validation, requirement
 * satisfaction, flow runtime, diagnostics, and facade projections.
 *
 * It intentionally uses the canonical `TAsccCarrierKind` vocabulary. There is
 * no second local carrier-kind enum in this view; duplicated carrier taxonomies
 * create compile drift and requirement-matching ambiguity.
 */

namespace assembler::communication_context
{
    struct TCarrierView final
    {
        TAsccCarrierKind kind{TAsccCarrierKind::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        bool valid{false};
        std::string_view label{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return valid
                && kind != TAsccCarrierKind::unknown
                && correlation.is_valid();
        }

        [[nodiscard]] constexpr bool is_kind(TAsccCarrierKind expected) const noexcept
        {
            return is_valid() && kind == expected;
        }

        [[nodiscard]] static constexpr TCarrierView make(
            TAsccCarrierKind carrier_kind,
            TCorrelationToken token,
            bool is_valid_carrier,
            std::string_view display_label = {}) noexcept
        {
            return TCarrierView{
                carrier_kind,
                token,
                is_valid_carrier,
                display_label
            };
        }
    };
}
