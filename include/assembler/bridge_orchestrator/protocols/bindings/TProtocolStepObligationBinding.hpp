#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"

/**
 * @file TProtocolStepObligationBinding.hpp
 * @brief Binds a protocol step to an adapter/port obligation operation family.
 *
 * This descriptor maps protocol movement to obligation surface expectations
 * without performing the call.
 */
namespace assembler::communication_context {
    struct TProtocolStepObligationBinding final {
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TBridgeStage stage{TBridgeStage::idle};
        TParticipantRole participant_role{TParticipantRole::unknown};
        TAsccCarrierKind carrier{TAsccCarrierKind::unknown};
        TObligationSide obligation_side{TObligationSide::unknown};
        std::string_view operation_family{};
        std::string_view operation_name{};
        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return protocol != TBridgeProtocolKind::unknown
                && participant_role != TParticipantRole::unknown
                && carrier != TAsccCarrierKind::unknown
                && obligation_side != TObligationSide::unknown
                && !operation_family.empty();
        }
    };
}
