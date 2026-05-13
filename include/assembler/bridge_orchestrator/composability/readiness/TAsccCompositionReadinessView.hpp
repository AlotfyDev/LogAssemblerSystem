#pragma once

#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccBindingReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccBridgeReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccParticipantReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccProtocolReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"
#include "assembler/communication_context/composability/readiness/TAsccSessionReadinessView.hpp"

/**
 * @file TAsccCompositionReadinessView.hpp
 * @brief Aggregate readiness projection for ASCC composable-core usage.
 *
 * @section ascc_comp_w06 Purpose
 * This view aggregates participant, binding, protocol, session, and bridge
 * readiness views into one read-only composition-level projection. It is not a
 * final production gate and it does not compose pipelines.
 */

namespace assembler::communication_context
{
    struct TAsccCompositionReadinessView final
    {
        TAsccParticipantReadinessView participants{};
        TAsccBindingReadinessView binding{};
        TAsccProtocolReadinessView protocol{};
        TAsccSessionReadinessView session{};
        TAsccBridgeReadinessView bridge{};
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        std::string_view composition_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TAsccReadinessStatus::unknown
                && participants.is_valid()
                && binding.is_valid()
                && protocol.is_valid()
                && session.is_valid()
                && bridge.is_valid()
                && !composition_name.empty();
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && is_ready(status)
                && participants.ready()
                && binding.ready()
                && protocol.ready()
                && session.ready()
                && bridge.ready();
        }

        [[nodiscard]] constexpr bool blocked() const noexcept
        {
            return is_blocking_readiness_status(status)
                || participants.blocked()
                || binding.blocked()
                || protocol.blocked()
                || session.blocked()
                || bridge.blocked();
        }

        [[nodiscard]] static constexpr TAsccCompositionReadinessView make(
            TAsccParticipantReadinessView participant_view,
            TAsccBindingReadinessView binding_view,
            TAsccProtocolReadinessView protocol_view,
            TAsccSessionReadinessView session_view,
            TAsccBridgeReadinessView bridge_view,
            TAsccReadinessStatus readiness_status = TAsccReadinessStatus::ready,
            std::string_view name = "ascc_composition_readiness") noexcept
        {
            return TAsccCompositionReadinessView{
                participant_view,
                binding_view,
                protocol_view,
                session_view,
                bridge_view,
                readiness_status,
                name
            };
        }
    };
}
