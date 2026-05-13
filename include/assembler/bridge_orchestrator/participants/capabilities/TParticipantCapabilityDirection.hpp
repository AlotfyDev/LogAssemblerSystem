#pragma once

#include <string_view>

namespace assembler::communication_context
{
    enum class TParticipantCapabilityDirection
    {
        unknown,
        produces_carrier,
        consumes_carrier,
        bidirectional_carrier,
        observes_only
    };

    [[nodiscard]] constexpr bool can_produce(
        TParticipantCapabilityDirection direction) noexcept
    {
        return direction == TParticipantCapabilityDirection::produces_carrier
            || direction == TParticipantCapabilityDirection::bidirectional_carrier;
    }

    [[nodiscard]] constexpr bool can_consume(
        TParticipantCapabilityDirection direction) noexcept
    {
        return direction == TParticipantCapabilityDirection::consumes_carrier
            || direction == TParticipantCapabilityDirection::bidirectional_carrier;
    }

    [[nodiscard]] constexpr bool is_observer_direction(
        TParticipantCapabilityDirection direction) noexcept
    {
        return direction == TParticipantCapabilityDirection::observes_only;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TParticipantCapabilityDirection direction) noexcept
    {
        switch (direction)
        {
            case TParticipantCapabilityDirection::unknown: return "unknown";
            case TParticipantCapabilityDirection::produces_carrier: return "produces_carrier";
            case TParticipantCapabilityDirection::consumes_carrier: return "consumes_carrier";
            case TParticipantCapabilityDirection::bidirectional_carrier: return "bidirectional_carrier";
            case TParticipantCapabilityDirection::observes_only: return "observes_only";
        }

        return "unknown";
    }
}
