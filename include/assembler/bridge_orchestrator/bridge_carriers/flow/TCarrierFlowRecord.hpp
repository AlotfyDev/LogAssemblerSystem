#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowDirection.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"

/**
 * @file TCarrierFlowRecord.hpp
 * @brief One runtime event in ASCC carrier flow.
 *
 * A carrier contract by itself is only a value. This record is the first
 * runtime evidence unit that says a carrier was produced, consumed, observed,
 * or relayed by a participant side during an ASCC operation.
 */

namespace assembler::communication_context
{
    struct TCarrierFlowRecord final
    {
        TCarrierView carrier{};
        TCarrierFlowDirection direction{TCarrierFlowDirection::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view participant_label{};
        std::string_view protocol_family{};
        std::string_view operation_name{};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return carrier.is_valid()
                && direction != TCarrierFlowDirection::unknown
                && correlation.is_valid();
        }

        [[nodiscard]] constexpr bool is_produced() const noexcept
        {
            return direction == TCarrierFlowDirection::produced;
        }

        [[nodiscard]] constexpr bool is_consumed() const noexcept
        {
            return direction == TCarrierFlowDirection::consumed;
        }

        [[nodiscard]] static constexpr TCarrierFlowRecord make(
            TCarrierView carrier_view,
            TCarrierFlowDirection flow_direction,
            TCorrelationToken token,
            std::string_view participant = {},
            std::string_view protocol = {},
            std::string_view operation = {},
            std::string_view record_note = {}) noexcept
        {
            return TCarrierFlowRecord{
                carrier_view,
                flow_direction,
                token,
                participant,
                protocol,
                operation,
                record_note
            };
        }
    };
}
