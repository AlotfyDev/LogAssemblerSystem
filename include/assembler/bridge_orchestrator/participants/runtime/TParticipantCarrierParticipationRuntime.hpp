#pragma once
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowRuntime.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCarrierCapability.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"

/**
 * @file TParticipantCarrierParticipationRuntime.hpp
 * @brief Runtime helper for recording participant carrier production/consumption.
 */
namespace assembler::communication_context {
    struct TParticipantCarrierParticipationRuntime final {
        template <std::size_t Capacity>
        [[nodiscard]] static constexpr bool record_participation(TCarrierFlowRuntime<Capacity>& runtime, TParticipant p, TParticipantCarrierCapability cap, TCarrierView carrier, TCarrierFlowDirection direction) noexcept {
            if (!p.is_valid() || !cap.is_valid()) return false;
            return runtime.accept_record(TCarrierFlowRecord{carrier, direction, carrier.correlation, to_string(p.role), "participant carrier participation"});
        }
    };
}
