#pragma once
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionReport.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
namespace assembler::communication_context
{
    struct TCarrierRequirementSatisfactionEngine final
    {
        [[nodiscard]] static constexpr TCarrierRequirementSatisfactionReport satisfy(TAsccCarrierKind required_kind, TCarrierView observed, bool required = true) noexcept
        {
            return TCarrierRequirementSatisfactionReport{required_kind, observed, observed.is_valid(), required, {}};
        }
    };
}
