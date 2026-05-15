#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowDirection.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowLedger.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowRecord.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowReport.hpp"
#include "assembler/communication_context/bridge_carriers/runtime/TCarrierFlowRuntimeStatus.hpp"

/**
 * @file TCarrierFlowRuntime.hpp
 * @brief Runtime facade over a bounded ASCC carrier-flow ledger.
 *
 * This runtime owns carrier-flow evidence recording for the bridge carrier
 * domain.
 *
 * Responsibilities:
 * - Accept canonical carrier flow records.
 * - Provide semantic recording helpers.
 * - Maintain runtime flow status.
 * - Expose aggregate runtime evidence reports.
 * - Track runtime blockage/rejection state.
 *
 * This runtime intentionally does NOT:
 * - invoke adapters/endpoints
 * - own payload buffers
 * - perform transport IO
 * - execute protocol/session logic
 *
 * It exists purely as bounded runtime evidence infrastructure.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TCarrierFlowRuntime final
    {
        TCarrierFlowLedger<Capacity> ledger{};
        TCarrierFlowRuntimeStatus status{TCarrierFlowRuntimeStatus::idle};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return ledger.is_valid()
                && status != TCarrierFlowRuntimeStatus::unknown;
        }

        [[nodiscard]] constexpr bool blocked() const noexcept
        {
            return status == TCarrierFlowRuntimeStatus::blocked
                || ledger.has_rejections();
        }

        constexpr bool accept_record(TCarrierFlowRecord record) noexcept
        {
            if (!is_valid())
            {
                status = TCarrierFlowRuntimeStatus::failed;
                return false;
            }

            status = TCarrierFlowRuntimeStatus::recording;

            const bool accepted = ledger.record(record);

            status = accepted
                ? TCarrierFlowRuntimeStatus::accepting
                : TCarrierFlowRuntimeStatus::blocked;

            return accepted;
        }

        constexpr bool record_direction(
            TCarrierView carrier,
            TCarrierFlowDirection direction,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return accept_record(
                TCarrierFlowRecord::make(
                    carrier,
                    direction,
                    participant_label,
                    protocol_family,
                    operation_name,
                    note));
        }

        constexpr bool record_produced(
            TCarrierView carrier,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return record_direction(
                carrier,
                TCarrierFlowDirection::produced,
                participant_label,
                protocol_family,
                operation_name,
                note);
        }

        constexpr bool record_consumed(
            TCarrierView carrier,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return record_direction(
                carrier,
                TCarrierFlowDirection::consumed,
                participant_label,
                protocol_family,
                operation_name,
                note);
        }

        constexpr bool record_observed(
            TCarrierView carrier,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return record_direction(
                carrier,
                TCarrierFlowDirection::observed,
                participant_label,
                protocol_family,
                operation_name,
                note);
        }

        constexpr bool record_relayed(
            TCarrierView carrier,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return record_direction(
                carrier,
                TCarrierFlowDirection::relayed,
                participant_label,
                protocol_family,
                operation_name,
                note);
        }

        constexpr bool record_deferred(
            TCarrierView carrier,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return record_direction(
                carrier,
                TCarrierFlowDirection::deferred,
                participant_label,
                protocol_family,
                operation_name,
                note);
        }

        constexpr bool record_rejected(
            TCarrierView carrier,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return record_direction(
                carrier,
                TCarrierFlowDirection::rejected,
                participant_label,
                protocol_family,
                operation_name,
                note);
        }

        constexpr bool record_failed(
            TCarrierView carrier,
            std::string_view participant_label = {},
            std::string_view protocol_family = {},
            std::string_view operation_name = {},
            std::string_view note = {}) noexcept
        {
            return record_direction(
                carrier,
                TCarrierFlowDirection::failed,
                participant_label,
                protocol_family,
                operation_name,
                note);
        }

        constexpr void complete() noexcept
        {
            status = blocked()
                ? TCarrierFlowRuntimeStatus::blocked
                : TCarrierFlowRuntimeStatus::completed;
        }

        [[nodiscard]] constexpr TCarrierFlowReport report(
            TCorrelationToken token,
            std::string_view name = "carrier_flow_runtime_report") const noexcept
        {
            return TCarrierFlowReport{
                ledger.count,
                ledger.produced_count(),
                ledger.consumed_count(),
                ledger.count_direction(TCarrierFlowDirection::observed),
                ledger.count_direction(TCarrierFlowDirection::relayed),
                ledger.rejected_records,
                token,
                name
            };
        }
    };
}
