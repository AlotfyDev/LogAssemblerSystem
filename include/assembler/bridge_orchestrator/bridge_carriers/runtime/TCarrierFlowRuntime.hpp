#pragma once
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowLedger.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowReport.hpp"
#include "assembler/communication_context/bridge_carriers/runtime/TCarrierFlowRuntimeStatus.hpp"
namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TCarrierFlowRuntime final
    {
        TCarrierFlowLedger<Capacity> ledger{};
        TCarrierFlowRuntimeStatus status{TCarrierFlowRuntimeStatus::idle};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return ledger.is_valid() && status != TCarrierFlowRuntimeStatus::unknown; }
        constexpr bool accept_record(TCarrierFlowRecord record) noexcept
        {
            status = TCarrierFlowRuntimeStatus::recording;
            const bool ok = ledger.record(record);
            status = ok ? TCarrierFlowRuntimeStatus::accepting : TCarrierFlowRuntimeStatus::blocked;
            return ok;
        }
        [[nodiscard]] constexpr TCarrierFlowReport report(TCorrelationToken token, std::string_view name = "carrier_flow_runtime_report") const noexcept
        {
            return TCarrierFlowReport{ledger.count, ledger.rejected_records, token, name};
        }
    };
}
