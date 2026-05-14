#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
namespace assembler::communication_context
{
    struct TCarrierRequirementSatisfactionReport final
    {
        TAsccCarrierKind required_kind{TAsccCarrierKind::unknown};
        TCarrierView observed_carrier{};
        bool kind_matched{false};
        bool required{true};
        std::string_view note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return required_kind != TAsccCarrierKind::unknown; }
        [[nodiscard]] constexpr bool satisfied() const noexcept { return is_valid() && (!required || kind_matched); }
    };
}
