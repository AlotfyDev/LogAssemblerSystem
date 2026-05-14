#pragma once
#include <array>
#include <cstddef>
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowRecord.hpp"
namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TCarrierFlowLedger final
    {
        std::array<TCarrierFlowRecord, Capacity> records{};
        std::size_t count{0u};
        std::uint64_t rejected_records{0u};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return count <= Capacity; }
        constexpr bool record(TCarrierFlowRecord flow_record) noexcept
        {
            if (count >= Capacity || !flow_record.is_valid())
            {
                ++rejected_records;
                return false;
            }
            records[count++] = flow_record;
            return true;
        }
    };
}
