#pragma once
#include <cstdint>
#include <string_view>
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"

/**
 * @file TProtocolStepRequirementBinding.hpp
 * @brief Binds a protocol step/stage to participant, carrier, and binding requirements.
 *
 * This is the missing link between endpoint-neutral protocol steps and
 * declared protocol requirements. It does not invoke endpoints.
 */
namespace assembler::communication_context {
    struct TProtocolStepRequirementBinding final {
        std::uint64_t binding_id{0u};
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TBridgeStage from{TBridgeStage::idle};
        TBridgeStage to{TBridgeStage::idle};
        std::uint64_t participant_requirement_id{0u};
        std::uint64_t carrier_requirement_id{0u};
        std::uint64_t binding_requirement_id{0u};
        bool required{true};
        std::string_view step_name{};
        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return binding_id != 0u && protocol != TBridgeProtocolKind::unknown && from != to;
        }
    };
}
