#pragma once
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityMatchResult.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityRequirement.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCarrierCapability.hpp"

/**
 * @file TParticipantCapabilityMatcher.hpp
 * @brief Runtime matcher between participant requirements and provided capabilities.
 */
namespace assembler::communication_context {
    struct TParticipantCapabilityMatcher final {
        [[nodiscard]] static constexpr TParticipantCapabilityMatchResult match(TParticipantCapabilityRequirement req, TParticipantCarrierCapability provided) noexcept {
            if (!req.is_valid()) return TParticipantCapabilityMatchResult::make(TParticipantCapabilityMatchStatus::unknown, req, provided, "invalid requirement");
            if (!provided.is_valid()) return TParticipantCapabilityMatchResult::make(req.is_required() ? TParticipantCapabilityMatchStatus::missing_required_capability : TParticipantCapabilityMatchStatus::optional_missing, req, provided);
            if (req.role != provided.role) return TParticipantCapabilityMatchResult::make(TParticipantCapabilityMatchStatus::wrong_role, req, provided);
            if (req.capability != provided.capability) return TParticipantCapabilityMatchResult::make(TParticipantCapabilityMatchStatus::wrong_capability, req, provided);
            if (req.carrier != provided.carrier) return TParticipantCapabilityMatchResult::make(TParticipantCapabilityMatchStatus::wrong_carrier, req, provided);
            if (req.direction != provided.direction) return TParticipantCapabilityMatchResult::make(TParticipantCapabilityMatchStatus::wrong_direction, req, provided);
            if (req.protocol != TBridgeProtocolKind::unknown && provided.protocol != TBridgeProtocolKind::unknown && req.protocol != provided.protocol) return TParticipantCapabilityMatchResult::make(TParticipantCapabilityMatchStatus::protocol_mismatch, req, provided);
            return TParticipantCapabilityMatchResult::make(TParticipantCapabilityMatchStatus::matched, req, provided);
        }
    };
}
