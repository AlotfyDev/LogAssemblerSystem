#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowDirection.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowLedger.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowReport.hpp"
#include "assembler/communication_context/bridge_carriers/runtime/TCarrierFlowRuntimeStatus.hpp"

/**
 * @file TCarrierFlowRuntime.hpp
 * @brief Runtime facade over a bounded ASCC carrier-flow ledger.
 *
 * This runtime accepts carrier-flow records, updates local flow status, and
 * emits aggregate flow evidence. It does not route endpoints, invoke adapters,
 * or own payload storage.
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
