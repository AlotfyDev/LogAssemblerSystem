#pragma once
#include <string_view>
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"

/**
 * @file TProtocolStepEvidenceRequirement.hpp
 * @brief Declares evidence expected for a protocol step.
 */
namespace assembler::communication_context {
    struct TProtocolStepEvidenceRequirement final {
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TBridgeStage stage{TBridgeStage::idle};
        bool require_frame{true};
        bool require_trace{true};
        bool require_requirement_report{false};
        bool require_invocation_report{false};
        std::string_view evidence_name{};
        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return protocol != TBridgeProtocolKind::unknown && stage != TBridgeStage::idle;
        }
    };
}
