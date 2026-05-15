#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"

/**
 * @file TObligationInvocationContext.hpp
 * @brief Runtime context for one ASCC obligation invocation.
 */
namespace assembler::communication_context {
    struct TObligationInvocationContext final {
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TBridgeStage stage{TBridgeStage::idle};
        TParticipantRole participant_role{TParticipantRole::unknown};
        TAsccCarrierKind carrier_kind{TAsccCarrierKind::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view operation_name{};
        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return protocol != TBridgeProtocolKind::unknown && participant_role != TParticipantRole::unknown && !operation_name.empty();
        }
    };
}
