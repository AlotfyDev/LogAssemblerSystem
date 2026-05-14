#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowDirection.hpp"
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
namespace assembler::communication_context
{
    struct TCarrierProtocolBindingMap final
    {
        TAsccCarrierKind carrier_kind{TAsccCarrierKind::unknown};
        TParticipantRole participant_role{TParticipantRole::unknown};
        TCarrierFlowDirection direction{TCarrierFlowDirection::unknown};
        std::string_view protocol_family{};
        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return carrier_kind != TAsccCarrierKind::unknown
                && participant_role != TParticipantRole::unknown
                && direction != TCarrierFlowDirection::unknown
                && !protocol_family.empty();
        }
    };
}
